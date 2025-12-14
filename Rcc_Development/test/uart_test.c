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


int main()
{
    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    Rcc_enablePeripheralClk(Rcc_GPIOB);
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    LED_init();
    USART_init(USART1, NULL);
    uint8_t str[17] = "Ahmed AboElyazeed";
    Buffer_t theBuffer = {
        .buf = str,
        .len = 17,
    };
    USART_sendBuffer(USART1, theBuffer);

    USART_reciveBuffer(USART1, theBuffer);
    while (1)
    {
        int i =0;
        if(theBuffer.buf[i] == 'x')
        {
            i++;
            LED_toggle(LED_WARNING);
        }
    }    
    return 0;
}
