#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "rcc/rcc.h"

#define RCC_BASE_ADDR  0x40023800UL
#define RCC ((RCC_Registers_t*) RCC_BASE_ADDR)  // Macro to access RCC registers    // base add casted to a pointer to RCC_Registers_t structure

// for verifing the intered PERIPHERAL values is one of the desited enum values
//#define PERIPHERAL_VERIFYMASK 0xFFFFFFF000000000

typedef struct 
{
    volatile uint32_t HSION :1 ;    // Internal High-Speed clock enable
    volatile uint32_t HSIRDY :1 ;   // Internal High-Speed clock ready flag
     uint32_t RESERVED0 :1 ; // Reserved bit
    volatile uint32_t HSITRIM :5 ;  // Internal High-Speed clock trimming
    volatile uint32_t HSICAL :8 ;   // Internal High-Speed clock calibration
    volatile uint32_t HSEON :1 ;    // External High-Speed clock enable
    volatile uint32_t HSERDY :1 ;   // External High-Speed clock ready flag
    volatile uint32_t HSEBYP :1 ;   // External High-Speed clock bypass
    volatile uint32_t CSSON :1 ;    // Clock Security System enable
    uint32_t RESERVED1 :4 ;          // Reserved bits
    volatile uint32_t PLLON :1 ;    // PLL enable
    volatile uint32_t PLLRDY :1 ;   // PLL clock ready flag
    volatile uint32_t PLLI2SON :1 ; // PLLI2S enable
    volatile uint32_t PLLI2SRDY :1 ;// PLLI2S clock ready flag
} RCC_CR_Bits_t;   //checked 1

typedef struct S
{
    volatile uint32_t PLLM :6 ;     // Division factor for the main PLL and audio PLL input clock
    volatile uint32_t PLLN :9 ;     // Main PLL multiplication factor for VCO
    uint32_t RESERVED1 :1 ;           // Reserved bits
    volatile uint32_t PLLP :2 ;     // Main PLL division factor for main system clock
    uint32_t RESERVED2 :4 ;           // Reserved bits
    volatile uint32_t PLLSRC :1 ;   // PLL entry clock source
    volatile uint32_t PLLQ :4 ;     // Main PLL division factor for USB OTG FS, SDIO and RNG clocks
    uint32_t RESERVED :4 ;           // Reserved bits
} RCC_PLLCFGR_Bits_t;   //checked 2

typedef struct 
{
    volatile uint32_t SW :2 ;      // System clock switch
    volatile uint32_t SWS :2 ;     // System clock switch status
    volatile uint32_t HPRE :4 ;    // AHB prescaler
    uint32_t RESERVED1 :2 ;           // Reserved bits
    volatile uint32_t PPRE1 :3 ;   // APB1 prescaler
    volatile uint32_t PPRE2 :3 ;   // APB2 prescaler
    volatile uint32_t RTCPRE :5 ;  // HSE division factor for RTC
    volatile uint32_t MCO1 :2 ;    // Microcontroller clock output 1    //?
    volatile uint32_t I2SSRC :1 ;  // I2S clock source
    volatile uint32_t MCO1PRE :3 ; // MCO1 prescaler
    volatile uint32_t MCO2PRE :3 ; // MCO2 prescaler
    volatile uint32_t MCO2 :2 ;    // Microcontroller clock output 2    //?
} RCC_CFGR_Bits_t;   //checked 3

typedef struct 
{
    volatile uint32_t LSIRDYF :1 ;   // LSI ready flag
    volatile uint32_t LSERDYF :1 ;   // LSE ready flag
    volatile uint32_t HSIRDYF :1 ;   // HSI ready flag
    volatile uint32_t HSERDYF :1 ;   // HSE ready flag
    volatile uint32_t PLLRDYF :1 ;   // PLL ready flag
    volatile uint32_t PLLI2SRDYF :1 ;// PLLI2S ready flag
    uint32_t RESERVED0 :1 ;          // Reserved bits
    volatile uint32_t CSSF :1 ;      // Clock security system failure flag
    volatile uint32_t LSIRDYIE :1 ;   // LSI ready interrupt enable
    volatile uint32_t LSERDYIE :1 ;   // LSE ready interrupt enable
    volatile uint32_t HSIRDYIE :1 ;   // HSI ready interrupt enable
    volatile uint32_t HSERDYIE :1 ;   // HSE ready interrupt enable
    volatile uint32_t PLLRDYIE :1 ;   // PLL ready interrupt enable
    volatile uint32_t PLLI2SRDYIE :1 ;// PLLI2S ready interrupt enable
    uint32_t RESERVED1 :2 ;          // Reserved bits
    volatile uint32_t LSIRDYC :1 ;   // LSI ready interrupt clear
    volatile uint32_t LSERDYC :1 ;   // LSE ready interrupt clear
    volatile uint32_t HSIRDYC :1 ;   // HSI ready interrupt clear
    volatile uint32_t HSERDYC :1 ;   // HSE ready interrupt clear
    volatile uint32_t PLLRDYC :1 ;   // PLL ready interrupt clear
    volatile uint32_t PLLI2SRDYC :1 ;// PLLI2S ready interrupt clear
    uint32_t RESERVED2 :2 ;          // Reserved bits
    volatile uint32_t CSSC :1 ;      // Clock security system interrupt clear
} RCC_CIR_Bits_t;   //checked 4

