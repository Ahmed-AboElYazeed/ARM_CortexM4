#ifndef USART_H
#define USART_H

#include "std_int.h"


// #define USART1 _USART1
// #define USART2 _USART2
// #define USART6 _USART6
typedef enum{
    USART1,
    USART2,
    USART6
}USART_id_t;

// void (*cbf)(void);

typedef struct{
    uint32_t baudrate;
    uint32_t parity;
    void (*cbf_Rx)(void);
    void (*cbf_Tx)(void);
    uint8_t enable_DMA_mode;
}USART_cfg_t;

typedef struct{
    uint8_t* buf;
    uint32_t len;
    uint32_t transmettedLen;
}Buffer_t;

void USART_init(USART_id_t USART_id, USART_cfg_t* cfg);
void USART_sendBuffer(USART_id_t USART_id, Buffer_t* buffer);
void USART_reciveBuffer(USART_id_t USART_id, Buffer_t* buffer);
uint32_t USART_addressGetter(USART_id_t USART_id);
void USART_sendByte_Polling(USART_id_t USART_id, uint8_t data);
uint8_t USART_receiveByte_Polling(USART_id_t USART_id);
// uint8_t USART_receiveByte_Polling(USART_id_t USART_id, uint8_t* data, uint32_t timeout_ms);

//for DMA_USART (Hserial) using USART1
void USART1_enable_DMAtransmitter ();
void USART1_disable_DMAtransmitter ();
void USART1_enable_DMAreciever ();
void USART1_disable_DMAreciever ();

#endif