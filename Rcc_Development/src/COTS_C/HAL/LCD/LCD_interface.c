#include <stdint.h>
#include "LCD/LCD.h"


LCD_cfg_t LCD_cfg[LCD_NUMBER]=
{
    [LCD_0]=
    {
        .mode=8,
        .LCD_pins[D0].port=PORTA_LCD,
        .LCD_pins[D0].pin = 0,
        .LCD_pins[D1].port=PORTA_LCD,
        .LCD_pins[D1].pin = 1,
        .LCD_pins[D2].port=PORTA_LCD,
        .LCD_pins[D2].pin = 2,
        .LCD_pins[D3].port=PORTA_LCD,
        .LCD_pins[D3].pin = 3,
        .LCD_pins[D4].port=PORTA_LCD,
        .LCD_pins[D4].pin = 4,
        .LCD_pins[D5].port=PORTA_LCD,
        .LCD_pins[D5].pin = 5,
        .LCD_pins[D6].port=PORTA_LCD,
        .LCD_pins[D6].pin = 6,
        .LCD_pins[D7].port=PORTA_LCD,
        .LCD_pins[D7].pin = 7,
        .LCD_pins[RS].port=PORTA_LCD,
        .LCD_pins[RS].pin = 8,
        .LCD_pins[RW].port=PORTA_LCD,
        .LCD_pins[RW].pin = 9,
        .LCD_pins[EN].port=PORTA_LCD,
        .LCD_pins[EN].pin = 10,
    }
};