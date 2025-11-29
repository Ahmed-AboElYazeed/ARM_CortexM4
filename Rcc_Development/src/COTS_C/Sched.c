#include <stdint.h>
#include "Sched.h"
#include "SYSTICK/SYSTICK.h"
#include "rcc/rcc.h"

#define NULL 0

static Runnable_t* savedRunnable [MAX_RUNNABLE];
static uint32_t Sched_triggerred;
static uint64_t tickCount;

static void Sched_exec (void);    //excuted in Handler mode


ErrState_enu_t Sched_init (uint32_t tickTime_ms)
{
    uint32_t Local_ClockFrequency = 0;
    uint32_t Local_Clockticks = 0;
    SYSTICK_Init(1);
    Rcc_GetSysClockFrequency(&Local_ClockFrequency);

    // if (SYSTICK_Reg->STK_CTRL_Bits.CLKSOURCE == 8)
    // {
    //     Local_Clockticks = (Local_ClockFrequency / 8 / 1000) * tickTime;
    // }
    // else
    // {
        Local_Clockticks = (Local_ClockFrequency / 1000) * tickTime_ms;
    // }
    SYSTICK_setValue(Local_Clockticks);

    SYSTICK_confgCallBackFun(Sched_exec);
    return ALL_GOOD;
}

static void Sched_exec (void)    //excuted in Handler mode
{
    Sched_triggerred = 1;
    tickCount++;
}

ErrState_enu_t Sched_registerRunnable (Runnable_t * Runnable)
{
    if (Runnable == NULLPTR)
    {
        return NULL_RUNNABLE;
    }
    else if (savedRunnable[Runnable->priority] == NULL)
    {
        savedRunnable[Runnable->priority] = Runnable;
    }
    else{

    }
    return ALL_GOOD;
}

void Sched_start ()
{
    SYSTICK_start();
    while (1)
    {
        if (Sched_triggerred == 1)
        {
            Sched_triggerred = 0;
            for (int idx=0; idx<MAX_RUNNABLE; idx++)
            {
                if (savedRunnable[idx] != NULL)
                {
                    if (savedRunnable[idx]->func != NULL)
                    {
                        if (tickCount % savedRunnable[idx]->priodicity_ticks == 0)
                        {
                            savedRunnable[idx]->func(savedRunnable[idx]->arg);
                        }
                        else
                        {
                            // not your time to execute
                        }
                    }
                    else
                    {
                        // func is a NULL ptr
                    }
                } 
                else
                {
                    // this runnable is not saved yet
                }
            }
        }
        else{
            // no interrupt called yet
        }
    }
}