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
#include "Hserial/Hserial.h"

void recieveEndNotify (void)
{

}
void sendEndNotify (void)
{

}

int main()
{
    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    Rcc_enablePeripheralClk(Rcc_GPIOB);
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    LED_init();
    USART_cfg_t USART_cfg ={
        .baudrate =115200,
        .parity = 0,
        .cbf_Rx = recieveEndNotify,
        .cbf_Tx = sendEndNotify,
    };
    USART_init(USART1, &USART_cfg);
    uint8_t str[17] = "Ahmed AboElyazeed";
    Buffer_t theBuffer = {
        .buf = str,
        .len = 17,
        .transmettedLen = 0,
    };
    USART_sendBuffer(USART1, &theBuffer);
    uint8_t str2[17] = "xxxxx";
    volatile Buffer_t theBuffer2 = {
        .buf = str2,
        .len = 17,
        .transmettedLen = 0,
    };
    USART_reciveBuffer(USART1, &theBuffer2);

    LED_turnOFF(LED_WARNING);
    volatile int i =0;
    while (1)
    {
        if(theBuffer2.buf[theBuffer2.transmettedLen -1] == 'a')
        {
            i++;
            LED_turnON(LED_WARNING);
        }
        else if(theBuffer2.buf[theBuffer2.transmettedLen -1] == 'x')
        {
            LED_turnOFF(LED_WARNING);
        }
    }    
    return 0;
}