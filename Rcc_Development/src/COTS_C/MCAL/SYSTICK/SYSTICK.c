#include "SYSTICK/SYSTICK.h"
#include "SYSTICK/SYSTICK_prv.h"

#define NULLPTR ((void*)0)

void (*userSYSTICK_func)(void);

void SysTick_Handler (void)
{
    userSYSTICK_func();
}

uint64_t systemCLK;

void SYSTICK_Init(uint64_t clk, uint32_t prescaller)
{
    systemCLK = clk;
    if (prescaller == 8)
    {
        SYSTICK_Reg->STK_CTRL_Bits.CLKSOURCE=0; //0: AHB/8
    }
    else
    {
        SYSTICK_Reg->STK_CTRL_Bits.CLKSOURCE=1; //1: Processor clock (AHB)
    }
    SYSTICK_Reg->STK_CTRL_Bits.TICKINT = 1;     //1: Counting down to zero to asserts the SysTick exception request.
}

void SYSTICK_confgCallBackFun(void (*fun)(void))
{
    if (fun != NULLPTR)
    {
        userSYSTICK_func = fun;
    }
}

void SYSTICK_setValue(uint32_t value)
{
    if (value>=0x00000001u && value<=0x00FFFFFFu)
    {
        SYSTICK_Reg->STK_LOAD_Bits.RELOAD = value;
    }
}

void SYSTICK_start()
{
   if(SYSTICK_Reg->STK_LOAD_Bits.RELOAD > 0u)
   {
    SYSTICK_Reg->STK_VAL_Bits.CURRENT=0;    //Clear current value.
    SYSTICK_Reg->STK_CTRL_Bits.ENABLE=1;    //Program Control and Status register.  START COUNTING...
   }
}

void SYSTICK_stop()
{
    SYSTICK_Reg->STK_CTRL_Bits.ENABLE=0;
}