typedef struct 
{
    volatile uint32_t GPIOARST :1 ; // GPIOA reset
    volatile uint32_t GPIOBRST :1 ; // GPIOB reset
    volatile uint32_t GPIOCRST :1 ; // GPIOC reset
    volatile uint32_t GPIODRST :1 ; // GPIOD reset
    volatile uint32_t GPIOERST :1 ; // GPIOE reset
    uint32_t RESERVED0 :2 ;         // Reserved bits
    volatile uint32_t GPIOHRST :1 ; // GPIOH reset
    uint32_t RESERVED1 :4 ;          // Reserved bits
    volatile uint32_t CRCRST :1 ;   // CRC reset
    uint32_t RESERVED2 :8 ;          // Reserved bits
    volatile uint32_t DMA1RST :1 ;  // DMA1 reset
    volatile uint32_t DMA2RST :1 ;  // DMA2 reset
} RCC_AHB1RSTR_Bits_t;  //checked 5

typedef struct 
{
    uint32_t RESERVED0 :7 ;         // Reserved bits
    volatile uint32_t OTGERST :1 ; // USB OTG FS reset
    uint32_t RESERVED1 :24 ;        // Reserved bits
} RCC_AHB2RSTR_Bits_t;  //checked 6

typedef struct 
{
    volatile uint32_t TIM2RST :1 ;   // TIM2 reset
    volatile uint32_t TIM3RST :1 ;   // TIM3 reset
    volatile uint32_t TIM4RST :1 ;   // TIM4 reset
    volatile uint32_t TIM5RST :1 ;   // TIM5 reset
    uint32_t RESERVED0 :7 ;           // Reserved bits
    volatile uint32_t WWDGRST :1 ;   // Window watchdog reset
    uint32_t RESERVED1 :2 ;           // Reserved bits
    volatile uint32_t SPI2RST :1 ;   // SPI2 reset
    volatile uint32_t SPI3RST :1 ;   // SPI3 reset
    uint32_t RESERVED2 :1 ;           // Reserved bits
    volatile uint32_t USART2RST :1 ; // USART2 reset
    uint32_t RESERVED3 :3 ;           // Reserved bits
    volatile uint32_t I2C1RST :1 ;   // I2C1 reset
    volatile uint32_t I2C2RST :1 ;   // I2C2 reset
    volatile uint32_t I2C3RST :1 ;   // I2C3 reset
    uint32_t RESERVED4 :4 ;           // Reserved bits
    volatile uint32_t PWRRST :1 ;    // Power interface reset
} RCC_APB1RSTR_Bits_t;  //checked 7

typedef struct 
{
    volatile uint32_t TIM1RST :1 ;   // TIM1 reset
    uint32_t RESERVED0 :3 ;           // Reserved bits
    volatile uint32_t USART1RST :1 ; // USART1 reset
    volatile uint32_t USART6RST :1 ; // USART6 reset
    uint32_t RESERVED1 :2 ;           // Reserved bits
    volatile uint32_t ADC1RST :1 ;   // ADC1 reset
    uint32_t RESERVED2 :2 ;           // Reserved bits
    volatile uint32_t SDIO_RST :1 ;  // SDIO reset
    volatile uint32_t SPI1RST :1 ;   // SPI1 reset
    volatile uint32_t SPI4RST :1 ;   // SPI4 reset
    volatile uint32_t SYSCFGRST :1 ; // System configuration controller reset
    uint32_t RESERVED3 :1 ;           // Reserved bits
    volatile uint32_t TIM9RST :1 ;   // TIM9 reset
    volatile uint32_t TIM10RST :1 ;  // TIM10 reset
    volatile uint32_t TIM11RST :1 ;  // TIM11 reset
} RCC_APB2RSTR_Bits_t;  //checked 8

typedef struct 
{
    volatile uint32_t GPIOAEN :1 ; // GPIOA clock enable
    volatile uint32_t GPIOBEN :1 ; // GPIOB clock enable
    volatile uint32_t GPIOCEN :1 ; // GPIOC clock enable
    volatile uint32_t GPIODEN :1 ; // GPIOD clock enable
    volatile uint32_t GPIOEEN :1 ; // GPIOE clock enable
    uint32_t RESERVED0 :2 ;         // Reserved bits
    volatile uint32_t GPIOHEN :1 ; // GPIOH clock enable
    uint32_t RESERVED1 :4 ;         // Reserved bits
    volatile uint32_t CRCEN :1 ;   // CRC clock enable
    uint32_t RESERVED2 :8 ;         // Reserved bits
    volatile uint32_t DMA1EN :1 ;  // DMA1 clock enable
    volatile uint32_t DMA2EN :1 ;  // DMA2 clock enable
} RCC_AHB1ENR_Bits_t;   //checked 9

