#include <stdio.h>

unsigned volatile int __attribute__((section(".LED_CFG_section"))) LED_cfg =100;

int main()
{
    volatile int * ptr = &LED_cfg;
    LED_cfg = 100;
    LED_cfg = 10;
    LED_cfg = 11;
    LED_cfg = 12;
    *ptr = 50;
}