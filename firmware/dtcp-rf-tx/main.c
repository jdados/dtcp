#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"
#include <math.h>

#include "ads1299.h"

volatile uint8_t gCurrentIndex = 0; // Tracks which element to send next
volatile uint8_t gTxState = 0; // 0: Header, 1-4: Float Bytes
const uint8_t HEADER_BYTE = 0xAA;

volatile float voltage;
float voltages[100];
uint8_t count;
float sum;

FIFO_t AFE_FIFO;

/* This results in approximately 0.5s of delay assuming 24MHz CPU_CLK */
#define DDS_SYSCLK_FREQ (100000000)
#define MCU_CLK_FREQ (24000000)
#define DDS_WCLK_FREQ (1000000)
#define DDS_WCLK_T_US (10)

/* Wrapper API */
void wait_us(uint32_t t){
    delay_cycles((MCU_CLK_FREQ/1000000)*t);
}

void dds_reset(){
    /*Pulse RST for at least 5 clock cycles*/
    DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN);
    DL_GPIO_setPins(DDS_PORT, DDS_RST_PIN);
    wait_us(DDS_WCLK_T_US/2);

    for(int i = 0; i < 10; i++){
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
    }

    DL_GPIO_clearPins(DDS_PORT, DDS_RST_PIN);
}

void dds_serial_load_en(){
    /* Pulse WCLK */
    DL_GPIO_setPins(DDS_PORT, DDS_WCLK_PIN);
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN);
    wait_us(DDS_WCLK_T_US*4);

    /* Pulse FQ_UD */
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_setPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_clearPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
}

void dds_serial_data_tx(uint32_t dword){
    /* Send the frequency info */
    uint32_t dword_temp = dword;
    for(int i = 0; i < 32; i++){
        /* Setting W0-W31 */
        if((dword_temp & 0x1) == 0x1){
            DL_GPIO_setPins(DDS_PORT, DDS_D7_PIN);
        } else {
            DL_GPIO_clearPins(DDS_PORT, DDS_D7_PIN);
        }

        /* Clock toggling */
        if(i == 0){
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_setPins(DDS_PORT, DDS_WCLK_PIN);
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN);
        } else {
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
        }

        /* Look at the next bit */
        dword_temp = dword_temp>>1;
    }

    /* W32 and W33 are control bits, always set to 0 */
    /* The rest of the bits should be 0 too */
    DL_GPIO_clearPins(DDS_PORT, DDS_D7_PIN);
    for(int i = 0; i < 8; i++){
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
    }

    wait_us(DDS_WCLK_T_US);
    /*Pulse FQ_UD at the end */
    DL_GPIO_setPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_clearPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
}

#define F_OUT_DDS 25000000

volatile uint8_t id;

int main(void) {
    delay_ms(150);
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();

    // /* Initialize the GPIO for the DDS interface */
    // DL_GPIO_clearPins(DDS_PORT, DDS_DDS_EN_PIN);
    // DL_GPIO_clearPins(PA_PORT, PA_EN_PIN);
    
    // /* Initialize DDS in serial mode */
    // dds_serial_load_en();

    // /* Calculate the DDS output frequency */
    // double f_ratio = (double)F_OUT_DDS/(double)DDS_SYSCLK_FREQ;
    // uint32_t freq_dword = (uint32_t)(f_ratio*pow(2,32));
    // dds_serial_data_tx(freq_dword);

    ADS1299_init();
    ADS1299_start_conversions();
    init_FIFO(&AFE_FIFO);

    DL_GPIO_clearInterruptStatus(GPIO_A_PORT, GPIO_A_DRDY_PIN);
    DL_GPIO_enableInterrupt(GPIO_A_PORT, GPIO_A_DRDY_PIN);
    // NVIC_EnableIRQ(GPIOA_INT_IRQn);
    // NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    count = 0;
    sum = 0;
    for (uint8_t i = 0; i < 100; ++i) voltages[i] = 0;

    while (1) {
        // DL_GPIO_setPins(PA_PORT, PA_EN_PIN);
        // wait_us(300000);
        // DL_GPIO_setPins(DDS_PORT, DDS_DDS_EN_PIN);
        // dds_serial_data_tx(freq_dword);
        // wait_us(500000);
        // DL_GPIO_clearPins(DDS_PORT, DDS_DDS_EN_PIN);
        // wait_us(100000);
        // DL_GPIO_clearPins(PA_PORT, PA_EN_PIN);
        // wait_us(1000000);

        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            voltage = ADS1299_read_data_channel_1();
            
            /* Remove offset */
            // sum -= voltages[count];
            // sum += voltage;
            voltages[count] = voltage;
            count = (count + 1) % 100;
            // float average = sum / 100;

            // if (fabsf(voltage) - fabsf(average) > 5.0f) {
            //     DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_RED_22_PIN);
            // }
        }

    }
}

/* Have a FIFO that takes the samples ? */
void GPIOA_IRQHandler(void) {
    switch (DL_GPIO_getPendingInterrupt(GPIOA)) {
        case (DL_GPIO_IIDX_DIO6):
            voltage = ADS1299_read_data_channel_1();
            // write_FIFO(&AFE_FIFO, voltage);
            voltages[count] = voltage;
            count = (count + 1) % 100;

            // if (voltage > 1.0f) {
                    /* Timer ? */
            //     delay_ms(55);
            // }
            
            /* UART transmit interrupt ? */
            // UART_transmit_voltage_binary(voltage);
            
            // if (count == 128) count = 0;
            // ++count;

            DL_GPIO_clearInterruptStatus(GPIO_A_PORT, GPIO_A_DRDY_PIN);
            break;
        default:
            break;
        }
}

void delay_ms(int ms) {
    delay_cycles(ms * (24e6)/1000);
}