typedef struct 
{
    uint32_t RESERVED0 :7 ;         // Reserved bits
    volatile uint32_t OTGFSEN :1 ; // USB OTG FS clock enable
    uint32_t RESERVED1 :24 ;        // Reserved bits
} RCC_AHB2ENR_Bits_t;   //checked 10

typedef struct 
{
    volatile uint32_t TIM2EN :1 ;   // TIM2 clock enable
    volatile uint32_t TIM3EN :1 ;   // TIM3 clock enable
    volatile uint32_t TIM4EN :1 ;   // TIM4 clock enable
    volatile uint32_t TIM5EN :1 ;   // TIM5 clock enable
    uint32_t RESERVED0 :7 ;          // Reserved bits
    volatile uint32_t WWDGEN :1 ;   // Window watchdog clock enable
    uint32_t RESERVED1 :2 ;          // Reserved bits
    volatile uint32_t SPI2EN :1 ;   // SPI2 clock enable
    volatile uint32_t SPI3EN :1 ;   // SPI3 clock enable
    uint32_t RESERVED2 :1 ;          // Reserved bits
    volatile uint32_t USART2EN :1 ; // USART2 clock enable
    uint32_t RESERVED3 :3 ;          // Reserved bits
    volatile uint32_t I2C1EN :1 ;   // I2C1 clock enable
    volatile uint32_t I2C2EN :1 ;   // I2C2 clock enable
    volatile uint32_t I2C3EN :1 ;   // I2C3 clock enable
    uint32_t RESERVED4 :4 ;          // Reserved bits
    volatile uint32_t PWREN :1 ;    // Power interface clock enable
} RCC_APB1ENR_Bits_t;   //checked 11

typedef struct 
{
    volatile uint32_t TIM1EN :1 ;   // TIM1 clock enable
    uint32_t RESERVED0 :3;          // Reserved bits
    volatile uint32_t USART1EN :1 ; // USART1 clock enable
    volatile uint32_t USART6EN :1 ; // USART6 clock enable
    uint32_t RESERVED1 :2 ;          // Reserved bits
    volatile uint32_t ADC1EN :1 ;   // ADC1 clock enable
    uint32_t RESERVED2 :2 ;          // Reserved bits
    volatile uint32_t SDIOEN :1 ;   // SDIO clock enable
    volatile uint32_t SPI1EN :1 ;   // SPI1 clock enable
    volatile uint32_t SPI4EN :1 ;   // SPI4 clock enable
    volatile uint32_t SYSCFGEN :1 ; // System configuration controller clock enable
    uint32_t RESERVED3 :1 ;          // Reserved bits
    volatile uint32_t TIM9EN :1 ;   // TIM9 clock enable
    volatile uint32_t TIM10EN :1 ;  // TIM10 clock enable
    volatile uint32_t TIM11EN :1 ;  // TIM11 clock enable
} RCC_APB2ENR_Bits_t;   //checked 12

typedef struct 
{
    volatile uint32_t GPIOALPEN :1 ; // GPIOA clock enable during Sleep mode
    volatile uint32_t GPIOBLPEN :1 ; // GPIOB clock enable during Sleep mode
    volatile uint32_t GPIOCLPEN :1 ; // GPIOC clock enable during Sleep mode
    volatile uint32_t GPIODLPEN :1 ; // GPIOD clock enable during Sleep mode
    volatile uint32_t GPIOELPEN :1 ; // GPIOE clock enable during Sleep mode
    uint32_t RESERVED0 :2 ;          // Reserved bits
    volatile uint32_t GPIOHLPEN :1 ; // GPIOH clock enable during Sleep mode
    uint32_t RESERVED1 :4 ;          // Reserved bits
    volatile uint32_t CRCLPEN :1 ;   // CRC clock enable during Sleep mode
    uint32_t RESERVED2 :2 ;          // Reserved bits
    volatile uint32_t FLITFLPEN :1 ; // Flash interface clock enable during Sleep mode
    volatile uint32_t SRAM1LPEN :1 ;  // SRAM1 clock enable during Sleep mode
    uint32_t RESERVED3 :4 ;          // Reserved bits
    volatile uint32_t DMA1LPEN :1 ;  // DMA1 clock enable during Sleep mode
    volatile uint32_t DMA2LPEN :1 ;  // DMA2 clock enable during Sleep mode
} RCC_AHB1LPENR_Bits_t; //checked 13

typedef struct 
{
    unsigned int RESERVED0 :7 ;         // Reserved bits
    volatile uint32_t OTGFSLPEN :1 ; // USB OTG FS clock enable during Sleep mode
    uint32_t RESERVED1 :24 ;        // Reserved bits
} RCC_AHB2LPENR_Bits_t; //checked 14

