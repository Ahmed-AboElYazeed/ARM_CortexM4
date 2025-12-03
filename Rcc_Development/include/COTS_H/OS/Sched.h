#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>

// #define MAX_RUNNABLE 5      // assumed
#define NULLPTR ((void*)0)

typedef void (*cbf_t) (void*);

// remote used priority         <<<<<<----------- NOTE
/*
    switch driver: readSWITCHs === 10
*/
typedef enum{
    SWITCH_RUNNABLE_PRIORITY,
    LED_RUNNABLE_PRIORITY,
    MAX_RUNNABLE
}Runnable_Priority_t;

typedef enum {
    ALL_GOOD,
    NULL_RUNNABLE,
    NULL_FUNC
}ErrState_enu_t;

typedef struct 
{
    cbf_t func;
    uint32_t priority;
    uint32_t priodicity_ticks;
    uint32_t first_delay;
    void* arg;
}Runnable_t;

ErrState_enu_t Sched_init (uint32_t tickTime);
ErrState_enu_t Sched_registerRunnable (Runnable_t * Runnable);
void Sched_start ();

#endif