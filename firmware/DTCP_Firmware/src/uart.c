#include "../uart.h"

// void UART_init() {
//     DL_UART_Main_setClockConfig(UART0, &UART0_clock_config);
//     DL_UART_Main_init(UART0, &UART0_config);
//     DL_UART_Main_setOversampling(UART0, DL_UART_OVERSAMPLING_RATE_3X);
//     DL_UART_Main_setBaudRateDivisor(UART0, UART_0_IBRD_33_kHZ_9600_BAUD, UART_0_FBRD_33_kHZ_9600_BAUD);
//     DL_UART_Main_enable(UART0);
// }

// void UART_transmit_message(char* string, uint32_t size) {
//     for (uint32_t i = 0; i < size; ++i) {
//         DL_UART_transmitDataBlocking(UART0, string[i]);
//     }
// }

void UART_transmitString(char* str) {
    while (*str) {
        // Wait for TX FIFO to have space, then send
        DL_UART_Main_transmitDataBlocking(UART0, *str++);
    }
}

void UART_transmit_voltage_ascii(float voltage) {
        /* UART Transmission */
        char buffer[32];
        // Manual float to string conversion
        int intPart = (int)voltage;
        int fracPart = (int)((voltage - (float)intPart) * 100.0f);
        if (fracPart < 0) fracPart = -fracPart; 

        // Serial Plotter needs one value + newline to plot a single point
        snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
        UART_transmitString(buffer);
}

void UART_transmit_voltage_binary(float val) {
    // 1. Create a pointer to the float and treat it as a byte array
    uint8_t *ptr = (uint8_t *)&val;

    // DL_UART_Main_transmitDataBlocking(UART0, 0xAA); 


    // 2. Transmit each of the 4 bytes in the float
    for (int i = 0; i < sizeof(float); i++) {
        // DL_UART_Main_transmitDataBlocking sends 1 byte at a time
        DL_UART_Main_transmitDataBlocking(UART0, ptr[i]);
    }
}