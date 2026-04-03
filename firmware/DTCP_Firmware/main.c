
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"

#include "ads1299.h"
#include "uart.h"

volatile float voltage;
float voltages[100];
uint8_t count;
float sum;

static FIFO_t AFE_FIFO;

/* small printf implementation */

int main(void) {
    delay_ms(150);

    // initializes all the modules
    // SPI Mode for ADS1299:
    // Clock polarity: 0, clock phase: 1
    SYSCFG_DL_init();
    // (GPIOA, CS_PIN);

    ADS1299_init();
    ADS1299_start_conversions();

    DL_GPIO_clearInterruptStatus(GPIO_A_PORT, GPIO_A_DRDY_PIN);
    DL_GPIO_enableInterrupt(GPIO_A_PORT, GPIO_A_DRDY_PIN);
    // NVIC_EnableIRQ(GPIOA_INT_IRQn);

    count = 0;
    sum = 0;
    for (uint8_t i = 0; i < 100; ++i) voltages[i] = 0;

    while (1) { 
        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            voltage = ADS1299_read_data_channel_2();
            
            /* Remove offset */
            // sum -= voltages[count];
            // sum += voltage;
            // voltages[count] = voltage;
            // count = (count + 1) % 100;
            // float average = sum / 100;

            // if (fabsf(voltage) - fabsf(average) > 5.0f) {
            //     DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_RED_22_PIN);
            // }

            UART_transmit_voltage_binary(voltage);

        }
    }
}


/* Have a FIFO that takes the samples */
void GPIOA_IRQHandler(void) {
    uint32_t int_status = DL_GPIO_getPendingInterrupt(GPIOA);
    if (int_status & GPIO_A_DRDY_IOMUX) {
        // voltage = ADS1299_read_data_channel_1();
        // voltages[count] = voltage;

        // if (voltage > 1.0f) {
                /* Timer ? */
        //     delay_ms(55);
        // }
        
        /* UART transmit interrupt ? */
        // // UART_transmit_voltage_binary(voltage);
        
        // if (count == 128) count = 0;
        // ++count;   
        DL_GPIO_clearInterruptStatus(GPIO_A_PORT, GPIO_A_DRDY_IOMUX);
    }
}

void delay_ms(int ms) {
    delay_cycles(ms * (24e6)/1000);
}