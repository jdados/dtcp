/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0C110X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0C110X
#define CONFIG_MSPM0C1104

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     24000000



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           24000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_27
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM28)
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM28_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_24_MHZ_115200_BAUD                                      (13)
#define UART_0_FBRD_24_MHZ_115200_BAUD                                       (1)




/* Defines for SPI_0 */
#define SPI_0_INST                                                         SPI0
#define SPI_0_INST_IRQHandler                                   SPI0_IRQHandler
#define SPI_0_INST_INT_IRQN                                       SPI0_INT_IRQn
#define GPIO_SPI_0_PICO_PORT                                              GPIOA
#define GPIO_SPI_0_PICO_PIN                                      DL_GPIO_PIN_18
#define GPIO_SPI_0_IOMUX_PICO                                   (IOMUX_PINCM19)
#define GPIO_SPI_0_IOMUX_PICO_FUNC                   IOMUX_PINCM19_PF_SPI0_PICO
#define GPIO_SPI_0_POCI_PORT                                              GPIOA
#define GPIO_SPI_0_POCI_PIN                                       DL_GPIO_PIN_4
#define GPIO_SPI_0_IOMUX_POCI                                    (IOMUX_PINCM5)
#define GPIO_SPI_0_IOMUX_POCI_FUNC                    IOMUX_PINCM5_PF_SPI0_POCI
/* GPIO configuration for SPI_0 */
#define GPIO_SPI_0_SCLK_PORT                                              GPIOA
#define GPIO_SPI_0_SCLK_PIN                                      DL_GPIO_PIN_11
#define GPIO_SPI_0_IOMUX_SCLK                                   (IOMUX_PINCM12)
#define GPIO_SPI_0_IOMUX_SCLK_FUNC                   IOMUX_PINCM12_PF_SPI0_SCLK



/* Port definition for Pin Group GPIO_A */
#define GPIO_A_PORT                                                      (GPIOA)

/* Defines for RED_22: GPIOA.22 with pinCMx 23 on package pin 17 */
#define GPIO_A_RED_22_PIN                                       (DL_GPIO_PIN_22)
#define GPIO_A_RED_22_IOMUX                                      (IOMUX_PINCM23)
/* Defines for CS: GPIOA.24 with pinCMx 25 on package pin 19 */
#define GPIO_A_CS_PIN                                           (DL_GPIO_PIN_24)
#define GPIO_A_CS_IOMUX                                          (IOMUX_PINCM25)
/* Defines for DRDY: GPIOA.2 with pinCMx 3 on package pin 8 */
#define GPIO_A_DRDY_PIN                                          (DL_GPIO_PIN_2)
#define GPIO_A_DRDY_IOMUX                                         (IOMUX_PINCM3)
/* Defines for PWDN: GPIOA.23 with pinCMx 24 on package pin 18 */
#define GPIO_A_PWDN_PIN                                         (DL_GPIO_PIN_23)
#define GPIO_A_PWDN_IOMUX                                        (IOMUX_PINCM24)
/* Defines for START: GPIOA.17 with pinCMx 18 on package pin 13 */
#define GPIO_A_START_PIN                                        (DL_GPIO_PIN_17)
#define GPIO_A_START_IOMUX                                       (IOMUX_PINCM18)
/* Defines for RESET: GPIOA.28 with pinCMx 29 on package pin 3 */
#define GPIO_A_RESET_PIN                                        (DL_GPIO_PIN_28)
#define GPIO_A_RESET_IOMUX                                       (IOMUX_PINCM29)


/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI_0_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
