#include "SYSTICK/SYSTICK.h"
#include "SYSTICK/SYSTICK_prv.h"
#include "rcc/rcc.h"

#define NULLPTR ((void*)0)

#define PLL_P_2         0b00
#define PLL_P_4         0b01
#define PLL_P_6         0b10
#define PLL_P_8         0b11



volatile uint64_t waitCounter = 0; 

void (*userSYSTICK_func)(void);

void SysTick_Handler (void)
{
    userSYSTICK_func();
}

void SYSTICK_waitCounter (void)
{
    waitCounter++;
}




void SYSTICK_Init(uint32_t prescaller)
{
    if (prescaller == 8)
    {
        SYSTICK_Reg->STK_CTRL_Bits.CLKSOURCE=0; //0: AHB/8
    }
    else
    {
        SYSTICK_Reg->STK_CTRL_Bits.CLKSOURCE=1; //1: Processor clock (AHB)
    }
    SYSTICK_Reg->STK_CTRL_Bits.TICKINT = 1;     //1: Counting down to zero to asserts the SysTick exception request. (ENable systick interrupt)
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


void SYSTICK_WaitBlocking_ms(uint32_t Delay_ms)
{
    uint32_t Local_ClockFrequency = 0;
    uint32_t Local_Clockticks = 0;
    SYSTICK_Init(1);
    Rcc_GetSysClockFrequency(&Local_ClockFrequency);

    if (SYSTICK_Reg->STK_CTRL_Bits.CLKSOURCE == 8)
    {
        Local_Clockticks = (Local_ClockFrequency / 8 / 1000) * Delay_ms;
    }
    else
    {
        Local_Clockticks = (Local_ClockFrequency / 1000) * Delay_ms;
    }

    

    SYSTICK_setValue(Local_Clockticks);
    SYSTICK_confgCallBackFun(SYSTICK_waitCounter);
    SYSTICK_start();

    while (waitCounter != 1);
    
    waitCounter = 0;
} 