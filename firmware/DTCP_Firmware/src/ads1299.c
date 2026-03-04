#include "../ads1299.h"

/* LSB with gain 24 */
const float LSB = 2.235e-8;
/* LSB with gain 1*/
// const float LSB = 5.364e-7;

/* don't use yet */
void SPI_init() {
    DL_SPI_setClockConfig(SPI0, &SPI_0_clock_config);
    DL_SPI_init(SPI0, &SPI_0_config);
    DL_SPI_setBitRateSerialClockDivider(SPI0, 5);
    DL_SPI_setFIFOThreshold(SPI0, DL_SPI_RX_FIFO_LEVEL_1_2_FULL, DL_SPI_TX_FIFO_LEVEL_1_2_EMPTY);
    // DL_SPI_setChipSelect(SPI_0_INST, DL_SPI_CHIP_SELECT_0);
    
    DL_SPI_enable(SPI0);
}

void ADS1299_init() {
	// SPI_init();
        // GPIO_A_RESET_PIN
        //DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_RESET_PIN);
        //delay_cycles(40);
        //DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_RESET_PIN);
        //delay_cycles(40);

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
        delay_ms(150);
        
        /* SDATAC (Stop Read Data Continuously mode) */
        ADS1299_transmit_cmd(SDATAC_cmd);

        /* Configure Registers */
        /* Config 1, Config 2, Config 3, LOFF (not used), CH1-CH4 */
        uint8_t config_data[] = {0b11010100, 0b11010000, 0b11111100, \
        0x00, 0b01100000, 0b11100001, 0x81, 0x81};

        ADS1299_write_registers(1, 8, config_data);
        delay_cycles(2e3);

        /* Working solution */
        // /* Write to CONFIG1  - CHN4 registers */
        // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        // DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 1);
        // DL_SPI_receiveData8(SPI_0_INST);
        // DL_SPI_transmitDataBlocking8(SPI0, 8 - 1);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* DAISY_EN = 1, CLK_EN = 0, Output data rate = 1 kSPS */
        // DL_SPI_transmitDataBlocking8(SPI0, 0b11010100);
        // // DL_SPI_transmitDataBlocking8(SPI0, 0x96);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* CONFIG 2*/
        // DL_SPI_transmitDataBlocking8(SPI0, 0b11010000);
        // // DL_SPI_transmitDataBlocking8(SPI0, 0xC0);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* CONFIG 3 */
        // // DL_SPI_transmitDataBlocking8(SPI0, 0xE0);
        // DL_SPI_transmitDataBlocking8(SPI0, 0b11111100);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* default values */
        // DL_SPI_transmitDataBlocking8(SPI0, 0x00);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* CH 1*/
        // DL_SPI_transmitDataBlocking8(SPI0, 0b01100000);
        // // DL_SPI_transmitDataBlocking8(SPI0, 0x01);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* CH 2*/
        // DL_SPI_transmitDataBlocking8(SPI0, 0b11100001);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* CH 3 */
        // DL_SPI_transmitDataBlocking8(SPI0, 0x81);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* CH 4 */
        // DL_SPI_transmitDataBlocking8(SPI0, 0x81);
        // DL_SPI_receiveData8(SPI_0_INST);
        // delay_cycles(50);
        // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        // delay_cycles(2e3);

        /* Bias driver registers */
        uint8_t bias_config_data[] = {0x01, 0x01};
        ADS1299_write_registers(0x0D, 2, bias_config_data);
        delay_cycles(2e3);

        // DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        // DL_SPI_transmitDataBlocking8(SPI0, 0x40 | 0x0D);
        // DL_SPI_receiveData8(SPI_0_INST);
        // DL_SPI_transmitDataBlocking8(SPI0, 2 - 1);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* Positive */
        // DL_SPI_transmitDataBlocking8(SPI0, 0x01);
        // DL_SPI_receiveData8(SPI_0_INST);
        // /* Negative */
        // DL_SPI_transmitDataBlocking8(SPI0, 0x00);
        // DL_SPI_receiveData8(SPI_0_INST);
        // delay_cycles(50);
        // DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        // delay_cycles(2e3);
}

/* Transmit a SPI command to ADS1299 */
void ADS1299_transmit_cmd(uint8_t cmd) {
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, cmd);
        DL_SPI_receiveData8(SPI_0_INST);
        delay_cycles(100);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
}

/* Write ADS1299 register(s) */
void ADS1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t *data) {
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x40 | reg_addr);
        DL_SPI_receiveData8(SPI_0_INST);
        DL_SPI_transmitDataBlocking8(SPI0, num_regs - 1);
        DL_SPI_receiveData8(SPI_0_INST);
        for (uint8_t i = 0; i < num_regs; ++i) {
                DL_SPI_transmitDataBlocking8(SPI0, data[i]);
                DL_SPI_receiveData8(SPI_0_INST);
        }
        delay_cycles(50);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
}

/* Read ADS1299 register(s) */
uint8_t ADS1299_read_registers(uint8_t reg_addr, uint8_t num_regs) {
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x20 | reg_addr);
        DL_SPI_receiveData8(SPI_0_INST);
        DL_SPI_transmitDataBlocking8(SPI0, num_regs - 1);
        DL_SPI_receiveData8(SPI_0_INST);
        DL_SPI_transmitDataBlocking8(SPI0, 0x00);
        uint8_t data = DL_SPI_receiveData8(SPI_0_INST);
        delay_cycles(50);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        return data;
}

/* Read conversion data from channel 1 */
float ADS1299_read_data() {
        uint8_t data[15];
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        // DL_SPI_transmitDataBlocking8(SPI0, RDATA_cmd);
        // DL_SPI_receiveData8(SPI_0_INST);
        for (uint8_t i = 0; i < 15; ++i) {
                DL_SPI_transmitDataBlocking8(SPI0, 0x00);
                data[i] = DL_SPI_receiveData8(SPI_0_INST);
        }
        delay_cycles(50);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);

        int32_t channel_1_data = ((int32_t)data[3] << 16) | ((int32_t)data[4] << 8) | ((int32_t)data[5]);
        /* sign extend */
        if (channel_1_data & 0x800000) channel_1_data |= 0xFF000000;
        float voltage = (float)channel_1_data * LSB * 1e3f;
        return voltage;
}

/* Start the data conversions */
void ADS1299_start_conversions() {
        ADS1299_transmit_cmd(START_cmd);
        /* Cannot read from or write to registers in this mode */
        ADS1299_transmit_cmd(RDATAC_cmd);
}

/* Stop the data conversions */
void ADS1299_stop_conversions() {

}