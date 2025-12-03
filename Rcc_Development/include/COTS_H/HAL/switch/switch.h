#ifndef SWITCH_H
#define SWITCH_H

#include <stdint.h>
#include "switch/switch_cfg.h"

#define true  1
#define false 0

#define DEBOUNSING_DELAY 100000UL


typedef enum{
    SWITCH_PORTA,
    SWITCH_PORTB,
    SWITCH_PORTC,
    SWITCH_PORTD,
    SWITCH_PORTE,
    SWITCH_PORTH
}SWITCH_port_enu_t;

/*  //4. pull-up/pull-down
00: No pull-up, pull-down
01: Pull-up
10: Pull-down
11: Reserved*/
#define NO_PULL     0b00u
#define PULL_UP     0b01u
#define PULL_DOWN   0b10u

#define HIGH  1
#define LOW   0
typedef enum{
    PIN_LOW,
    PIN_HIGH
}PIN_state_enm_t;

typedef enum{
    SWITCH_activeLow,
    SWITCH_activeHigh
}SWITCH_active_state_t;


typedef struct 
{
    SWITCH_active_state_t active_state;
    SWITCH_port_enu_t port;
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

void SWITCH_init_sch(void);
uint8_t SWITCH_readState_sch(SWITCH_names_t SWITCH_name);

#endif