typedef struct 
{
    volatile uint32_t TIM2LPEN :1 ;   // TIM2 clock enable during Sleep mode
    volatile uint32_t TIM3LPEN :1 ;   // TIM3 clock enable during Sleep mode
    volatile uint32_t TIM4LPEN :1 ;   // TIM4 clock enable during Sleep mode
    volatile uint32_t TIM5LPEN :1 ;   // TIM5 clock enable during Sleep mode
    uint32_t RESERVED0 :7 ;           // Reserved bits
    volatile uint32_t WWDGLPEN :1 ;   // Window watchdog clock enable during Sleep mode
    uint32_t RESERVED1 :2 ;           // Reserved bits
    volatile uint32_t SPI2LPEN :1 ;   // SPI2 clock enable during Sleep mode
    volatile uint32_t SPI3LPEN :1 ;   // SPI3 clock enable during Sleep mode
    uint32_t RESERVED2 :1 ;           // Reserved bits
    volatile uint32_t USART2LPEN :1 ; // USART2 clock enable during Sleep mode
    uint32_t RESERVED3 :3 ;           // Reserved bits
    volatile uint32_t I2C1LPEN :1 ;   // I2C1 clock enable during Sleep mode
    volatile uint32_t I2C2LPEN :1 ;   // I2C2 clock enable during Sleep mode
    volatile uint32_t I2C3LPEN :1 ;   // I2C3 clock enable during Sleep mode
    uint32_t RESERVED4 :4 ;           // Reserved bits
    volatile uint32_t PWRLPEN :1 ;    // Power interface clock enable during
} RCC_APB1LPENR_Bits_t; //checked 15

typedef struct 
{
    volatile uint32_t TIM1LPEN :1 ;   // TIM1 clock enable during Sleep mode
    uint32_t RESERVED0 :3 ;           // Reserved bits
    volatile uint32_t USART1LPEN :1 ; // USART1 clock enable during Sleep mode
    volatile uint32_t USART6LPEN :1 ; // USART6 clock enable during Sleep mode
    uint32_t RESERVED1 :2 ;           // Reserved bits
    volatile uint32_t ADC1LPEN :1 ;   // ADC1 clock enable during Sleep mode
    uint32_t RESERVED2 :2 ;           // Reserved bits
    volatile uint32_t SDIOLPEN :1 ;   // SDIO clock enable during Sleep mode
    volatile uint32_t SPI1LPEN :1 ;   // SPI1 clock enable during Sleep mode
    volatile uint32_t SPI4LPEN :1 ;   // SPI4 clock enable during Sleep mode
    volatile uint32_t SYSCFGLPEN :1 ; // System configuration controller clock enable during Sleep mode
    uint32_t RESERVED3 :1 ;           // Reserved bits
    volatile uint32_t TIM9LPEN :1 ;   // TIM9 clock enable during Sleep mode
    volatile uint32_t TIM10LPEN :1 ;  // TIM10 clock enable during Sleep mode
    volatile uint32_t TIM11LPEN :1 ;  // TIM11 clock enable during Sleep mode
} RCC_APB2LPENR_Bits_t; //checked 16

typedef struct 
{
    volatile uint32_t LSEON :1 ;     // External Low-Speed oscillator enable
    volatile uint32_t LSERDY :1 ;    // External Low-Speed oscillator ready
    volatile uint32_t LSEBYP :1 ;    // External Low-Speed oscillator bypass
    uint32_t RESERVED1 :5;          // Reserved bits
    volatile uint32_t RTCSEL :2 ;    // RTC clock source selection
    uint32_t RESERVED2 :5 ;         // Reserved bits
    volatile uint32_t RTCEN :1 ;     // Backup domain software reset
    volatile uint32_t BDRST :1 ;     // RTC clock enable
} RCC_BDCR_Bits_t;  //checked 17

typedef struct 
{
    volatile uint32_t LSION :1 ;     // Internal Low-Speed oscillator enable
    volatile uint32_t LSIRDY :1 ;    // Internal Low-Speed oscillator ready
    uint32_t RESERVED0 :22 ;         // Reserved bits
    volatile uint32_t RMVF :1 ;      // Remove reset flag
    volatile uint32_t BORRSTF :1 ;   // BOR reset flag
    volatile uint32_t PINRSTF :1 ;   // PIN reset flag
    volatile uint32_t PORRSTF :1 ;   // POR/PDR reset flag
    volatile uint32_t SFTRSTF :1 ;   // Software reset flag
    volatile uint32_t IWDGRSTF :1 ;  // Independent watchdog reset flag
    volatile uint32_t WWDGRSTF :1 ;  // Window watchdog reset flag
    volatile uint32_t LPWRRSTF :1 ;  // Low-power reset flag
} RCC_CSR_Bits_t;   //checked 18

typedef struct 
{
    volatile uint32_t MODPER :13 ; // Modulation period
    volatile uint32_t INCSTEP :15 ; // Incrementation step
    uint32_t RESERVED0 :2 ;         // Reserved bits
    volatile uint32_t SPREADSEL :1 ;  // Spread spectrum modulation selection
    volatile uint32_t SSCGEN :1 ;   // Spread spectrum modulation enable
} RCC_SSCGR_Bits_t;  //checked 19

