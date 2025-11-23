#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "led/led_cfg.h"

#define true  1
#define false 0

#define HIGH  1
#define LOW   0


typedef enum{
    LED_PORTA,
    LED_PORTB,
    LED_PORTC,
    LED_PORTD,
    LED_PORTE,
    LED_PORTH
}LED_port_enu_t;


/*  //4. pull-up/pull-down
00: No pull-up, pull-down
01: Pull-up
10: Pull-down
11: Reserved*/
#define NO_PULL     0b00u
#define PULL_UP     0b01u
#define PULL_DOWN   0b10u

typedef enum{
    LED_activeLow,
    LED_activeHigh
}LED_active_state_t;


typedef struct 
{
    LED_active_state_t active_state;
    LED_port_enu_t port;
    uint8_t pin;
    uint8_t pullType;
}LED_cfg_t;

typedef enum
{
    LED_ON,
    LED_OFF,
    LED_ERR
}LED_state_t;


void LED_init(void);
uint8_t LED_turnON(LED_names_t LED_name);
uint8_t LED_turnOFF(LED_names_t LED_name);
uint8_t LED_toggle(LED_names_t LED_name);

#endif