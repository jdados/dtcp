
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"

#include "ads1299.h"
#include "uart.h"

volatile float voltage;
float voltages[100];
uint8_t count;
float sum;

FIFO_t AFE_FIFO;

volatile uint8_t gCurrentIndex = 0; // Tracks which element to send next
volatile uint8_t gTxState = 0; // 0: Header, 1-4: Float Bytes
const uint8_t HEADER_BYTE = 0xAA;

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
    init_FIFO(&AFE_FIFO);

    DL_GPIO_clearInterruptStatus(GPIO_A_PORT, GPIO_A_DRDY_PIN);
    DL_GPIO_enableInterrupt(GPIO_A_PORT, GPIO_A_DRDY_PIN);
    NVIC_EnableIRQ(GPIOA_INT_IRQn);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    DL_UART_Main_transmitData(UART_0_INST, HEADER_BYTE);
    gTxState = 1; // Next interrupt should send the first byte of the float

    count = 0;
    sum = 0;
    for (uint8_t i = 0; i < 100; ++i) voltages[i] = 0;

    while (1) { 
        // uint8_t val = 0;
        // val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        // if (val == 0) {
        //     voltage = ADS1299_read_data_channel_2();
            
        //     /* Remove offset */
        //     // sum -= voltages[count];
        //     // sum += voltage;
        //     // voltages[count] = voltage;
        //     // count = (count + 1) % 100;
        //     // float average = sum / 100;

        //     // if (fabsf(voltage) - fabsf(average) > 5.0f) {
        //     //     DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_RED_22_PIN);
        //     // }

        //     // UART_transmit_voltage_binary(voltage);

        // }
    }
}


/* Have a FIFO that takes the samples ? */
void GPIOA_IRQHandler(void) {
    switch (DL_GPIO_getPendingInterrupt(GPIOA)) {
        case (DL_GPIO_IIDX_DIO2):
            voltage = ADS1299_read_data_channel_2();
            write_FIFO(&AFE_FIFO, voltage);
            // voltages[count] = voltage;
            // count = (count + 1) % 100;

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

void UART_0_INST_IRQHandler(void) {
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_TX:
            
            // float val = voltages[gCurrentIndex];
            float val = read_FIFO(&AFE_FIFO);
            if (val == 0) break;
            uint8_t *ptr = (uint8_t *)&val;

            if (gTxState == 0) {
                // State 0: Send Header
                DL_UART_Main_transmitData(UART_0_INST, HEADER_BYTE);
                gTxState = 1;
            } 
            else if (gTxState <= 4) {
                // State 1-4: Send the 4 bytes of the float
                // ptr[0] for state 1, ptr[1] for state 2, etc.
                DL_UART_Main_transmitData(UART_0_INST, ptr[gTxState - 1]);
                gTxState++;
                
                // If we just sent the last byte (state 4), reset for the next float
                if (gTxState > 4) {
                    gTxState = 0;
                    gCurrentIndex = (gCurrentIndex + 1) % 100;
                }
            }
            break;
            
        default:
            break;
    }
}

void delay_ms(int ms) {
    delay_cycles(ms * (24e6)/1000);
}