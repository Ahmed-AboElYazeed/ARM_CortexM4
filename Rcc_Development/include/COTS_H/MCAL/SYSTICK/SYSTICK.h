#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

void SYSTICK_Init(uint64_t clk, uint32_t prescaller);

void SYSTICK_confgCallBackFun(void (*fun)(void));

void SYSTICK_setValue(uint32_t value);

void SYSTICK_start();

void SYSTICK_stop();

#endif