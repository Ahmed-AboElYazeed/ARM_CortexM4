#include "led/led.h"
#include "GPIO/GPIO.h"

extern LED_cfg_t LED_cfg[];
// initializing glopal arr of struct of GPIO_pins
GPIO_pinCfg_t GPIO_LEDPin[LED_LEN]; 

void LED_init()
{
    for (int i=0; i< LED_LEN; i++)
    {
        GPIO_identfyPin(&GPIO_LEDPin[i],LED_cfg[i].port,LED_cfg[i].pin); //GPIOA/B/C/D/E , pin number 0-15
        GPIO_setPinDirMode(&GPIO_LEDPin[i],OUTPUT);  //input, output, alternate, analog
        GPIO_setOutPinMode(&GPIO_LEDPin[i],PUSH_PULL,LED_cfg[i].pullType);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&GPIO_LEDPin[i], DIO); 
        GPIO_creatPin(&GPIO_LEDPin[i]);
    }

    //LED_cfg[i].port
    
}
uint8_t LED_turnON(LED_names_t LED_name)
{
    if (LED_cfg[LED_name].active_state == LED_activeHigh)
    {
        GPIO_setPinVal(&GPIO_LEDPin[LED_name], HIGH);
        return LED_ON;
    }
    else if (LED_cfg[LED_name].active_state == LED_activeLow)
    {
        GPIO_setPinVal(&GPIO_LEDPin[LED_name], LOW);
        return LED_ON;
    }
    else
    {
        return LED_ERR;
    }
}
uint8_t LED_turnOFF(LED_names_t LED_name)
{
    if (LED_cfg[LED_name].active_state == LED_activeHigh)
    {
        GPIO_setPinVal(&GPIO_LEDPin[LED_name], LOW);
        return LED_OFF;
    }
    else if (LED_cfg[LED_name].active_state == LED_activeLow)
    {
        GPIO_setPinVal(&GPIO_LEDPin[LED_name], HIGH);
        return LED_OFF;
    }
    else
    {
        return LED_ERR;
    }
}
uint8_t LED_toggle(LED_names_t LED_name)
{
    GPIO_togglePin(&GPIO_LEDPin[LED_name]);
    return 0;
}
