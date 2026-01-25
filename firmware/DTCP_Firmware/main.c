
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
// #include "ti/driverlib/dl_uart.h"

#include "ads1299.h"
#include "uart.h"

/* small printf implementation */

int main(void) {
    // initializes all the modules
    // SPI Mode for ADS1299:
    // Clock polarity: 0, clock phase: 1
    SYSCFG_DL_init();
    // (GPIOA, CS_PIN);

    // DL_SPI_transmitDataBlocking8(SPI0, 0x00);

    /* Reset */
    // ADS1299_transmit_cmd(RESET_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, RESET_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(2e3);

    /* Wake up */
    // ADS1299_transmit_cmd(WAKEUP_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, WAKEUP_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(1e3);

    /* SDATAC (Stop Read Data Continuously mode) */
    // ADS1299_transmit_cmd(SDATAC_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, SDATAC_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(1e3);

    /* Write to CONFIG1  - CHN2 registers */
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 1);
    DL_SPI_transmitDataBlocking8(SPI0, 6 - 1);
    /* DAISY_EN = 1, CLK_EN = 0, Output data rate = 1 kSPS */
    // DL_SPI_transmitDataBlocking8(SPI0, 0b11011100);
    DL_SPI_transmitDataBlocking8(SPI0, 0x96);
    /* CONFIG 2*/
    // DL_SPI_transmitDataBlocking8(SPI0, 0b11000000);
    DL_SPI_transmitDataBlocking8(SPI0, 0xC0);
    /* CONFIG 3 */
    DL_SPI_transmitDataBlocking8(SPI0, 0xE0);
    /* default values */
    DL_SPI_transmitDataBlocking8(SPI0, 0x00);
    /* CH 1*/
    // DL_SPI_transmitDataBlocking8(SPI0, 0b01100000);
    DL_SPI_transmitDataBlocking8(SPI0, 0x01);
    /* CH 2*/
    DL_SPI_transmitDataBlocking8(SPI0, 0x01);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(2e3);

    /* Single-shot */
    // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 0x17);
    // DL_SPI_transmitDataBlocking8(SPI0, 0);
    // DL_SPI_transmitDataBlocking8(SPI0, 0b00001000);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // delay_cycles(15);

    /* Start the conversions */
    // ADS1299_transmit_cmd(START_cmd);
    // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // DL_SPI_transmitDataBlocking8(SPI0, START_cmd);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_START_PIN);
    delay_cycles(1e3);

    /* Cannot read from or write to registers in this mode */
    // ADS1299_transmit_cmd(RDATAC_cmd);
    // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // DL_SPI_transmitDataBlocking8(SPI0, RDATAC_cmd);
    // delay_cycles(1e3);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);

    while (1) { 

        // use "XDS110 Class Application/User UART" COM port

        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
            DL_SPI_transmitDataBlocking8(SPI0, RDATA_cmd);
            uint32_t data = DL_SPI_receiveDataBlocking32(SPI0);
            DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
            delay_cycles(20);
            /* Start the conversions */
        }

        // uint8_t data = ADS1299_read_registers(1, 1);
        // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        // DL_SPI_transmitDataBlocking8(SPI0, 0x20 | 0x02);
        // DL_SPI_transmitDataBlocking8(SPI0, 1 - 1);
        // uint8_t data = DL_SPI_receiveDataBlocking8(SPI0);
        // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    }
}


// static delay_ms(int ms) {

// }