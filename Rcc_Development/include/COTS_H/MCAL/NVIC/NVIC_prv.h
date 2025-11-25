#ifndef NVIC_PRV_H
#define NVIC_PRV_H

#include <stdint.h>

// 0xE000E100-0xE000E4EF

#define NVIC_ISERx_BASEADD 0xE000E100UL
#define NVIC_ICERx_BASEADD 0xE000E180UL
#define NVIC_ISPRx_BASEADD 0xE000E200UL
#define NVIC_ICPRx_BASEADD 0xE000E280UL
#define NVIC_IABRx_BASEADD 0xE000E300UL

#define NVIC_IPRx_BASEADD  0xE000E400UL

#define STIR 0xE000EF00UL

//FOR  changing the priority grouping:
#define SCB_REGBLOCK_BASEADD 0xE000ED00UL
#define AIRCR_REG_BASEADD    (SCB_REGBLOCK_BASEADD+0x0CUL)
#define AIRCR_REG            (*(volatile uint32_t*)(SCB_REGBLOCK_BASEADD+0x0CUL))


#define NVIC_ISERx_VALUE_f(x)  (*(volatile uint32_t*)(NVIC_ISERx_BASEADD + (0x04UL * (x)))) //(x = 0 to 7)
#define NVIC_ICERx_VALUE_f(x)  (*(volatile uint32_t*)(NVIC_ICERx_BASEADD + (0x04UL * (x)))) // ^
#define NVIC_ISPRx_VALUE_f(x)  (*(volatile uint32_t*)(NVIC_ISPRx_BASEADD + (0x04UL * (x)))) // ^
#define NVIC_ICPRx_VALUE_f(x)  (*(volatile uint32_t*)(NVIC_ICPRx_BASEADD + (0x04UL * (x)))) // ^
#define NVIC_IABRx_VALUE_f(x)  (*(volatile uint32_t*)(NVIC_IABRx_BASEADD + (0x04UL * (x)))) // ^

#define NVIC_IPRx_VALUE_f(x)   (*(volatile uint32_t*)(NVIC_IPRx_BASEADD  + (0x04UL * (x))))  //(x = 0 to 59)

// typedef struct{
//     volatile uint32_t NVIC_ISER0;
//     uint32_t Reserved[6];

// }NVIC_Reg_t;


// typedef struct
// {
//   volatile uint32_t ISER[8U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
//     uint32_t RESERVED0[24U];
//   volatile uint32_t ICER[8U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
//     uint32_t RESERVED1[24U];
//   volatile uint32_t ISPR[8U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
//     uint32_t RESERVED2[24U];
//   volatile uint32_t ICPR[8U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
//     uint32_t RESERVED3[24U];
//   volatile uint32_t IABR[8U];               /*!< Offset: 0x200 (R/W)  Interrupt Active bit Register */
//     uint32_t RESERVED4[56U];
//   volatile uint8_t  IP[240U];               /*!< Offset: 0x300 (R/W)  Interrupt Priority Register (8Bit wide) */
//     uint32_t RESERVED5[644U];
//   volatile uint32_t STIR;                   /*!< Offset: 0xE00 ( /W)  Software Trigger Interrupt Register */
// }  NVIC_Type;


#endif