
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

    // DL_SPI_setChipSelect(SPI_0_INST, DL_SPI_CHIP_SELECT_0);

    /* Reset */
    // ADS1299_transmit_cmd(RESET_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, RESET_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(20);

    /* Wake up */
    // ADS1299_transmit_cmd(WAKEUP_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, WAKEUP_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(5);

    /* SDATAC (Stop Read Data Continuously mode) */
    // ADS1299_transmit_cmd(SDATAC_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, SDATAC_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(5);

    /* Write to CONFIG1  - CHN2 registers */
    // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 1);
    // DL_SPI_transmitDataBlocking8(SPI0, 6 - 1);
    // /* DAISY_EN = 1, CLK_EN = 0, Output data rate = 1 kSPS */
    // // DL_SPI_transmitDataBlocking8(SPI0, 0b11011100);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x96);
    // /* CONFIG 2*/
    // // DL_SPI_transmitDataBlocking8(SPI0, 0b11000000);
    // DL_SPI_transmitDataBlocking8(SPI0, 0xC0);
    // /* CONFIG 3 */
    // DL_SPI_transmitDataBlocking8(SPI0, 0b01100000);
    // /* default values */
    // DL_SPI_transmitDataBlocking8(SPI0, 0x00);
    // /* CH 1*/
    // // DL_SPI_transmitDataBlocking8(SPI0, 0b01100000);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x01);
    // /* CH 2*/
    // DL_SPI_transmitDataBlocking8(SPI0, 0x01);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // delay_cycles(5);

    /* Single-shot */
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 0x17);
    DL_SPI_transmitDataBlocking8(SPI0, 0);
    DL_SPI_transmitDataBlocking8(SPI0, 0b00001000);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(15);

    /* Start the conversions */
    //ADS1299_transmit_cmd(START_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_START_PIN);
    delay_cycles(3);

    /* Cannot read from or write to registers in this mode */
    // ADS1299_transmit_cmd(RDATAC_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, RDATAC_cmd);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(8);

    while (1) { 

        // use "XDS110 Class Application/User UART" COM port
        
        /*
        uint32_t data[28] = {0};
        for (uint32_t i = 0; i < 28; ++i) {
            data[i] = DL_SPI_receiveDataBlocking32(SPI0);
        }
        */

        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
            uint32_t data = DL_SPI_receiveData32(SPI0);
            delay_cycles(20);
            /* Start the conversions */
            DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
            DL_SPI_transmitDataBlocking8(SPI0, START_cmd);
            DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
            delay_cycles(3);
        }

        uint8_t data = ADS1299_read_registers(1, 1);
        /*
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x20 | 1);
        DL_SPI_transmitDataBlocking8(SPI0, 1 - 1);
        uint8_t data = DL_SPI_receiveDataBlocking8(SPI0);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        */
    }
}