typedef struct 
{
    uint32_t RESERVED0 :6 ;          // Reserved bits
    volatile uint32_t PLLI2SN :9 ;   // PLLI2S multiplication factor for VCO
    uint32_t RESERVED1 :13 ;          // Reserved bits
    volatile uint32_t PLLI2SR :3 ;   // PLLI2S division factor for I2S clock
} RCC_PLLI2SCFGR_Bits_t;    //checked 20

typedef struct 
{
    uint32_t RESERVED0 :24 ;          // Reserved bits
    volatile uint32_t TIMPRE :1 ; // I2S clock source selection
} RCC_DCKCFGR_Bits_t;   //checked 21



typedef struct
{
    union{
        volatile uint32_t CR;
        RCC_CR_Bits_t CR_Bits;
    };
    union{
        volatile uint32_t PLLCFGR;
        RCC_PLLCFGR_Bits_t PLLCFGR_Bits;
    };
    union{
        volatile uint32_t CFGR;
        RCC_CFGR_Bits_t CFGR_Bits;
    };
    union{
        volatile uint32_t CIR;
        RCC_CIR_Bits_t CIR_Bits;
    };
    union{
        volatile uint32_t AHB1RSTR;
        RCC_AHB1RSTR_Bits_t AHB1RSTR_Bits;
    };
    union{
        volatile uint32_t AHB2RSTR;
        RCC_AHB2RSTR_Bits_t AHB2RSTR_Bits;        
    };
    uint32_t RESERVED0[2];
    union{
        volatile uint32_t APB1RSTR;
        RCC_APB1RSTR_Bits_t APB1RSTR_Bits;        
    };
    union{
        volatile uint32_t APB2RSTR;
        RCC_APB2RSTR_Bits_t APB2RSTR_Bits;        
    };
    uint32_t RESERVED1[2];
    union{
        volatile uint32_t AHB1ENR;
        RCC_AHB1ENR_Bits_t AHB1ENR_Bits;        
    };
    union{
        volatile uint32_t AHB2ENR;
        RCC_AHB2ENR_Bits_t AHB2ENR_Bits;        
    };
    uint32_t RESERVED2;
    union{
        volatile uint32_t APB1ENR;
        RCC_APB1ENR_Bits_t APB1ENR_Bits;        
    };
    union{
        volatile uint32_t APB2ENR;
        RCC_APB2ENR_Bits_t APB2ENR_Bits;        
    };
    uint32_t RESERVED3[2];
    union{
        volatile uint32_t AHB1LPENR;
        RCC_AHB1LPENR_Bits_t AHB1LPENR_Bits;
    };
    union{
        volatile uint32_t AHB2LPENR;
        RCC_AHB2LPENR_Bits_t AHB2LPENR_Bits;        
    };
    uint32_t RESERVED4;
    union{
        volatile uint32_t APB1LPENR;
        RCC_APB1LPENR_Bits_t APB1LPENR_Bits;
    };
    union{
        volatile uint32_t APB2LPENR;
        RCC_APB2LPENR_Bits_t APB2LPENR_Bits;        
    };
    uint32_t RESERVED5[2];
    union{
        volatile uint32_t BDCR;
        RCC_BDCR_Bits_t BDCR_Bits;        
    };
    union{
        volatile uint32_t CSR;
        RCC_CSR_Bits_t CSR_Bits;        
    };
    uint32_t RESERVED6[2];
    union{
        volatile uint32_t SSCGR;
        RCC_SSCGR_Bits_t SSCGR_Bits;        
    };
    union{
        volatile uint32_t PLLI2SCFGR;
        RCC_PLLI2SCFGR_Bits_t PLLI2SCFGR_Bits;        
    };
    uint32_t RESERVED7;
    union{
        volatile uint32_t DCKCFGR;
        RCC_DCKCFGR_Bits_t DCKCFGR_Bits;
    };
} RCC_Registers_t;


/* how to use them
    
    for single bit acces:
    // 1. Enable HSI (Setting HSION bit to 1)
        RCC->CR_Bits.HSION = 1;
    for multi bit access:
    // Set the HSI trimming value to 16 (decimal value 16)
        RCC->CR_Bits.HSITRIM = 16;      // Decimal
        RCC->CR_Bits.HSITRIM = 0b10000; // Binary
*/


void Rcc_init(void)
{
    //calling linking method "for now"
        
        //FOR VONFIGURING PLL
        Rcc_cfg_t Rcc_cfg;
        Rcc_cfg.systemClkSource = HSI_CLK;
        Rcc_cfg.pllCfg.pllSource = HSI_CLK;
        Rcc_cfg.pllCfg.pllM = 8 ;
        Rcc_cfg.pllCfg.pllN = 168 ;
        Rcc_cfg.pllCfg.pllP = 4 ;
        Rcc_cfg.pllCfg.pllQ = 7 ;
    
    Rcc_setConfig(&Rcc_cfg);
    // Rcc_PllConfig(&Rcc_cfg.pllCfg);
    // Rcc_setSystemClk(Rcc_cfg.systemClkSource);

    //Rcc_disableUnusedSystemClk()
}

