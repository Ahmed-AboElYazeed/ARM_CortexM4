#include "rcc/rcc.h"
#include "GPIO/GPIO.h"
#include "led/led.h"
#include "switch/switch.h"
#include "NVIC/NVIC.h"
#include "SYSTICK/SYSTICK.h"
#include "Sched.h"
#include "LCD/LCD.h"
#include "dotMatrix/dotMatrix.h"
#include "UART/uart.h"
#include "DMA/DMA.h"


int main()
{
    Rcc_init();
    volatile uint8_t arr1[5] = {1,2,3,4,5};
    volatile uint8_t arr2[6] = {0};
    volatile Buffer_t theBuffer = {
        .buf = (uint8_t*)arr2,
        .len = 5,
    };
    DMA_memCopy((uint32_t)arr2,(uint32_t)arr1,theBuffer.len);
    while (1)
    {
        // USART_reciveBuffer(USART1, theBuffer);
        for(uint32_t i=0; i<1000000000; i++)
        {
            asm("NOP");
        } 
    }    
    return 0;
}