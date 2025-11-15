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
        GPIO_setOutPinMode(&GPIO_LEDPin[i],PUSH_PULL,PULL_UP);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&GPIO_LEDPin[i], DIO); 
        GPIO_creatPin(&GPIO_LEDPin[i]);
    }

    //LED_cfg[i].port
    
}
uint8_t LED_turnON(LED_names_t LED_name)
{
    GPIO_setPinVal(&GPIO_LEDPin[LED_name], 1);
    return 0;
}
uint8_t LED_turnOFF(LED_names_t LED_name)
{
    GPIO_setPinVal(&GPIO_LEDPin[LED_name], 0);
    return 0;
}
uint8_t LED_toggle(LED_names_t LED_name)
{
    GPIO_togglePin(&GPIO_LEDPin[LED_name]);
    return 0;
}
