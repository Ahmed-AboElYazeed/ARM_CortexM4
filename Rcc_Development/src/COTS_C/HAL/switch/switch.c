#include <stdint.h>
#include "switch/switch.h"
#include "GPIO/GPIO.h"


extern const SWITCH_cfg_t SWITCH_cfg[MAX_SWITCHs];
GPIO_pinCfg_t GPIO_SWITCHPin[MAX_SWITCHs];

void SWITCH_init(void)
{
    for(int i=0; i< MAX_SWITCHs; i++)
    {
        GPIO_identfyPin(&GPIO_SWITCHPin[i],SWITCH_cfg[i].port,SWITCH_cfg[i].pin); //GPIOA/B/C/D/E , pin number 0-15
        GPIO_setPinDirMode(&GPIO_SWITCHPin[i],INPUT);  //input, output, alternate, analog
        GPIO_setOutPinMode(&GPIO_SWITCHPin[i],PUSH_PULL,SWITCH_cfg[i].pullType);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&GPIO_SWITCHPin[i], DIO); 
        GPIO_creatPin(&GPIO_SWITCHPin[i]);
    }
}


uint8_t SWITCH_readState(SWITCH_names_t SWITCH_name)
{
    SWITCH_state_t switch_state= SWITCH_UNPRESSED_OFF;
    PIN_state_enm_t pin_state = GPIO_readPinVal(&GPIO_SWITCHPin[SWITCH_name], &switch_state);
    if (SWITCH_cfg[SWITCH_name].active_state == SWITCH_activeHigh)
    {
        if (pin_state == PIN_HIGH)
        {
            //for (volatile int i=0; i<DEBOUNSING_DELAY; i++);
            GPIO_readPinVal(&GPIO_SWITCHPin[SWITCH_name], &switch_state);
            switch_state= SWITCH_PRESSED_ON;
        }else
        {
            switch_state= SWITCH_UNPRESSED_OFF;
        }
    }
    else    //ACTIVE Low switch
    {
        if (pin_state == PIN_LOW)
        {
            //for (volatile int i=0; i<DEBOUNSING_DELAY; i++);
            GPIO_readPinVal(&GPIO_SWITCHPin[SWITCH_name], &switch_state);
            switch_state= SWITCH_PRESSED_ON;
        }else
        {
            switch_state= SWITCH_UNPRESSED_OFF;
        }
    }
    
    
    return switch_state;
}




/***********************************************************************************/
#include "Sched.h"

// FOR scheduler
PIN_state_enm_t switch_pin_state[MAX_SWITCHs] = {LOW};  // the final switch state
PIN_state_enm_t previous_switch_state[MAX_SWITCHs] = {LOW};  //
PIN_state_enm_t counter_switch_state [MAX_SWITCHs] = {0};  //

void readSWITCHs_sch (void * arg);

Runnable_t SWITCH_Runnable =
{
    .func= readSWITCHs_sch,
    .priority = SWITCH_RUNNABLE_PRIORITY, 
    .priodicity_ticks=1,   //ms
    .first_delay=0,
    .arg = (void*)NO_INPUTS,
};

/*  the Runnable switch function  */
void readSWITCHs_sch (void * arg)
{
    PIN_state_enm_t current_switch_state[MAX_SWITCHs] = {LOW};  //
    for(int i=0; i< MAX_SWITCHs; i++)
    {
        current_switch_state[i] = GPIO_readPinVal(&GPIO_SWITCHPin[i], &switch_pin_state[i]);
        if (current_switch_state[i] == previous_switch_state[i])
        {
            counter_switch_state[i]++;
        }
        if (counter_switch_state[i] >= 5)
        {
            switch_pin_state[i] = current_switch_state[i];
            counter_switch_state[i] = 0;
        }
    }
}

void SWITCH_init_sch(void)
{
    SWITCH_init();
    Sched_registerRunnable(&SWITCH_Runnable);
}

uint8_t SWITCH_readState_sch(SWITCH_names_t SWITCH_name)
{
    SWITCH_state_t switch_state= SWITCH_UNPRESSED_OFF;
    if (SWITCH_cfg[SWITCH_name].active_state == SWITCH_activeHigh)
    {
        if (switch_pin_state[SWITCH_name] == PIN_HIGH)
        {
            switch_state= SWITCH_PRESSED_ON;
        }else
        {
            switch_state= SWITCH_UNPRESSED_OFF;
        }
    }
    else    //ACTIVE Low switch
    {
        if (switch_pin_state[SWITCH_name] == PIN_LOW)
        {
            switch_state= SWITCH_PRESSED_ON;
        }else
        {
            switch_state= SWITCH_UNPRESSED_OFF;
        }
    }
    

    return switch_state;
}