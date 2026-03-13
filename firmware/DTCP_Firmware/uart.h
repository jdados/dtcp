#include "ti/driverlib/dl_uart_main.h"
#include "ti/driverlib/dl_gpio.h"
#include <stdio.h>

// use "XDS110 Class Application/User UART" COM port

// #define UART_0_INST                                                        UART0
// #define UART_0_INST_FREQUENCY                                              32768
// #define UART_0_INST_IRQHandler                                  UART0_IRQHandler
// #define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
// #define GPIO_UART_0_TX_PORT                                                GPIOA
// #define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_27
// #define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM28)
// #define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM28_PF_UART0_TX
// #define UART_0_BAUD_RATE                                                  (9600)
// #define UART_0_IBRD_33_kHZ_9600_BAUD                                         (1)
// #define UART_0_FBRD_33_kHZ_9600_BAUD                                         (9)

// static const DL_UART_Main_ClockConfig UART0_clock_config = {
//     .clockSel    = DL_UART_MAIN_CLOCK_LFCLK,
//     .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
// };

// static const DL_UART_Main_Config UART0_config = {
//     .mode        = DL_UART_MAIN_MODE_NORMAL,
//     .direction   = DL_UART_MAIN_DIRECTION_TX,
//     .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
//     .parity      = DL_UART_MAIN_PARITY_NONE,
//     .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
//     .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
// };

// void UART_init();
// void UART_transmit_message(char* string, uint32_t size);

void UART_transmitString(char* str);
void UART_transmit_voltage_ascii(float voltage);
void UART_transmit_voltage_binary(float val);