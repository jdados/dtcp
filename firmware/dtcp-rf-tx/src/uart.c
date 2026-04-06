#include "../uart.h"

void UART_transmit_voltage_binary(float val) {
    // 1. Create a pointer to the float and treat it as a byte array
    uint8_t *ptr = (uint8_t *)&val;

    // 2. Header Byte to indicate start 
    DL_UART_Main_transmitDataBlocking(UART0, 0xAA); 

    // 3. Transmit each of the 4 bytes in the float
    for (int i = 0; i < sizeof(float); ++i) {
        // DL_UART_Main_transmitDataBlocking sends 1 byte at a time
        DL_UART_Main_transmitDataBlocking(UART0, ptr[i]);
    }
}