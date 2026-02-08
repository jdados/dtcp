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