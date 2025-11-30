#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"

#define CS_PIN DL_GPIO_PIN_23

void SPI_init(void);
void ADS_1299_init(void);
void ADS_1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t data);
uint32_t ADS_1299_read_register(void);
uint32_t ADS1299_read_data(void);