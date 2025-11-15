#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "led/led_cfg.h"

#define true  1
#define false 0

typedef enum{
    LED_activeLow,
    LED_activeHigh
}active_state_t;


typedef struct 
{
    active_state_t active_state;
    void * port;
    uint8_t pin;
    uint8_t pullType;
}LED_cfg_t;


void LED_init(void);
uint8_t LED_turnON(LED_names_t LED_name);
uint8_t LED_turnOFF(LED_names_t LED_name);
uint8_t LED_toggle(LED_names_t LED_name);

#endif