void Rcc_setConfig(Rcc_cfg_t* Rcc_cfg)
{
    Rcc_PllConfig(&(Rcc_cfg->pllCfg));

    Rcc_setSystemClk(Rcc_cfg->systemClkSource);
}

/* RCC clock configuration register (RCC_CFGR)
    Bits 3:2 SWS: System clock switch status
        Set and cleared by hardware to indicate which clock source is used as the system clock.
            00: HSI oscillator used as the system clock
            01: HSE oscillator used as the system clock
            10: PLL used as the system clock
            11: not applicable
*/
void Rcc_getSystemClk(Rcc_clkSource_t* clkSource)
{
    switch (RCC->CFGR_Bits.SWS)
    { 
        case 0b00:
            *clkSource = HSI_CLK;
            break;
        case 0b01:
            *clkSource = HSE_CLK;
            break;
        case 0b10:
            *clkSource = PLL_CLK;
            break;
        default:
            // Handle invalid clock source
            *clkSource = INVALID_CLK;
            break;
    }
}

/* RCC clock configuration register (RCC_CFGR)
Bits 1:0 SW: System clock switch
Set and cleared by software to select the system clock source.
Set by hardware to force the HSI selection when leaving the Stop or Standby mode or in
case of failure of the HSE oscillator used directly or indirectly as the system clock.
    00: HSI oscillator selected as system clock
    01: HSE oscillator selected as system clock
    10: PLL selected as system clock
    11: not allowed
*/
/*
    1. read current system clock source 
    2. if different from desired source, switch to desired source "ELSE Jump to END"
    3. check
    current -> desired
        HSI -> HSE  
                    a. Enable HSE
                    b. Wait until HSE is ready
                    c. Switch to HSE
                    d. read switch status until confirmed 
                    e. Disable HSI (optional)
            -> PLL_HSI
                    0. Configure PLL if not already configured
                        -> HSI as PLL source
                            a. read switch to confirm HSI is still ready (optional)
                    1. Enable PLL
                    2. Wait until PLL is ready
                    3. Switch to PLL
                    4. read switch status until confirmed
                    5. Disable previous clock source (optional)
            -> PLL_HSE
                    0. Configure PLL if not already configured
                        -> HSE as PLL source
                            a. Enable HSE
                            b. Wait until HSE is ready
                    1. Enable PLL
                    2. Wait until PLL is ready
                    3. Switch to PLL
                    4. read switch status until confirmed
                    5. Disable previous clock source (optional)
        HSE -> HSI 
                    a. Enable HSI
                    b. Wait until HSI is ready
                    c. Switch to HSI
                    d. read switch status until confirmed 
                    e. Disable HSE 
            -> PLL_HSI
                    0. Configure PLL if not already configured
                        -> HSI as PLL source
                            a. Enable HSI
                            b. Wait until HSI is ready
                    1. Enable PLL
                    2. Wait until PLL is ready
                    3. Switch to PLL
                    4. read switch status until confirmed
                    5. Disable previous clock source (optional)
            -> PLL_HSE
                    0. Configure PLL if not already configured
                        -> HSE as PLL source
                            a. read switch to confirm HSE is still ready (optional)
                    1. Enable PLL
                    2. Wait until PLL is ready
                    3. Switch to PLL
                    4. read switch status until confirmed
                    5. Disable previous clock source (optional)
        PLL_HSI -> PLL_HSE
                    a. Enable HSE
                    b. Wait until HSE is ready
                    c. Switch PLL source to HSE
                    d. read switch status until confirmed
                    e. Disable HSI (optional)
                -> HSI
                    a. Switch to HSI
                    b. read switch status until confirmed
                    c. Disable PLL
                -> HSE
                    a. Enable HSE
                    b. Wait until HSE is ready
                    c. Switch to HSE
                    d. read switch status until confirmed
                    e. Disable PLL
        PLL_HSE -> PLL_HSI
                    a. Enable HSI
                    b. Wait until HSI is ready
                    c. Switch PLL source to HSI
                    d. read switch status until confirmed
                    e. Disable HSE 
                -> HSI
                    a. Enable HSI
                    b. Wait until HSI is ready
                    c. Switch to HSI
                    d. read switch status until confirmed
                    e. Disable PLL
                -> HSE
                    a. switch to HSE
                    b. read switch status until confirmed
                    c. Disable PLL
*/
void Rcc_setSystemClk(Rcc_clkSource_t clkSource)
{
    Rcc_clkSource_t currentClkSource;
    // Get the current system clock source
    Rcc_getSystemClk(&currentClkSource);

    if (currentClkSource != clkSource)
    {
        switch (clkSource)
        {
            case HSI_CLK:
                Rcc_setSystemClk_HSI(clkSource);
                    if (currentClkSource == HSE_CLK)
                    {
                        /* Disable HSE */
                        RCC->CR_Bits.HSEON = 0b0u;  //0: HSE oscillator OFF
                    }
                    else { /* nothing */ }
                    if (currentClkSource == PLL_CLK)
                    {
                        /*      Disable PLL     */
                        RCC->CR_Bits.PLLON = 0b0u; //0: PLL OFF    //1: PLL ON
                    }
                    else { /* nothing */ }
                break;
            case HSE_CLK:
                Rcc_setSystemClk_HSE(clkSource);
                if (currentClkSource == PLL_CLK)
                {
                    /*      Disable PLL     */
                    RCC->CR_Bits.PLLON = 0b0u; //0: PLL OFF    //1: PLL ON
                }
                else { /* nothing */ }
                #ifdef RCC_HSI_UNUSED_DESABEL
                    RCC->CR_Bits.HSION = 0; // Disable HSI (optional)
                #endif
                break;
            case PLL_CLK:
                Rcc_setSystemClk_PLL(clkSource);
                break;
            default:
                // Handle invalid current clock source
                printf("INVALID clock sourse, enter on of these (HSI_CLK, HSE_CLK, PLL_CLK)");
                break;
        }
        // Wait until the switch is complete
        //while (RCC->CFGR_Bits.SWS != RCC->CFGR_Bits.SW);
    }

}

