#ifndef SYSTICK_PRV_H
#define SYSTICK_PRV_H

#include "std_int.h"

typedef struct 
{
    //volatile uint32_t STK_CTRL;
    union {
        volatile uint32_t STK_CTRL;
        struct STK_CTRL_Bits_t{
            volatile uint32_t ENABLE: 1;
            volatile uint32_t TICKINT: 1;
            volatile uint32_t CLKSOURCE: 1;
            uint32_t reserved: 13;
            volatile uint32_t COUNTFLAG:1;
        }STK_CTRL_Bits;
    };
    union{
        volatile uint32_t STK_LOAD;
        struct STK_LOAD_Bits_t{
            volatile uint32_t RELOAD: 24;
            uint32_t reserved: 8;
        }STK_LOAD_Bits;
    };
    union{
        volatile uint32_t STK_VAL;
        struct STK_VAL_Bits_t{
            volatile uint32_t CURRENT: 24;
            uint32_t reserved: 8;
        }STK_VAL_Bits;
    };
    union{
        volatile uint32_t STK_CALIB;
        struct STK_CALIB_Bits_t{
            volatile uint32_t CURRENT: 24;
            uint32_t reserved: 8;
        }STK_CALIB_Bits;
    };
}SYSTICK_Reg_t;

#define SYSTICK_BASEADD 0xE000E010U
SYSTICK_Reg_t* SYSTICK_Reg = (SYSTICK_Reg_t*)SYSTICK_BASEADD;


#endif