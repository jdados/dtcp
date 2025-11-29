#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"

void ADS_1299_init(void);
void ADS_1299_write_register(uint8_t reg_addr, uint8_t num_regs, uint8_t data);
void ADS_1299_read_register(void);