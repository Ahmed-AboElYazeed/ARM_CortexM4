#ifndef RCC_H
#define RCC_H

//#include "std_bitUtillity.h"



// Defiene this macro to disable previous clock source after switching
#define RCC_DESABEL_AFTER_SWITCH

typedef struct
{
    uint32_t pllSource;
    uint32_t pllM;
    uint32_t pllN;
    uint32_t pllP;
    uint32_t pllQ;
}pllCongfig_t;

typedef enum
{
    Rcc_clk_disable = 0,
    Rcc_clk_enable = 1
}Rcc_clkState_t;

typedef enum
{
    HSI_CLK = 0,
    HSE_CLK = 1,
    PLL_CLK = 2,
    INVALID_CLK = 0xFFFFFFFF
}Rcc_clkSource_t;

/* Rcc function headers*/

void Rcc_getSystemClk(Rcc_clkSource_t* clkSource);
void Rcc_setSystemClk(Rcc_clkSource_t clkSource);
void Rcc_ctrlClk(uint32_t clk, uint8_t state);

void Rcc_enablePeripheralClk(uint32_t peripheral);
void Rcc_disablePeripheralClk(uint32_t peripheral);
void Rcc_setBusPrescaler(uint32_t bus, uint32_t prescaler);

void Rcc_PllConfig(pllCongfig_t* pllConfig);

void Rcc_init(void);
void Rcc_setConfig(void);


#endif