#include "../ads1299.h"

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


        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x06);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        delay_cycles(100);

        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x02);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        delay_cycles(100);

        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x11);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        delay_cycles(100);

        // ADS1299_write_registers(1, 1, 0b11011100);
        // delay_cycles(10);
}

void ADS1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t data) {
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x40 | reg_addr);
        DL_SPI_transmitDataBlocking8(SPI0, num_regs - 1);
        DL_SPI_transmitDataBlocking8(SPI0, data);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
}

uint8_t ADS1299_read_register(uint8_t reg_addr, uint8_t num_regs) {
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0x20);
        DL_SPI_transmitDataBlocking8(SPI0, 0);
        uint8_t data = DL_SPI_receiveDataBlocking8(SPI0);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        return data;
}

uint32_t ADS1299_read_data() {
        uint32_t data = 0;
        return data;
}
