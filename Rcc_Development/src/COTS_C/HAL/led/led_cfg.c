#include <stdint.h>
#include "led/led.h"
 
const LED_cfg_t LED_cfg [LED_LEN]
={
    [LED_WARNING]=
    {
        .active_state = LED_activeLow,
        .port = LED_PORTC,
        .pin = 13,
        .pullType = PULL_UP,
    },
    [LED_GARAG]=
    {
        .active_state = LED_activeHigh,
        .port = LED_PORTC,
        .pin = 14,
        .pullType= PULL_DOWN,
    },
    [LED_THIRD]=
    {
        .active_state = LED_activeHigh,
        .port = LED_PORTA,
        .pin = 11,
        .pullType= PULL_DOWN,
    }
};