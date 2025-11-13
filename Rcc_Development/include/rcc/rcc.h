#ifndef RCC_H
#define RCC_H

//#include "std_bitUtillity.h"



// Defiene this macro to disable previous clock source after switching
#define RCC_HSI_UNUSED_DESABEL

// ERROR enum
typedef enum 
{
    Rcc_enuAllGood,
    Rcc_enuPll_P_err,
    Rcc_enuPll_N_err

}Err_flag_t;

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

typedef enum{
    GPIOA = ((uint64_t)0b0001 << 32)  |  (0b1 << 0),
    //                      ^bus identity        ^ Peripheral bit number in Rcc regesters
    //                   0001 ->  AHB1         0 : 31 
    //                   0010 ->  AHB2
    //                   0100 ->  APB1
    //                   1000 ->  APB2
    GPIOB = ((uint64_t)0b0001 << 32)  |  (0b1 << 1),
    GPIOC = ((uint64_t)0b0001 << 32)  |  (0b1 << 2),
    GPIOD = ((uint64_t)0b0001 << 32)  |  (0b1 << 3),
    GPIOE = ((uint64_t)0b0001 << 32)  |  (0b1 << 4),
    GPIOH = ((uint64_t)0b0001 << 32)  |  (0b1 << 7),
    CRC   = ((uint64_t)0b0001 << 32)  |  (0b1 << 12),
    DMA1  = ((uint64_t)0b0001 << 32)  |  (0b1 << 21),
    DMA2  = ((uint64_t)0b0001 << 32)  |  (0b1 << 22),

    // AHB2    
    OTGFS = ((uint64_t)0b0010 << 32)  |  (0b1 << 7),

    // APB1   
    TIM2  = ((uint64_t)0b0100 << 32)  |  (0b1 << 0),
    TIM3  = ((uint64_t)0b0100 << 32)  |  (0b1 << 1),
    TIM4  = ((uint64_t)0b0100 << 32)  |  (0b1 << 2),
    TIM5  = ((uint64_t)0b0100 << 32)  |  (0b1 << 3),
    WWDG  = ((uint64_t)0b0100 << 32)  |  (0b1 << 11),
    SPI2  = ((uint64_t)0b0100 << 32)  |  (0b1 << 14),
    SPI3  = ((uint64_t)0b0100 << 32)  |  (0b1 << 15),
    USART2= ((uint64_t)0b0100 << 32)  |  (0b1 << 17),
    I2C1  = ((uint64_t)0b0100 << 32)  |  (0b1 << 21),
    I2C2  = ((uint64_t)0b0100 << 32)  |  (0b1 << 22),
    I2C3  = ((uint64_t)0b0100 << 32)  |  (0b1 << 23),
    PWR   = ((uint64_t)0b0100 << 32)  |  (0b1 << 28),

    // APB2    
    TIM1  = ((uint64_t)0b1000 << 32)  |  (0b1 << 0),
    USART1= ((uint64_t)0b1000 << 32)  |  (0b1 << 4),
    USART6= ((uint64_t)0b1000 << 32)  |  (0b1 << 5),
    ADC1  = ((uint64_t)0b1000 << 32)  |  (0b1 << 8),
    SDIO  = ((uint64_t)0b1000 << 32)  |  (0b1 << 11),
    SPI1  = ((uint64_t)0b1000 << 32)  |  (0b1 << 12),
    SPI4  = ((uint64_t)0b1000 << 32)  |  (0b1 << 13),
    SYSCFG= ((uint64_t)0b1000 << 32)  |  (0b1 << 14),
    TIM9  = ((uint64_t)0b1000 << 32)  |  (0b1 << 16),
    TIM10 = ((uint64_t)0b1000 << 32)  |  (0b1 << 17),
    TIM11 = ((uint64_t)0b1000 << 32)  |  (0b1 << 18),
}Rcc_peripheral_t;

/* Rcc function headers*/
void Rcc_getPllConfig(pllCongfig_t *pllConfig);
void Rcc_getSystemClk(Rcc_clkSource_t* clkSource);
void Rcc_setSystemClk(Rcc_clkSource_t clkSource);
void Rcc_ctrlClk(uint32_t clk, uint8_t state);
void Rcc_disableUnusedSystemClk(void);

void Rcc_enablePeripheralClk(uint64_t peripheral); //or should it be  (Rcc_peripheral_t peripheral)
void Rcc_disablePeripheralClk(uint32_t peripheral);
void Rcc_setBusPrescaler(uint32_t bus, uint32_t prescaler);

void Rcc_PllConfig(pllCongfig_t* pllConfig);

void Rcc_init(void);
void Rcc_setConfig(void);


#endif