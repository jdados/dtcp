/*
 * Copyright (c) 2020, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include "ti_msp_dl_config.h"

// Array of floats
float dataArray[] = {0.0000, 0.7347, 1.1888, 1.1888, 0.7347, 0.0000, -0.7347, -1.1888, -1.1888, -0.7347, -0.0000, 0.7347, 1.1888, 1.1888, 0.7347, 0.0000, -0.7347, -1.1888, -1.1888, -0.7347, -0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347, -0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347, -0.0000, 0.7347, 1.1888, 1.1888, 0.7347, 0.0000, -0.7347, -1.1888, -1.1888, -0.7347, 0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347, 0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347, 0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347, -0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347, 0.0000, 0.7347, 1.1888, 1.1888, 0.7347, -0.0000, -0.7347, -1.1888, -1.1888, -0.7347}; 

#define ARRAY_SIZE (sizeof(dataArray) / sizeof(dataArray[0]))

volatile uint8_t gCurrentIndex = 0; // Tracks which element to send next
volatile uint8_t gTxState = 0; // 0: Header, 1-4: Float Bytes
const uint8_t HEADER_BYTE = 0xAA;

void UART_transmitString(char* str) {
    while (*str) {
        // Wait for TX FIFO to have space, then send
        DL_UART_Main_transmitDataBlocking(UART_0_INST, *str++);
    }
}

// void transmitFloatArray() {
//     char buffer[32];
//     for (int i = 0; i < ARRAY_SIZE; i++) {
//         float val = dataArray[i];
        
//         // Handle negative numbers
//         if (val < 0) {
//             UART_transmitString("-");
//             val = -val;
//         }

//         int intPart = (int)val;
//         int fracPart = (int)((val - intPart) * 100); // 2 decimal places

//         // Format into buffer: "12.34\r\n"
//         sprintf(buffer, "%d.%02d\r\n", intPart, fracPart);
//         UART_transmitString(buffer);
//     }
// }

// void transmitFloatArrayPlotter() {
//     char buffer[32];
//     for (int i = 0; i < ARRAY_SIZE; i++) {
//         float val = dataArray[i];
        
//         // Manual float formatting
//         int intPart = (int)val;
//         int fracPart = (int)((val - (float)intPart) * 100.0f);
//         if (fracPart < 0) fracPart = -fracPart; // Ensure decimal is positive

//         // Format: "Value," for first elements, "Value\r\n" for the last one
//         // if (i < ARRAY_SIZE - 1) {
//         //     snprintf(buffer, sizeof(buffer), "%d.%02d,", intPart, fracPart);
//         // } else {
//         //     snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
//         // }

//         snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
        
//         UART_transmitString(buffer);
//     }
// }

// void transmitNextValue() {
//     char buffer[32];
//     float val = dataArray[gCurrentIndex];

//     // Manual float to string conversion
//     int intPart = (int)val;
//     int fracPart = (int)((val - (float)intPart) * 100.0f);
//     if (fracPart < 0) fracPart = -fracPart; 

//     // Serial Plotter needs one value + newline to plot a single point
//     snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
//     UART_transmitString(buffer);

//     // Increment index and wrap around to the start of the array
//     gCurrentIndex++;
//     if (gCurrentIndex >= ARRAY_SIZE) {
//         gCurrentIndex = 0;
//     }
// }

void transmitFloat(float val) {
    // 1. Handle negative sign
    if (val < 0) {
        DL_UART_Main_transmitDataBlocking(UART_0_INST, '-');
        val = -val;
    }

    // 2. Transmit integer part
    int intPart = (int)val;
    DL_UART_Main_transmitDataBlocking(UART_0_INST, (intPart + '0'));

    // 3. Transmit decimal point
    DL_UART_Main_transmitDataBlocking(UART_0_INST, '.');

    // 4. Transmit fractional part (2 decimal places)
    int fracPart = (int)((val - (float)intPart) * 100.0f + 0.5f); // +0.5 for rounding
    DL_UART_Main_transmitDataBlocking(UART_0_INST, (fracPart / 10) + '0');
    DL_UART_Main_transmitDataBlocking(UART_0_INST, (fracPart % 10) + '0');

    // 5. Newline for Plotter
    DL_UART_Main_transmitDataBlocking(UART_0_INST, '\r');
    DL_UART_Main_transmitDataBlocking(UART_0_INST, '\n');
}

void transmitFloatBinary(float val) {
    // 1. Create a pointer to the float and treat it as a byte array
    uint8_t *ptr = (uint8_t *)&val;

    // 2. Send Frame Start (many tools use 0xABCD or 0xAA)
    DL_UART_Main_transmitDataBlocking(UART_0_INST, 0xAA); 

    // 3. Transmit each of the 4 bytes in the float
    for (int i = 0; i < sizeof(float); i++) {
        // DL_UART_Main_transmitDataBlocking sends 1 byte at a time
        DL_UART_Main_transmitDataBlocking(UART_0_INST, ptr[i]);
    }
}

// Update your loop to use this:
void transmitNextValue() {
    transmitFloatBinary(dataArray[gCurrentIndex]);
    gCurrentIndex = (gCurrentIndex + 1) % ARRAY_SIZE;
}

volatile uint8_t byteCount = 1; // Start at 1 because we manually sent byte 0

void UART_0_INST_IRQHandler(void) {
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_TX:
            
            float val = dataArray[gCurrentIndex];
            uint8_t *ptr = (uint8_t *)&val;

            if (gTxState == 0) {
                // State 0: Send Header
                DL_UART_Main_transmitData(UART_0_INST, HEADER_BYTE);
                gTxState = 1;
            } 
            else if (gTxState <= 4) {
                // State 1-4: Send the 4 bytes of the float
                // ptr[0] for state 1, ptr[1] for state 2, etc.
                DL_UART_Main_transmitData(UART_0_INST, ptr[gTxState - 1]);
                gTxState++;
                
                // If we just sent the last byte (state 4), reset for the next float
                if (gTxState > 4) {
                    gTxState = 0;
                    gCurrentIndex = (gCurrentIndex + 1) % ARRAY_SIZE;
                }
            }
            break;
            
        default:
            break;
    }
}

int main(void) {
    SYSCFG_DL_init();

    // Enable UART Interrupts in NVIC
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);

    // START: Manually send the very first header to kick off the ISR
    DL_UART_Main_transmitData(UART_0_INST, HEADER_BYTE);
    gTxState = 1; // Next interrupt should send the first byte of the float
    
    // Transmit the whole array once
    // transmitFloatArray();

    while (1) {
        // transmitFloatArrayPlotter(); // Plot the array repeatedly
        // transmitNextValue(); 

        // DL_Common_delayCycles(32000000); // Delay to plotter does not move too fast.
        __WFI();
    }
}
