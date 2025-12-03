
#include <stdio.h>
#include <stdint.h>
#include <rcc/rcc.h>
#include <GPIO/GPIO.h>
#include <led/led.h>
#include "switch/switch.h"
#include "NVIC/NVIC.h"
#include "SYSTICK/SYSTICK.h"
#include "Sched.h"

void toggleLED (void * arg)
{
    if (SWITCH_readState_sch(SWITCH_FIRST) == SWITCH_PRESSED_ON)
    {
        LED_turnON((LED_names_t)arg);
    }
    else
    {
        LED_turnOFF((LED_names_t)arg);
    }
}



Runnable_t LED_Runnable =
{
    .func= toggleLED,
    .priority = LED_RUNNABLE_PRIORITY,
    .priodicity_ticks=5,   //ms
    .first_delay=0,
    .arg = (void*)LED_THIRD,
};

// Runnable_t LED_Runnable2 =
// {
//     .func= toggleLED,
//     .priority = 2,
//     .priodicity_ticks=2000,   //ms
//     .first_delay=0,
//     .arg = (void*)LED_WARNING,
// };

int main ()
{


    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    Rcc_enablePeripheralClk(Rcc_GPIOC);


    SWITCH_init_sch();
    LED_init();
    LED_turnOFF(LED_THIRD);
    LED_turnON(LED_THIRD);

    //__asm volatile ("CPSIE i");
    Sched_init(1);
    Sched_registerRunnable(&LED_Runnable);
    Sched_start();

    volatile int x=0;
    while (1)
    {
        x++;
    }

    return 0;
}



















// #include <stdio.h>
// #include <stdint.h>
// #include <rcc/rcc.h>
// #include <GPIO/GPIO.h>
// #include <led/led.h>
// #include "switch/switch.h"
// #include "NVIC/NVIC.h"
// #include "SYSTICK/SYSTICK.h"
// #include "Sched.h"
// #include "LCD/LCD.h"

// LCD_cfg_t LCD_cfg[LCD_NUMBER];


// int main()
// {
//     Rcc_init();
//     Rcc_enablePeripheralClk(Rcc_GPIOA);
//     LCD_init(&LCD_cfg[LCD_0]);
//     // LCD_writeChar(&LCD_cfg[LCD_0], 'z');
//     LCD_writeString(&LCD_cfg[LCD_0], "Zee");
//     return 0;
// }

























// void toggleLED (void * arg)
// {
//     if (SWITCH_readState_sch(SWITCH_FIRST) == SWITCH_PRESSED_ON)
//     {
//         LED_turnON((LED_names_t)arg);
//     }
//     else
//     {
//         LED_turnOFF((LED_names_t)arg);
//     }
// }



// Runnable_t LED_Runnable =
// {
//     .func= toggleLED,
//     .priority = 1,
//     .priodicity_ticks=5,   //ms
//     .first_delay=0,
//     .arg = (void*)LED_THIRD,
// };

// // Runnable_t LED_Runnable2 =
// // {
// //     .func= toggleLED,
// //     .priority = 2,
// //     .priodicity_ticks=2000,   //ms
// //     .first_delay=0,
// //     .arg = (void*)LED_WARNING,
// // };

// int main ()
// {


//     Rcc_init();
//     Rcc_enablePeripheralClk(Rcc_GPIOA);
//     Rcc_enablePeripheralClk(Rcc_GPIOC);


//     SWITCH_init_sch();
//     LED_init();
//     LED_turnOFF(LED_THIRD);
//     LED_turnON(LED_THIRD);

//     //__asm volatile ("CPSIE i");
//     Sched_init(1);
//     Sched_registerRunnable(&LED_Runnable);
//     Sched_start();

//     volatile int x=0;
//     while (1)
//     {
//         x++;
//     }

//     return 0;
// }
































// int main (void)
// {
//     Rcc_enablePeripheralClk(Rcc_GPIOA);
//     LED_init();


//     while (1)
//     {
//         LED_turnON(LED_THIRD);
//         for(int i=0; i<1000000; i++)
//         {
//             asm("NOP");
//         } 
//         LED_turnOFF(LED_THIRD);
//         for(int i=0; i<1000000; i++)
//         {
//             asm("NOP");
//         } 
//         LED_toggle(LED_THIRD);
//         for(int i=0; i<1000000; i++)
//         {
//             asm("NOP");
//         } 
//     }
//     return 0;
// }





























/*
void toggleLED (void * arg)
{
    LED_toggle((LED_names_t)arg);
}



Runnable_t LED_Runnable =
{
    .func= toggleLED,
    .priority = 1,
    .priodicity_ticks=1000,   //ms
    .first_delay=0,
    .arg = (void*)LED_GARAG,
};

Runnable_t LED_Runnable2 =
{
    .func= toggleLED,
    .priority = 2,
    .priodicity_ticks=2000,   //ms
    .first_delay=0,
    .arg = (void*)LED_WARNING,
};

int main ()
{


    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOC);

    //SWITCH_init();
    LED_init();
    LED_turnOFF(LED_GARAG);
    LED_turnON(LED_GARAG);

    //__asm volatile ("CPSIE i");
    Sched_init(1);
    Sched_registerRunnable(&LED_Runnable);
    Sched_registerRunnable(&LED_Runnable2);
    Sched_start();

    volatile int x=0;
    while (1)
    {
        x++;
    }

    return 0;
}
*/



























// #define TEST 25

// void SYSTICK_ISR_func (void)
// {
//     LED_toggle(LED_GARAG);
// }

// void fun ()
// {
//     __asm volatile ("CPSIE i");
// }

// int main (void)
// {


//     // NVIC_EnableIRQ(TEST);
//     // //NVIC_SetPriority(25,(0b1110ul<<4));
//     // //volatile int readPending =0;

//     Rcc_init();
//     Rcc_enablePeripheralClk(Rcc_GPIOC);

//     fun();
    
//     // SYSTICK_Init(1);
//     // SYSTICK_setValue(16000000);

//     SWITCH_init();
//     LED_init();
//     LED_turnOFF(LED_GARAG);
//     LED_turnON(LED_GARAG);

//     // SYSTICK_confgCallBackFun(SYSTICK_ISR_func);
//     // SYSTICK_start();

//     volatile int x=4;
//     while (1)
//     {
//         LED_toggle(LED_GARAG);
//         SYSTICK_WaitBlocking_ms(1000);
//     }
//     // while(1)
//     // {
//     //     // if (SWITCH_readState(SWITCH_FIRST) == SWITCH_PRESSED_ON)
//     //     // {
//     //     //     for (volatile int i=0; i<10000; i++);
//     //     //     LED_turnON(LED_GARAG);
//     //     // }
//     //     // if (SWITCH_readState(SWITCH_FIRST) == SWITCH_UNPRESSED_OFF)
//     //     // {
//     //     //     LED_turnOFF(LED_GARAG);
//     //     // }
//     //     NVIC_SetPendingIRQ(TEST);
//     //     readPending = NVIC_GetPendingIRQ(TEST);
//     //     if (readPending)
//     //     {
//     //         NVIC_ClearPendingIRQ(TEST);
//     //         LED_toggle(LED_GARAG);
//     //         //for (volatile int i=0; i<1000000; i++);
//     //     }
//     //     NVIC_SetPendingIRQ(TEST);
        
        
//     // }
//     return 0;
// }





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