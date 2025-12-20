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

uint8_t str[12] = "recived cbf\n";
Buffer_t theBuffer = {
    .buf = str,
    .len = 2,
};
void reciveComplete (void)
{
    USART_sendBuffer(USART1, theBuffer);
}

void transmitComplete (void)
{
    // theBuffer.len = 5;
    USART_reciveBuffer(USART1, theBuffer);
}

int main()
{
    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    Rcc_enablePeripheralClk(Rcc_GPIOB);
    Rcc_enablePeripheralClk(Rcc_GPIOC);
    LED_init();
    USART_cfg_t USART_cfg = {
        .baudrate = 115200,
        .parity = 0, 
        .cbf_Rx = reciveComplete,
        .cbf_Tx = transmitComplete,
    };
    USART_init(USART1, &USART_cfg);
    uint8_t str[20] = "stm send: starting \n";
    Buffer_t theBuffer = {
        .buf = str,
        .len = 20,
    };
    USART_sendBuffer(USART1, theBuffer);

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