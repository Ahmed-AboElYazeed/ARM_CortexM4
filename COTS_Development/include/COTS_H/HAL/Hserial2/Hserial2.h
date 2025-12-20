#ifndef HSERIAL_H       // if you included two Hserial.h headers:
#define HSERIAL_H       // only one of the Hserial dirvers would be included (which is defined first)

#include "UART2/uart2.h"

void Hserial_init();
void Hserial_sendBuffer(Buffer_t* TxBuf);
void Hserial_recieveBuffer(Buffer_t* RxBuf);

#endif