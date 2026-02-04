
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
// #include "ti/driverlib/dl_uart.h"

#include "ads1299.h"
#include "uart.h"

float voltage;
/* small printf implementation */

int main(void) {
    delay_cycles(10e3);

    // initializes all the modules
    // SPI Mode for ADS1299:
    // Clock polarity: 0, clock phase: 1
    SYSCFG_DL_init();
    // (GPIOA, CS_PIN);

    /* dummy */
    // DL_SPI_transmitDataBlocking8(SPI0, 0x00);
    // DL_SPI_receiveData8(SPI_0_INST);

    /* Reset */
    // ADS1299_transmit_cmd(RESET_cmd);
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, RESET_cmd);
    DL_SPI_receiveData8(SPI_0_INST);
    delay_cycles(1e6);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);

    /* Wake up */
    ADS1299_transmit_cmd(WAKEUP_cmd);

    /* SDATAC (Stop Read Data Continuously mode) */
    ADS1299_transmit_cmd(SDATAC_cmd);

    /* Write to CONFIG1  - CHN4 registers */
    DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 1);
    DL_SPI_receiveData8(SPI_0_INST);
    DL_SPI_transmitDataBlocking8(SPI0, 8 - 1);
    DL_SPI_receiveData8(SPI_0_INST);
    /* DAISY_EN = 1, CLK_EN = 0, Output data rate = 1 kSPS */
    DL_SPI_transmitDataBlocking8(SPI0, 0b11010100);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x96);
    DL_SPI_receiveData8(SPI_0_INST);
    /* CONFIG 2*/
    DL_SPI_transmitDataBlocking8(SPI0, 0b11010000);
    // DL_SPI_transmitDataBlocking8(SPI0, 0xC0);
    DL_SPI_receiveData8(SPI_0_INST);
    /* CONFIG 3 */
    DL_SPI_transmitDataBlocking8(SPI0, 0xE0);
    // DL_SPI_transmitDataBlocking8(SPI0, 0b11111000);
    DL_SPI_receiveData8(SPI_0_INST);
    /* default values */
    DL_SPI_transmitDataBlocking8(SPI0, 0x00);
    DL_SPI_receiveData8(SPI_0_INST);
    /* CH 1*/
    DL_SPI_transmitDataBlocking8(SPI0, 0b01100101);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x01);
    DL_SPI_receiveData8(SPI_0_INST);
    /* CH 2*/
    DL_SPI_transmitDataBlocking8(SPI0, 0b11100001);
    DL_SPI_receiveData8(SPI_0_INST);
    /* CH 3 */
    DL_SPI_transmitDataBlocking8(SPI0, 0x81);
    DL_SPI_receiveData8(SPI_0_INST);
    /* CH 4 */
    DL_SPI_transmitDataBlocking8(SPI0, 0x81);
    DL_SPI_receiveData8(SPI_0_INST);
    delay_cycles(50);
    DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    delay_cycles(2e3);

    /* Single-shot */
    // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 0x17);
    // DL_SPI_receiveData8(SPI_0_INST);
    // DL_SPI_transmitDataBlocking8(SPI0, 0);
    // DL_SPI_receiveData8(SPI_0_INST);
    // DL_SPI_transmitDataBlocking8(SPI0, 0b00001000);
    // DL_SPI_receiveData8(SPI_0_INST);
    // delay_cycles(50);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // delay_cycles(15);

    /* Start the conversions */
    ADS1299_transmit_cmd(START_cmd);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_START_PIN);
    // delay_cycles(15);

    // __BKPT(0);
    /* Cannot read from or write to registers in this mode */
    ADS1299_transmit_cmd(RDATAC_cmd);
    // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
    // DL_SPI_transmitDataBlocking8(SPI0, RDATAC_cmd);
    // delay_cycles(1e3);
    // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);

    // int32_t channel_1_data[10] = {};
    int32_t channel_1_data = 0;
    // float voltage[10] = {};
    voltage = 0;
    // uint8_t index = 0;
    uint8_t data[15];
    /* LSB with gain 24 */
    const float LSB = 2.235e-8;
    /* LSB with gain 1*/
    // const float LSB = 5.364e-7;

    while (1) { 
        // uint8_t data = ADS1299_read_registers(1, 1);
        // uint8_t data_2 = ADS1299_read_registers(2, 1);
        // __BKPT(0);

        // use "XDS110 Class Application/User UART" COM port

        uint8_t val = 0;
        val = DL_GPIO_readPins(GPIO_A_PORT, GPIO_A_DRDY_PIN);
        if (val == 0) {
            DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
            // DL_SPI_transmitDataBlocking8(SPI0, RDATA_cmd);
            // DL_SPI_receiveData8(SPI_0_INST);
            for (uint8_t i = 0; i < 15; ++i) {
                DL_SPI_transmitDataBlocking8(SPI0, 0x00);
                data[i] = DL_SPI_receiveData8(SPI_0_INST);
            }
            delay_cycles(50);
            DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);

            // if (index == 10) index = 0; 
            // channel_1_data[index] = ((int32_t)data[3] << 16) | ((int32_t)data[4] << 8) | ((int32_t)data[5]);
            channel_1_data = ((int32_t)data[3] << 16) | ((int32_t)data[4] << 8) | ((int32_t)data[5]);
            /* sign extend */
            // if (channel_1_data[index] & 0x800000) channel_1_data[index] |= 0xFF000000;
            if (channel_1_data & 0x800000) channel_1_data |= 0xFF000000;
            // if (channel_1_data[index] & 0x800000) channel_1_data[index] -= 0x1000000;
            // channel_1_data[index] = channel_1_data[index] * 4.5 / (2e23 * 1);
            // channel_1_data[index] = (channel_1_data[index] - 0x800000) / (4.5 / (2e23 - 1));
            // channel_1_data[index] = channel_1_data[index] * 4.5 / (2e23 - 1);
            // voltage[index] = (float)channel_1_data[index] * LSB * 1e3f;
            voltage = (float)channel_1_data * LSB * 1e3f;
            // ++index;
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