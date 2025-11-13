#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include <stdio.h>

typedef enum{
    PORTA = ,
}GPIO_portName_t;

uint8_t GPIO_setPinDir(port, uint8_t pinNum);

uint8_t GPIO_setPin(port, uint8_t pinNum);
uint8_t GPIO_clearPin(port, uint8_t pinNum);
uint8_t GPIO_togglePin(port, uint8_t pinNum);

uint8_t GPIO_enablePinPullUP(port, uint8_t pinNum);
uint8_t GPIO_enablePinPullDOWN(port, uint8_t pinNum);


#endif