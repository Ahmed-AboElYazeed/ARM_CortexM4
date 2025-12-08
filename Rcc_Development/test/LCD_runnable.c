
#include <stdio.h>
#include <stdint.h>
#include <rcc/rcc.h>
#include <GPIO/GPIO.h>
#include <led/led.h>
#include "switch/switch.h"
#include "NVIC/NVIC.h"
#include "SYSTICK/SYSTICK.h"
#include "Sched.h"
#include "LCD/LCD.h"

extern LCD_cfg_t LCD_cfg[LCD_NUMBER];

void toggleLED (void * arg)
{
    LCD_writeString_asynch(&LCD_cfg[LCD_0],"Cee123456789123456789123456789012",0);
}



Runnable_t LED_Runnable =
{
    .func= toggleLED,
    .priority = LED1_RUNNABLE_PRIORITY,
    .priodicity_ticks=1000,   //ms
    .first_delay=100,
    .arg = (void*)LED_THIRD,
};

// Runnable_t LED_Runnable2 =
// {
//     .func= toggleLED,
//     .priority = LED2_RUNNABLE_PRIORITY,
//     .priodicity_ticks=2000,   //ms
//     .first_delay=0,
//     .arg = (void*)LED_WARNING,
// };

int main()
{
    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);

    __asm volatile ("CPSIE i");

    LED_init();
    LED_turnOFF(LED_THIRD);
    LED_turnON(LED_THIRD);

    Sched_init(1);
    LCD_asych_init(&LCD_cfg[LCD_0]);
    Sched_registerRunnable(&LED_Runnable);
    Sched_start();


    // LCD_init(&LCD_cfg[LCD_0]);
    // // LCD_writeChar(&LCD_cfg[LCD_0], 'z');
    // LCD_writeString(&LCD_cfg[LCD_0], "Zee");
    // LCD_writeString(&LCD_cfg[LCD_0], "   good 123456");
    // //LCD_setCursorPosition(&LCD_cfg[LCD_0],40);
    // LCD_writeString(&LCD_cfg[LCD_0], "good 123");

    // LCD_saveAllCustomCharacter (&LCD_cfg[LCD_0]);
    // LCD_writeChar(&LCD_cfg[LCD_0],0);
    // // LCD_saveCustomCharacter (&LCD_cfg[LCD_0],1);
    // LCD_writeChar(&LCD_cfg[LCD_0],1);
    
    // // while (1)
    // {
    //     LCD_setCursorPosition (&LCD_cfg[LCD_0], 4);
    //     LCD_writeChar(&LCD_cfg[LCD_0],1);
    //     SYSTICK_WaitBlocking_ms(100);    //39 microSec
    //     LCD_setCursorPosition (&LCD_cfg[LCD_0], 4);
    //     LCD_writeChar(&LCD_cfg[LCD_0],2);
    //     SYSTICK_WaitBlocking_ms(100);    //39 microSec
    // }
    
    return 0;
}