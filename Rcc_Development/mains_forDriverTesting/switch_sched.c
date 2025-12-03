
#include <stdio.h>
#include <stdint.h>
#include <rcc/rcc.h>
#include <GPIO/GPIO.h>
#include <led/led.h>
#include "switch/switch.h"
#include "NVIC/NVIC.h"
#include "SYSTICK/SYSTICK.h"
#include "Sched.h"

void toggleLED (void * arg)
{
    if (SWITCH_readState_sch(SWITCH_FIRST) == SWITCH_PRESSED_ON)
    {
        LED_turnON((LED_names_t)arg);
    }
    else
    {
        LED_turnOFF((LED_names_t)arg);
    }
}



Runnable_t LED_Runnable =
{
    .func= toggleLED,
    .priority = LED_RUNNABLE_PRIORITY,
    .priodicity_ticks=5,   //ms
    .first_delay=0,
    .arg = (void*)LED_THIRD,
};

// Runnable_t LED_Runnable2 =
// {
//     .func= toggleLED,
//     .priority = 2,
//     .priodicity_ticks=2000,   //ms
//     .first_delay=0,
//     .arg = (void*)LED_WARNING,
// };

int main ()
{


    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    Rcc_enablePeripheralClk(Rcc_GPIOC);


    SWITCH_init_sch();
    LED_init();
    LED_turnOFF(LED_THIRD);
    LED_turnON(LED_THIRD);

    //__asm volatile ("CPSIE i");
    Sched_init(1);
    Sched_registerRunnable(&LED_Runnable);
    Sched_start();

    volatile int x=0;
    while (1)
    {
        x++;
    }

    return 0;
}