#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include "switch/switch_cfg.h"

#define true  1
#define false 0

#define HIGH  1
#define LOW   0


typedef enum{
    SWITCH_activeLow,
    SWITCH_activeHigh
}SWITCH_active_state_t;


typedef struct 
{
    SWITCH_active_state_t active_state;
    void * port;
    uint8_t pin;
    uint8_t pullType;
}SWITCH_cfg_t;

typedef enum
{
    SWITCH_UNPRESSED_OFF,
    SWITCH_PRESSED_ON,
    SWITCH_ERR
}SWITCH_state_t;


void SWITCH_init(void);
uint8_t SWITCH_readState(SWITCH_names_t SWITCH_name);


#endif