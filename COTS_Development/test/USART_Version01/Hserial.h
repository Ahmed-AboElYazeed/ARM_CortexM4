#ifndef HSERIAL_H
#define HSERIAL_H

#include "UART/uart.h"

void Hserial_init();
void Hserial_sendBuffer(Buffer_t* TxBuf);
void Hserial_recieveBuffer(Buffer_t* RxBuf);

#endif