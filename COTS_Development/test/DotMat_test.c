
#include <stdio.h>
#include <stdint.h>
#include <rcc/rcc.h>
#include <GPIO/GPIO.h>
#include <led/led.h>
#include "switch/switch.h"
#include "NVIC/NVIC.h"
#include "SYSTICK/SYSTICK.h"
#include "Sched.h"
#include "LCD/LCD.h"
#include "dotMatrix/dotMatrix.h"

int main()
{
    Rcc_init();
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    Rcc_enablePeripheralClk(Rcc_GPIOB);
    Rcc_enablePeripheralClk(Rcc_GPIOC);

    DotMat_init(DOTMAT_0);
    DotMat_writeRow(DOTMAT_0,COL_0,ROW_0);
    __asm volatile ("CPSIE i");
    DotMat_asynch_init();

    Sched_init(1);
    Sched_start();
    return 0;
}
