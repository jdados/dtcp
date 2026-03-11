#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti/driverlib/dl_spi.h"


/* pins on the board (invalid)
    CS (Select) - PA23
    SCLK (Clock) - PA11
    MOSI (PICO) - PA18/A7
    MISO (POCI) - PA16
*/

#define CS_PIN DL_GPIO_PIN_24

#define READ_REG_ADDR_OFFSET 0x20
#define WRITE_REG_ADDR_OFFSET 0x40

/* SPI System Commands */
#define WAKEUP_cmd 0x02
#define STANDBY_cmd 0x04
#define RESET_cmd 0x06
#define START_cmd 0x08
#define STOP_cmd 0x0A

/* SPI Data Read Commands */
#define RDATAC_cmd 0x10
#define SDATAC_cmd 0x11
#define RDATA_cmd 0x12

#define V_REF 4.5f
#define GAIN 24

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
void ADS1299_init(void);
void ADS1299_transmit_cmd(uint8_t cmd);
void ADS1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t *data);
uint8_t ADS1299_read_registers(uint8_t reg_addr, uint8_t num_regs);
float ADS1299_read_data(void);
float ADS1299_read_data_channel_2();
void ADS1299_start_conversions(void);
void ADS1299_stop_conversions(void);
extern void delay_ms(int ms);