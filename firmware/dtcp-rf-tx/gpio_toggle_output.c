#include "ti_msp_dl_config.h"
#include <math.h>

/* This results in approximately 0.5s of delay assuming 24MHz CPU_CLK */
#define DDS_SYSCLK_FREQ (100000000)
#define MCU_CLK_FREQ (24000000)
#define DDS_WCLK_FREQ (1000000)
#define DDS_WCLK_T_US (10)

/* Wrapper API */
void wait_us(uint32_t t){
    delay_cycles((MCU_CLK_FREQ/1000000)*t);
}

void pin_init(){
    //DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN | DDS_FQ_UD_PIN | DDS_RST_PIN);
    DL_GPIO_setPins(DDS_PORT, DDS_DDS_EN_PIN);
    //DL_GPIO_clearPins(PA_PORT, PA_EN_PIN);
}

void dds_reset(){
    /*Pulse RST for at least 5 clock cycles*/
    DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN);
    DL_GPIO_setPins(DDS_PORT, DDS_RST_PIN);
    wait_us(DDS_WCLK_T_US/2);

    for(int i = 0; i < 10; i++){
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
    }

    DL_GPIO_clearPins(DDS_PORT, DDS_RST_PIN);
}

void dds_serial_load_en(){
    /* Set W[2:0] to 011 */
    // DL_GPIO_setPins(DDS_PORT, DDS_D0_PIN | DDS_D1_PIN);
    // DL_GPIO_clearPins(DDS_PORT, DDS_D2_PIN);
    // wait_us(DDS_WCLK_T_US*10);

    /* Pulse WCLK */
    DL_GPIO_setPins(DDS_PORT, DDS_WCLK_PIN);
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN);
    wait_us(DDS_WCLK_T_US*4);


    /* Pulse FQ_UD */
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_setPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_clearPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
}

void dds_serial_data_tx(uint32_t dword){
    /* Send the frequency info */
    uint32_t dword_temp = dword;
    for(int i = 0; i < 32; i++){
        /* Setting W0-W31 */
        if((dword_temp & 0x1) == 0x1){
            DL_GPIO_setPins(DDS_PORT, DDS_D7_PIN);
        } else {
            DL_GPIO_clearPins(DDS_PORT, DDS_D7_PIN);
        }

        /* Clock toggling */
        if(i == 0){
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_setPins(DDS_PORT, DDS_WCLK_PIN);
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_clearPins(DDS_PORT, DDS_WCLK_PIN);
        } else {
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
            wait_us(DDS_WCLK_T_US/2);
            DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
        }

        /* Look at the next bit */
        dword_temp = dword_temp>>1;
    }

    /* W32 and W33 are control bits, always set to 0 */
    /* The rest of the bits should be 0 too */
    DL_GPIO_clearPins(DDS_PORT, DDS_D7_PIN);
    for(int i = 0; i < 8; i++){
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
        wait_us(DDS_WCLK_T_US/2);
        DL_GPIO_togglePins(DDS_PORT, DDS_WCLK_PIN);
    }

    wait_us(DDS_WCLK_T_US);
    /*Pulse FQ_UD at the end */
    DL_GPIO_setPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
    DL_GPIO_clearPins(DDS_PORT, DDS_FREQ_UPD_PIN);
    wait_us(DDS_WCLK_T_US);
}

#define F_OUT_DDS 25000000

int main(void)
{
    /* Power on GPIO, initialize pins as digital outputs */
    SYSCFG_DL_init();

    /* Initialize the GPIO for the DDS interface */
    pin_init();
    
    DL_GPIO_setPins(DDS_PORT, DDS_DDS_EN_PIN);
    /* Reset the DDS */
    //dds_reset();

    /* Initialize DDS in serial mode */
    dds_serial_load_en();

    /* Calculate the DDS output frequency */
    double f_ratio = (double)F_OUT_DDS/(double)DDS_SYSCLK_FREQ;
    uint32_t freq_dword = (uint32_t)(f_ratio*pow(2,32));
    
    dds_serial_data_tx(freq_dword);
    // DL_GPIO_clearPins(DDS_PORT, DDS_DDS_EN_PIN);
    // wait_us(10000);
    
    // wait_us(10000000);
    // DL_GPIO_clearPins(DDS_PORT, DDS_DDS_EN_PIN);
    // wait_us(10000000);
    // DL_GPIO_setPins(DDS_PORT, DDS_DDS_EN_PIN);
    //DL_GPIO_setPins(PA_PORT, PA_EN_PIN);
    while (1) {
        // DL_GPIO_setPins(PA_PORT, PA_EN_PIN);
        // dds_serial_data_tx(freq_dword);
        // wait_us(10000);
        // dds_reset();
        // DL_GPIO_clearPins(PA_PORT, PA_EN_PIN);
        // wait_us(990000);
    }
}
