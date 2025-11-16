#include <stdint.h>
#include "led/led.h"
#include "GPIO/GPIO.h"
 
const LED_cfg_t LED_cfg [LED_LEN]
={
    [LED_WARNING]=
    {
        .active_state = LED_activeLow,
        .port = GPIOC,
        .pin = 13,
        .pullType = PULL_UP,
    },
    [LED_GARAG]=
    {
        .active_state = LED_activeHigh,
        .port = GPIOC,
        .pin = 14,
        .pullType= PULL_DOWN,
    }
};