void Rcc_setSystemClk_HSI(Rcc_clkSource_t clkSource)
{
    //initializing time out
    uint8_t timeOut = 50;
    /*
    -> HSI 
        a. Enable HSI
        b. Wait until HSI is ready
        c. Switch to HSI
        d. read switch status until confirmed 
        e. Disable HSE 
    */
    RCC->CR_Bits.HSION = 1; // Enable HSI
    while (RCC->CR_Bits.HSIRDY == 0b1u && timeOut--); // Wait until HSI is ready
    RCC->CFGR_Bits.SW = 0b00; // Switch to HSI  (00: HSI oscillator selected as system clock)
    timeOut = 50;   //reset time out
    while (RCC->CFGR_Bits.SWS != 0b00  && timeOut--);  //read switch status until confirmed 
}
void Rcc_setSystemClk_HSE(Rcc_clkSource_t clkSource)
{
    //initializing time out
    uint8_t timeOut = 50;
    /*
    -> HSE  
        a. Enable HSE
        b. Wait until HSE is ready
        c. Switch to HSE
        d. read switch status until confirmed 
        e. Disable HSI (optional)
    */
    RCC->CR_Bits.HSEON = 1; // Enable HSE
    timeOut = 50;   //reset time out
    while (RCC->CR_Bits.HSERDY == 0 && timeOut--); // Wait until HSE is ready
    RCC->CFGR_Bits.SW = 0b01; // Switch to HSE (01: HSE oscillator used as the system clock)
    timeOut = 50;   //reset time out
    while (RCC->CFGR_Bits.SWS != 0b01 && timeOut--);  //read switch status until confirmed  
}
void Rcc_setSystemClk_PLL(Rcc_clkSource_t clkSource)
{
    //initializing time out
    uint8_t timeOut = 50;
    /*
    -> PLL
        0. Configure PLL if not already configured
        1. Enable PLL
        2. Wait until PLL is ready
        3. Switch to PLL
        4. read switch status until confirmed
        5. Disable previous clock source (optional)
    */
    printf("CAUTION: you MUST call the \"Rcc_PllConfig\" before selecting PLL_CLK.  \n");
    RCC->CR_Bits.PLLON= 0b1u;   //Enable PLL
    // these two lines tell the flash to that the clock speed will increase by a large amount.
    /* When you perform this step before switching to PLL, the Flash interface has enough wait cycles to handle the faster clock.
        Thus, the system can safely switch to the PLL as the system clock source, and the loop waiting for it to stabilize completes successfully.
        */
    *(uint32_t*)((0x40000000UL + 0x00020000UL) + 0x3C00UL) &= ~0b111;
    *(uint32_t*)((0x40000000UL + 0x00020000UL) + 0x3C00UL) |= (2 & 0b111);
    timeOut = 50;   //reset time out
    while(0b1u != RCC->CR_Bits.PLLRDY && timeOut--); //Wait until PLL is ready 
    RCC->CFGR_Bits.SW = 0b10u;  //Switch to PLL (10: PLL selected as system clock)
    timeOut = 50;   //reset time out
    while ( 0b10u != RCC->CFGR_Bits.SWS && timeOut--);   //read switch status until confirmed
}

