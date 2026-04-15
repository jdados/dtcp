#include "ti/driverlib/dl_uart_main.h"
#include "ti/driverlib/dl_gpio.h"
#include <stdio.h>

// void UART_transmitString(char* str);
// void UART_transmit_voltage_ascii(float voltage);
void UART_transmit_voltage_binary(float val);