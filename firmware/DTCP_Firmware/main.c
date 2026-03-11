
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_uart.h"

#include "ads1299.h"
#include "uart.h"

#include <stdio.h>

float voltage;
float voltages[128];
/* small printf implementation */

void UART_transmitString(char* str) {
    while (*str) {
        // Wait for TX FIFO to have space, then send
        DL_UART_Main_transmitDataBlocking(UART_0_INST, *str++);
    }
}

void UART_transmit_voltage(float voltage) {
        /* UART Transmission */
        char buffer[32];
        // Manual float to string conversion
        int intPart = (int)voltage;
        int fracPart = (int)((voltage - (float)intPart) * 100.0f);
        if (fracPart < 0) fracPart = -fracPart; 

        // Serial Plotter needs one value + newline to plot a single point
        snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
        UART_transmitString(buffer);
}

int main(void) {
    delay_ms(150);

    // initializes all the modules
    // SPI Mode for ADS1299:
    // Clock polarity: 0, clock phase: 1
    SYSCFG_DL_init();
    // (GPIOA, CS_PIN);

    ADS1299_init();
    // NVIC_EnableIRQ(GPIOA_INT_IRQn);
    ADS1299_start_conversions();

    /* Com5 */
    // use "XDS110 Class Application/User UART" COM port
    uint8_t data_uart[] = "Hello World\n";
    for (int i=0; i < sizeof(data_uart); i++) {
        DL_UART_transmitDataBlocking(UART_0_INST, data_uart[i]);
    }

    uint8_t index = 0;

    while (1) { 
        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            voltage = ADS1299_read_data_channel_2();
            
            UART_transmit_voltage(voltage);

            if (index == 128) {
                /* Remove offset */
                // int sum = 0;
                // for (uint8_t i = 0; i < 128; ++i) sum += voltages[i];
                // int average = sum / 128;
                // for (uint8_t i = 0; i < 128; ++i) voltages[i] -= average;
                index = 0;
            }
            voltages[index] = voltage;
            ++index;
        }
    }
}

// void GROUP1_IRQHandler(void) {
//     switch (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) {
//     }
// }

void delay_ms(int ms) {
    delay_cycles(ms * (24e6)/1000);
}