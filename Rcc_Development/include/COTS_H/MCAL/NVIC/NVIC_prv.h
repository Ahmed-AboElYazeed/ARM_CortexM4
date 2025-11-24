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



#endif