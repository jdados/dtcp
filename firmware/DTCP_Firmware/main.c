
#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"
// #include "ti/driverlib/dl_uart.h"

#include "ads1299.h"
#include "uart.h"

int main(void) {
    // test comment (commit)

    // initializes all the modules
    // SPI Mode for ADS1299:
    // Clock polarity: 0, clock phase: 1
    SYSCFG_DL_init();
    // (GPIOA, CS_PIN);

    // DL_SPI_setChipSelect(SPI_0_INST, DL_SPI_CHIP_SELECT_0);

    while (1) { 
        /*
        uint8_t data = 0xFF;
        DL_SPI_transmitData8(SPI_0_INST, data);
        */

        // write to configuration register 1 (1 kSPS)
        /*
        uint8_t data_buffer[3] = {0x41, 0x00, 0b10010100};
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI_0_INST, data_buffer[0]);
        DL_SPI_transmitDataBlocking8(SPI_0_INST, data_buffer[1]);
        DL_SPI_transmitDataBlocking8(SPI_0_INST, data_buffer[2]);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        */

        // use "XDS110 Class Application/User UART" COM port
        // uint8_t byte = 'A';
       //  DL_UART_transmitDataBlocking(UART_0_INST, byte);
        // ADS_1299_write_registers(1, 1, 0b10010100);
        // pauses code execution
        // __BKPT(0);
        //DL_GPIO_togglePins(GPIO_PORTA, GPIO_PORTA_RED_22_PIN);

        // char string[] = "Hello, World!\n";
        // UART_transmit_message(string, 15);
        // pauses code execution
        // __BKPT(0);

        /* read ID */
        uint8_t id = 0;
        // uint8_t data_buffer[2] = {0x20, 0};
        DL_GPIO_clearPins(GPIOA, CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI0, 0b10101010);
        DL_SPI_transmitDataBlocking8(SPI0, 0b01010101);
        id = DL_SPI_receiveDataBlocking8(SPI0);
        DL_GPIO_setPins(GPIOA, CS_PIN);
        // __BKPT(0);
        // printf("Received id: %x", id);
    }
}
