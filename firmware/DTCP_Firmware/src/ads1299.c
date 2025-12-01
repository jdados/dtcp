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
	SPI_init();
}

void ADS_1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t data) {
        uint8_t data_buffer[3] = {WRITE_REG_ADDR_OFFSET | reg_addr, num_regs - 1, data};
        DL_GPIO_clearPins(GPIOA, CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, data_buffer[0]);
        DL_SPI_transmitDataBlocking8(SPI0, data_buffer[1]);
        DL_SPI_transmitDataBlocking8(SPI0, data_buffer[2]);
        DL_GPIO_setPins(GPIOA, CS_PIN);
}

uint32_t ADS1299_read_register(void) {
        uint32_t data = 0;
        return data;
}

uint32_t ADS1299_read_data() {
        uint32_t data = 0;
        return data;
}
