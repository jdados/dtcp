/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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

#include "ti_msp_dl_config.h"
#include "ti/driverlib/dl_spi.h"
#include "ti/driverlib/dl_gpio.h"

int main(void) {
    // test comment (commit)

    // initializes SPI as well
    // (Clock polarity: 0, clock phase: 1)
    SYSCFG_DL_init();

    // DL_SPI_setChipSelect(SPI_0_INST, DL_SPI_CHIP_SELECT_0);

    while (1) { 
        /*
        uint8_t data = 0xFF;
        DL_SPI_transmitData8(SPI_0_INST, data);
        */

        // write to configuration register 1 (1 kSPS)
        uint8_t data_buffer[3] = {0x41, 0x00, 0b10010100};
        DL_GPIO_clearPins(GPIO_A_PORT, GPIO_A_CS_PIN);
        DL_SPI_transmitDataBlocking8(SPI_0_INST, data_buffer[0]);
        DL_SPI_transmitDataBlocking8(SPI_0_INST, data_buffer[1]);
        DL_SPI_transmitDataBlocking8(SPI_0_INST, data_buffer[2]);
        DL_GPIO_setPins(GPIO_A_PORT, GPIO_A_CS_PIN);

        //DL_GPIO_togglePins(GPIO_PORTA, GPIO_PORTA_RED_22_PIN);

        // pauses code execution
        __BKPT(0);
    }
}
