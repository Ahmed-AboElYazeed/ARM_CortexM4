
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

LCD_cfg_t LCD_cfg[LCD_NUMBER];


int main()
{
    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    LCD_init(&LCD_cfg[LCD_0]);
    // LCD_writeChar(&LCD_cfg[LCD_0], 'z');
    LCD_writeString(&LCD_cfg[LCD_0], "Zee");
    LCD_writeString(&LCD_cfg[LCD_0], "   good 123456");
    //LCD_setCursorPosition(&LCD_cfg[LCD_0],40);
    LCD_writeString(&LCD_cfg[LCD_0], "good 123");

    LCD_saveAllCustomCharacter (&LCD_cfg[LCD_0]);
    LCD_writeChar(&LCD_cfg[LCD_0],0);
    // LCD_saveCustomCharacter (&LCD_cfg[LCD_0],1);
    LCD_writeChar(&LCD_cfg[LCD_0],1);
    
    while (1)
    {
        LCD_setCursorPosition (&LCD_cfg[LCD_0], 4);
        LCD_writeChar(&LCD_cfg[LCD_0],1);
        SYSTICK_WaitBlocking_ms(100);    //39 microSec
        LCD_setCursorPosition (&LCD_cfg[LCD_0], 4);
        LCD_writeChar(&LCD_cfg[LCD_0],2);
        SYSTICK_WaitBlocking_ms(100);    //39 microSec
    }
    
    return 0;
}