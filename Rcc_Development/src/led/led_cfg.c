#include <stdint.h>
#include "led/led.h"
#include "GPIO/GPIO.h"
 
const LED_cfg_t LED_cfg [LED_LEN]
={
    [LED_WARNING]=
    {
        .active_state = LED_activeLow,
        .port = GPIOA,
        .pin = 1,
        .pullType = true,
    },
    [LED_ERROR]=
    {
        .active_state = LED_activeLow,
        .port = GPIOA,
        .pin = 2,
        .pullType=true,
    }
};