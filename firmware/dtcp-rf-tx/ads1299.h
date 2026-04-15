#ifndef ADS1299_H_
#define ADS1299_H_

#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
#include "ti_msp_dl_config.h"

/* SPI pins for the MCU (used to communicate with the AFE)
    CS (Select) - PA24
    SCLK (Clock) - PA11
    MOSI (PICO) - PA18
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

/* FIFO for holding samples */
#define FIFO_SIZE 32

typedef struct FIFO_t { 
    float buffer[FIFO_SIZE];
    /* read pointer */
    volatile uint16_t head;
    /* write pointer */
    volatile uint16_t tail;
    volatile uint16_t count;
} FIFO_t;

// void SPI_init(void);
void ADS1299_init(void);
void ADS1299_transmit_cmd(uint8_t cmd);
void ADS1299_write_registers(uint8_t reg_addr, uint8_t num_regs, uint8_t *data);
uint8_t ADS1299_read_registers(uint8_t reg_addr, uint8_t num_regs);
float ADS1299_read_data_channel_1(void);
float ADS1299_read_data_channel_2(void);
void ADS1299_start_conversions(void);
void ADS1299_stop_conversions(void);
extern void delay_ms(int ms);
void init_FIFO(FIFO_t *f);
bool write_FIFO(FIFO_t *f, float data);
bool read_FIFO(FIFO_t *f, float* data);

#endif /* ADS1299_H_ */