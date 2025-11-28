#include "SYSTICK/SYSTICK.h"
#include "SYSTICK/SYSTICK_prv.h"

#define NULLPTR ((void*)0)

#define PLL_P_2         0b00
#define PLL_P_4         0b01
#define PLL_P_6         0b10
#define PLL_P_8         0b11

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


SYSTICK_ErrorStatus_t SYSTICK_Wait_ms(u32 Copy_u32Delay_ms)
{
    SYSTICK_ErrorStatus_t error_status = SYSTICK_OK;

    u32 Local_ClockFrequency = 0;
    u32 Local_Clockticks = 0;
    RCC_ErrorStatus_t rcc_error_status = RCC_GetSysClockFrequency(&Local_ClockFrequency);
    if (RCC_OK != rcc_error_status)
    {
        error_status = SYSTICK_RCC_ERROR;
    }
    else
    {
        if (SYSTICK->CTRL.bits.CLKSOURCE == SYSTEMCLOCK_DIV_8)
        {
            Local_Clockticks = (Local_ClockFrequency / 8 / 1000) * Copy_u32Delay_ms;
        }
        else
        {
            Local_Clockticks = (Local_ClockFrequency / 1000) * Copy_u32Delay_ms;
        }

        error_status = SYSTICK_SetSystickReloadValue(Local_Clockticks - 1);
        if (error_status != SYSTICK_INVALID_RELOAD_VALUE)
        {
            SYSTICK->VAL.bits.CURRENT = 0; // clear current value of ticks
            SYSTICK_Enable();
            SYSTICK_EnableInterrupt();
        }
        else
        {
            // Empty else
        }
    }

    return error_status;
} 