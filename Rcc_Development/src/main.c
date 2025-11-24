
#include <stdio.h>
#include <stdint.h>
#include <rcc/rcc.h>
#include <GPIO/GPIO.h>
#include <led/led.h>
#include "switch/switch.h"
#include "NVIC/NVIC.h"

int main (void)
{

    NVIC_EnableIRQ(4);

    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    SWITCH_init();
    LED_init();
    LED_turnOFF(LED_GARAG);
    while (1)
    {
        // if (SWITCH_readState(SWITCH_FIRST) == SWITCH_PRESSED_ON)
        // {
        //     for (volatile int i=0; i<10000; i++);
        //     LED_turnON(LED_GARAG);
        // }
        // if (SWITCH_readState(SWITCH_FIRST) == SWITCH_UNPRESSED_OFF)
        // {
        //     LED_turnOFF(LED_GARAG);
        // }
        LED_toggle(LED_GARAG);
        for (volatile int i=0; i<1000000; i++);
        
    }
    return 0;
}





//accedently ran one time
    // Rcc_clkSource_t sysClkSource= HSI_CLK;
    // pllCongfig_t pllConfig;
    // pllConfig.pllSource= HSI_CLK;
    // pllConfig.pllM= 10;
    // pllConfig.pllN= 10;
    // pllConfig.pllP= 10;
    // pllConfig.pllQ= 10;
    // while (1)
    // {
    //     printf("%d", 10);
    //     Rcc_setSystemClk(sysClkSource);
    //     Rcc_getSystemClk(&sysClkSource);
    //     Rcc_PllConfig(&pllConfig);

    // }
//when 

//void Rcc_PllConfig(pllCongfig_t* pllConfig)
// {
//     Rcc_clkSource_t currentClkSource;
//     // Get the current system clock source
//     Rcc_getSystemClk(&currentClkSource);

//     /*
//         OFF
//         HSI -> PLL

//         HSE -> PLL
//     */
//    if (HSI_CLK == pllConfig->pllSource)
//    {
    
//    }
// }















/*                  codes                   */





/*              testing gpio driver

int main (void)
{
// OUTPUT PIN CONFIGURATION EXAMPLE
    void * port= GPIOC;
    uint32_t pin= 13;
    uint8_t value= 1; //HIGH
    GPIO_pinCfg_t motorPin;
    motorPin.mode=0;
        Rcc_enablePeripheralClk(((uint64_t)0b0001 << 32)  |  (0b1 << 2)); //GPIOC
    GPIO_identfyPin(&motorPin,port,pin); //GPIOA/B/C/D/E , pin number 0-15
    GPIO_setPinDirMode(&motorPin,OUTPUT);  //input, output, alternate, analog
    //GPIO_setOutPinMode(&motorPin,PUSH_PULL,PULL_UP);   //push-pull/open-drain , pull-up/pull-down
    //GPIO_selectAlternateFunc(&motorPin, TIM1_TIM2); 

    GPIO_creatPin(&motorPin);

    while (1)
    {
        GPIO_setPinVal(&motorPin,0);
        GPIO_readPinVal(&motorPin, &value);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        }  
        GPIO_setPinVal(&motorPin,1);  
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        }    
    }
    return 0;
}

*/





/*                  testing gpio read

int main()
{
// IN PIN CONFIGURATION EXAMPLE
    void * port= GPIOC;
    uint32_t pin= 14;
    uint8_t value; //HIGH
    GPIO_pinCfg_t sensorPin;
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    GPIO_identfyPin(&sensorPin,port,pin); //GPIOA/B/C/D/E , pin number 0-15
    GPIO_setPinDirMode(&sensorPin,INPUT);  //input, output, alternate, analog
    //GPIO_setOutPinMode(&sensorPin,PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
    //GPIO_selectAlternateFunc(&sensorPin, TIM1);
    
    GPIO_creatPin(&sensorPin);

    
        GPIO_readPinVal(&sensorPin, &value);
        GPIO_readPinVal(&sensorPin, &value);
        GPIO_readPinVal(&sensorPin, &value);
        GPIO_readPinVal(&sensorPin, &value);


    while (1)
    {
        GPIO_readPinVal(&sensorPin, &value);
    }
    return 0;
}
*/






/*                  testing led driver

int main (void)
{
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    LED_init();


    while (1)
    {
        LED_turnON(LED_WARNING);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        } 
        LED_turnOFF(LED_WARNING);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        } 
        LED_toggle(LED_GARAG);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        } 
    }
    return 0;
}

*/



/*               testing led driver

int main (void)
{
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    LED_init();


    while (1)
    {
        LED_turnON(LED_WARNING);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        } 
        LED_turnOFF(LED_WARNING);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        } 
        LED_toggle(LED_GARAG);
        for(int i=0; i<1000000; i++)
        {
            asm("NOP");
        } 
    }
    return 0;
}


*/


/*              testing switch

int main (void)
{
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    SWITCH_init();
    LED_init();
    LED_turnOFF(LED_GARAG);
    while (1)
    {
        if (SWITCH_readState(SWITCH_FIRST) == SWITCH_PRESSED_ON)
        {
            for (volatile int i=0; i<10000; i++);
            LED_turnON(LED_GARAG);
        }
        if (SWITCH_readState(SWITCH_FIRST) == SWITCH_UNPRESSED_OFF)
        {
            LED_turnOFF(LED_GARAG);
        }
        
        
    }
    return 0;
}

*/