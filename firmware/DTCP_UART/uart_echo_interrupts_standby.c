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
float dataArray[] = {12.34f, 56.78f, 90.12f, -5.67f}; 
#define ARRAY_SIZE (sizeof(dataArray) / sizeof(dataArray[0]))

uint8_t gCurrentIndex = 0; // Tracks which element to send next

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

void transmitFloatArrayPlotter() {
    char buffer[32];
    for (int i = 0; i < ARRAY_SIZE; i++) {
        float val = dataArray[i];
        
        // Manual float formatting
        int intPart = (int)val;
        int fracPart = (int)((val - (float)intPart) * 100.0f);
        if (fracPart < 0) fracPart = -fracPart; // Ensure decimal is positive

        // Format: "Value," for first elements, "Value\r\n" for the last one
        // if (i < ARRAY_SIZE - 1) {
        //     snprintf(buffer, sizeof(buffer), "%d.%02d,", intPart, fracPart);
        // } else {
        //     snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
        // }

        snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
        
        UART_transmitString(buffer);
    }
}

void transmitNextValue() {
    char buffer[32];
    float val = dataArray[gCurrentIndex];

    // Manual float to string conversion
    int intPart = (int)val;
    int fracPart = (int)((val - (float)intPart) * 100.0f);
    if (fracPart < 0) fracPart = -fracPart; 

    // Serial Plotter needs one value + newline to plot a single point
    snprintf(buffer, sizeof(buffer), "%d.%02d\r\n", intPart, fracPart);
    UART_transmitString(buffer);

    // Increment index and wrap around to the start of the array
    gCurrentIndex++;
    if (gCurrentIndex >= ARRAY_SIZE) {
        gCurrentIndex = 0;
    }
}

int main(void) {
    SYSCFG_DL_init();
    
    // Transmit the whole array once
    // transmitFloatArray();

    while (1) {
        // transmitFloatArrayPlotter(); // Plot the array repeatedly
        transmitNextValue(); 

        // DL_Common_delayCycles(32000000); // Delay to plotter does not move too fast.
        //__WFI();
    }
}
