
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"

#include "ads1299.h"
#include "uart.h"

volatile float voltage;
float voltages[128];
/* small printf implementation */

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

    uint8_t index = 0;

    while (1) { 
        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            voltage = ADS1299_read_data();

            // if (voltage > 1.0f) {
            //     delay_ms(55);

            // }
            
            UART_transmit_voltage_binary(voltage);

            if (index == 128) {
                /* Remove offset */
                // int sum = 0;
                // for (uint8_t i = 0; i < 128; ++i) sum += voltages[i];
                // int average = sum / 128;
                // for (uint8_t i = 0; i < 128; ++i) voltages[i] -= average;
                index = 0;
            }
            // voltages[index] = voltage;
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