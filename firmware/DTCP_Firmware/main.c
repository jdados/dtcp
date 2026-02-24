
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
// #include "ti/driverlib/dl_uart.h"

#include "ads1299.h"
#include "uart.h"

float voltage;
float voltages[128];
/* small printf implementation */

int main(void) {
    delay_cycles(10e3);

    // initializes all the modules
    // SPI Mode for ADS1299:
    // Clock polarity: 0, clock phase: 1
    SYSCFG_DL_init();
    // (GPIOA, CS_PIN);

    ADS1299_init();

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
            voltage = ADS1299_read_data();
            if (index == 128) index = 0;
            voltages[index] = voltage;
            ++index;
        }
    }
}


// static delay_ms(int ms) {

// }