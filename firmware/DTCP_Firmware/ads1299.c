#include "ads1299.h"

void SPI_init() {

}

void ADS1299_init() {
	SPI_init();
}

void ADS_1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t data) {
        uint8_t data_buffer[3] = {reg_addr, num_regs - 1, data};
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
