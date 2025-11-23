#ifndef RCC_H
#define RCC_H

//#include "std_bitUtillity.h"



// Defiene this macro to disable previous clock source after switching
#define RCC_HSI_UNUSED_DESABEL

// ERROR enum
// typedef enum 
// {
//     Rcc_enuAllGood,
//     Rcc_enuPll_P_err,
//     Rcc_enuPll_N_err

// }Err_flag_t;

// typedef enum
// {
//     Rcc_clk_disable = 0,
//     Rcc_clk_enable = 1
// }Rcc_clkState_t;

typedef enum
{
    HSI_CLK = 0,
    HSE_CLK = 1,
    PLL_CLK = 2,
    INVALID_CLK = 0xFFFF
}Rcc_clkSource_t;

typedef struct
{
    Rcc_clkSource_t pllSource;
    uint32_t pllM;
    uint32_t pllN;
    uint32_t pllP;
    uint32_t pllQ;
}pllCongfig_t;

typedef struct
{
    Rcc_clkSource_t systemClkSource;
    pllCongfig_t pllCfg;
}Rcc_cfg_t;


typedef enum{
    Rcc_GPIOA = ((uint64_t)0b0001 << 32)  |  (0b1 << 0),
    //                      ^bus identity        ^ Peripheral bit number in Rcc regesters
    //                   0001 ->  AHB1         0 : 31 
    //                   0010 ->  AHB2
    //                   0100 ->  APB1
    //                   1000 ->  APB2
    Rcc_GPIOB = ((uint64_t)0b0001 << 32)  |  (0b1 << 1),
    Rcc_GPIOC = ((uint64_t)0b0001 << 32)  |  (0b1 << 2),
    Rcc_GPIOD = ((uint64_t)0b0001 << 32)  |  (0b1 << 3),
    Rcc_GPIOE = ((uint64_t)0b0001 << 32)  |  (0b1 << 4),
    Rcc_GPIOH = ((uint64_t)0b0001 << 32)  |  (0b1 << 7),
    Rcc_CRC   = ((uint64_t)0b0001 << 32)  |  (0b1 << 12),
    Rcc_DMA1  = ((uint64_t)0b0001 << 32)  |  (0b1 << 21),
    Rcc_DMA2  = ((uint64_t)0b0001 << 32)  |  (0b1 << 22),

    // AHB2    
    Rcc_OTGFS = ((uint64_t)0b0010 << 32)  |  (0b1 << 7),

    // APB1   
    Rcc_TIM2  = ((uint64_t)0b0100 << 32)  |  (0b1 << 0),
    Rcc_TIM3  = ((uint64_t)0b0100 << 32)  |  (0b1 << 1),
    Rcc_TIM4  = ((uint64_t)0b0100 << 32)  |  (0b1 << 2),
    Rcc_TIM5  = ((uint64_t)0b0100 << 32)  |  (0b1 << 3),
    Rcc_WWDG  = ((uint64_t)0b0100 << 32)  |  (0b1 << 11),
    Rcc_SPI2  = ((uint64_t)0b0100 << 32)  |  (0b1 << 14),
    Rcc_SPI3  = ((uint64_t)0b0100 << 32)  |  (0b1 << 15),
    Rcc_USART2= ((uint64_t)0b0100 << 32)  |  (0b1 << 17),
    Rcc_I2C1  = ((uint64_t)0b0100 << 32)  |  (0b1 << 21),
    Rcc_I2C2  = ((uint64_t)0b0100 << 32)  |  (0b1 << 22),
    Rcc_I2C3  = ((uint64_t)0b0100 << 32)  |  (0b1 << 23),
    Rcc_PWR   = ((uint64_t)0b0100 << 32)  |  (0b1 << 28),

    // APB2    
    Rcc_TIM1  = ((uint64_t)0b1000 << 32)  |  (0b1 << 0),
    Rcc_USART1= ((uint64_t)0b1000 << 32)  |  (0b1 << 4),
    Rcc_USART6= ((uint64_t)0b1000 << 32)  |  (0b1 << 5),
    Rcc_ADC1  = ((uint64_t)0b1000 << 32)  |  (0b1 << 8),
    Rcc_SDIO  = ((uint64_t)0b1000 << 32)  |  (0b1 << 11),
    Rcc_SPI1  = ((uint64_t)0b1000 << 32)  |  (0b1 << 12),
    Rcc_SPI4  = ((uint64_t)0b1000 << 32)  |  (0b1 << 13),
    Rcc_SYSCFG= ((uint64_t)0b1000 << 32)  |  (0b1 << 14),
    Rcc_TIM9  = ((uint64_t)0b1000 << 32)  |  (0b1 << 16),
    Rcc_TIM10 = ((uint64_t)0b1000 << 32)  |  (0b1 << 17),
    Rcc_TIM11 = ((uint64_t)0b1000 << 32)  |  (0b1 << 18),
}Rcc_peripheral_t;

/* Rcc function headers*/
void Rcc_getPllConfig(pllCongfig_t *pllConfig);
void Rcc_getSystemClk(Rcc_clkSource_t* clkSource);

void Rcc_setSystemClk_HSI(Rcc_clkSource_t clkSource);
void Rcc_setSystemClk_HSE(Rcc_clkSource_t clkSource);
void Rcc_setSystemClk_PLL(Rcc_clkSource_t clkSource);

void Rcc_setSystemClk(Rcc_clkSource_t clkSource);
void Rcc_ctrlClk(uint32_t clk, uint8_t state);
void Rcc_disableUnusedSystemClk(void);

void Rcc_enablePeripheralClk(uint64_t peripheral); //or should it be  (Rcc_peripheral_t peripheral)
void Rcc_disablePeripheralClk(uint32_t peripheral);
void Rcc_setBusPrescaler(uint32_t bus, uint32_t prescaler);

void Rcc_PllConfig(pllCongfig_t* pllConfig);

void Rcc_init(void);
void Rcc_setConfig(Rcc_cfg_t* Rcc_cfg);


#endif