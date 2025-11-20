#include "switch/switch.h"
#include "GPIO/GPIO.h"

// 'const' to save it in the .rodata {ROM} and SAVE some memory in the RAM
const SWITCH_cfg_t SWITCH_cfg[MAX_SWITCHs]=
{
    [SWITCH_FIRST]={
        .active_state= SWITCH_activeHigh,
        .port= GPIOC,
        .pin= 15,
        .pullType = PULL_DOWN,
    },
    [SWITCH_SECOND]={
        .active_state= SWITCH_activeHigh,
        .port = GPIOC,
        .pin = 1,
        .pullType = PULL_UP,
    },
    [SWITCH_THIRD]={
        .active_state= SWITCH_activeHigh,
        .port= GPIOC,
        .pin= 2,
        .pullType = PULL_DOWN,
    }
};