/*
typedef struct
{
    uint32_t pllSource;
    uint32_t pllM;
    uint32_t pllN;
    uint32_t pllP;
    uint32_t pllQ;
}pllCongfig_t;
*/
void Rcc_PllConfig(pllCongfig_t* pllConfig)
{
    uint8_t timeOut = 50;
    Rcc_clkSource_t currentClkSource;
    // Get the current system clock source
    Rcc_getSystemClk(&currentClkSource);
   if (HSI_CLK != currentClkSource)
   {
        RCC->CR_Bits.HSION = 1; // Enable HSI
        timeOut = 50;   //reset time out
        while (RCC->CR_Bits.HSIRDY == 0 && timeOut--); // Wait until HSI is ready
   }
   //SWITCH to HSI
    RCC->CFGR_Bits.SW = 0b00; // Switch to HSI  (00: HSI oscillator selected as system clock)
    timeOut = 50;   //reset time out
    while (RCC->CFGR_Bits.SWS != 0b00 && timeOut--);  //read switch status until confirmed 
    //set user PLL configerations 
    RCC->PLLCFGR_Bits.PLLM = pllConfig->pllM;
    RCC->PLLCFGR_Bits.PLLN = pllConfig->pllN;
    RCC->PLLCFGR_Bits.PLLP = (pllConfig->pllP/2)-1;   //only 2,4,6,8  by 0,1,2,3 as input so i used this eq:   output"0,1,2,3' = (input'2,4,6,8'/2)-1
    RCC->PLLCFGR_Bits.PLLQ = pllConfig->pllQ;
    // set the desired pll clock source
    //this next switch change the PLLSOURC Bit, *** his bit can be written only when PLL and PLLI2S are disabled ***
    if (RCC->CR_Bits.PLLRDY == 0b0u)
    {
        switch (pllConfig->pllSource)
        {
        case HSI_CLK:   // PLL_HSI
            /* PLL_HSI (0: HSI clock selected as PLL and PLLI2S clock entry) */
            RCC->PLLCFGR_Bits.PLLSRC = 0b0u;              
            break;
        case HSE_CLK:
            // enable the PLL SOURCE            
            RCC->CR_Bits.HSEON = 1; // Enable HSE
            timeOut = 50;   //reset time out
            while (RCC->CR_Bits.HSERDY == 0 && timeOut--); // Wait until HSE is ready
            /* PLL_HSE (1: HSE oscillator clock selected as PLL and PLLI2S clock entry) */
            RCC->PLLCFGR_Bits.PLLSRC = 0b1u;
            break;
        default:
        // handel wrong pllSource inputs
            break;
        }
   }
}

void Rcc_getPllConfig(pllCongfig_t *pllConfig)
{
    //read user PLL configerations 
    pllConfig->pllSource = RCC->PLLCFGR_Bits.PLLSRC;
    pllConfig->pllM = RCC->PLLCFGR_Bits.PLLM;
    pllConfig->pllN = RCC->PLLCFGR_Bits.PLLN;
    pllConfig->pllP = RCC->PLLCFGR_Bits.PLLP;
    pllConfig->pllQ = RCC->PLLCFGR_Bits.PLLQ;
}

void Rcc_disableUnusedSystemClk()
{
    Rcc_clkSource_t localActual_clkSource;
    pllCongfig_t *pllConfig;
    // Get the current system clock source
    Rcc_getSystemClk(&localActual_clkSource);
    pllConfig=0;    //INITIALIZING to remove the warning
    Rcc_getPllConfig(pllConfig);
    switch (localActual_clkSource)
    {
    case HSI_CLK:
        /* Disable HSE */
        RCC->CR_Bits.HSEON = 0b0u;  //0: HSE oscillator OFF
        /* Disable PLL */
        RCC->CR_Bits.PLLON = 0b0u;  //0: PLL oscillator OFF
        break;
    case HSE_CLK:
        /* Disable HSI */
        #ifdef RCC_HSI_UNUSED_DESABEL
            RCC->CR_Bits.HSION = 0; // Disable HSI (optional) 0: HSI oscillator OFF
        #endif
        /* Disable PLL */
        RCC->CR_Bits.PLLON = 0b0u;  //0: PLL oscillator OFF
        break;
    case PLL_CLK:
        switch (pllConfig->pllSource)
        {
        case HSI_CLK:
            /* Disable HSE */
            RCC->CR_Bits.HSEON = 0b0u;  //0: HSE oscillator OFF
            break;
        case HSE_CLK:
            /* Disable HSI */
            #ifdef RCC_HSI_UNUSED_DESABEL
                RCC->CR_Bits.HSION = 0; // Disable HSI (optional) 0: HSI oscillator OFF
            #endif
            break;

        default:
            break;
        }
        break;
    
    default:
        break;
    }
}

void Rcc_enablePeripheralClk(uint64_t peripheral)   //or should it be  (Rcc_peripheral_t peripheral) ???
{
    switch (peripheral >> 32)
    {
        case 0b0001:
            RCC->AHB1ENR |= (uint32_t) peripheral;
            break;
        case 0b0010:
            RCC->AHB2ENR |= (uint32_t) peripheral;
            break;
        case 0b0100:
            RCC->APB1ENR |= (uint32_t) peripheral;
            break;
        case 0b1000:
            RCC->APB2ENR |= (uint32_t) peripheral;
            break;
    }
}