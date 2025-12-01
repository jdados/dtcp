#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"

#define CS_PIN DL_GPIO_PIN_23
#define READ_REG_ADDR_OFFSET 0x20
#define WRITE_REG_ADDR_OFFSET 0x40

static const DL_SPI_Config SPI_0_config = {
    .mode        = DL_SPI_MODE_CONTROLLER,
    .frameFormat = DL_SPI_FRAME_FORMAT_MOTO3_POL0_PHA1,
    .parity      = DL_SPI_PARITY_NONE,
    .dataSize    = DL_SPI_DATA_SIZE_8,
    .bitOrder    = DL_SPI_BIT_ORDER_MSB_FIRST,
};

static const DL_SPI_ClockConfig SPI_0_clock_config = {
    .clockSel    = DL_SPI_CLOCK_BUSCLK,
    .divideRatio = DL_SPI_CLOCK_DIVIDE_RATIO_1
};

void SPI_init(void);
void ADS_1299_init(void);
void ADS_1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t data);
uint32_t ADS_1299_read_register(void);
uint32_t ADS1299_read_data(void);