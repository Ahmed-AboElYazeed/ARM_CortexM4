#include <stdint.h>
#include "NVIC/NVIC.h"
#include "NVIC/NVIC_prv.h"
#include "std_bitUtillity.h"

/*
    volatile uint32_t x=&NVIC_ISERx_VALUE_f( ((uint32_t)(IRQn/32)));
    volatile uint32_t Y=&NVIC_ICERx_VALUE_f( ((uint32_t)(IRQn/32)));
    volatile uint32_t E=&NVIC_ISPRx_VALUE_f( ((uint32_t)(IRQn/32)));
    volatile uint32_t W=&NVIC_ICPRx_VALUE_f( ((uint32_t)(IRQn/32)));
    volatile uint32_t C=&NVIC_IABRx_VALUE_f( ((uint32_t)(IRQn/32)));

    volatile uint32_t S= &NVIC_IPRx_VALUE_f( ((uint32_t)(IRQn/4)));
*/



//Enables an interrupt or exception.
void NVIC_EnableIRQ(IRQn_t IRQn)
{
        //uint8_t timeOut =50;
    //                                             \/ set the bit
    NVIC_ISERx_VALUE_f( ((uint32_t)(IRQn/32))) |= (0b1u << IRQn%32);
    //                                 ^Byte number           ^Bit number

    //i think it does not worth a time out check. 
        // while(0b1u != READ_BIT(NVIC_ISERx_VALUE_f( ((uint32_t)(IRQn/32))), IRQn%32) && timeOut--); //Wait until Bit is set
        // if (timeOut =< 0)
        // {
        //     //return ErrorState;
        // }
}

//Disables an interrupt or exception.
void NVIC_DisableIRQ(IRQn_t IRQn)
{
    //                                             \/ set the bit
    NVIC_ICERx_VALUE_f( ((uint32_t)(IRQn/32))) |= (0b1u << IRQn%32);
    //                                 ^Byte number           ^Bit number
}

//Sets the pending status of interrupt or exception to 1.
void NVIC_SetPendingIRQ(IRQn_t IRQn)
{
    //                                             \/ set the bit
    NVIC_ISPRx_VALUE_f( ((uint32_t)(IRQn/32))) |= (0b1u << IRQn%32);
    //                                 ^Byte number           ^Bit number
}

//Clears the pending status of interrupt or exception to 0.       
void NVIC_ClearPendingIRQ(IRQn_t IRQn)     
{
    //                                             \/ set the bit
    NVIC_ICPRx_VALUE_f( ((uint32_t)(IRQn/32))) |= (0b1u << IRQn%32);
    //                                 ^Byte number           ^Bit number
}

//Reads the pending status of interrupt or exception. This function returns non-zero value if the pending status is set to 1.
uint32_t NVIC_GetPendingIRQ(IRQn_t IRQn)     
{
    return READ_BIT(NVIC_ISPRx_VALUE_f(((uint32_t)(IRQn/32))), IRQn%32);
    //                                               ^Byte number ^Bit number
}

/* Sets the priority of an interrupt or exception with configurable priority level to 1.
 // priority range: 16 -> 240    (priority <= 15) >==> 0  &&  (priority >=241) >==> 240
    example: 
            NVIC_SetPriority(25,(0b1110ul<<4));
 */
void NVIC_SetPriority(IRQn_t IRQn, uint32_t priority)       // 0b1111xxxx << bit number
{
    NVIC_IPRx_VALUE_f( ((uint32_t)(IRQn/4))) |= ((0b11110000ul & priority) << ((IRQn%4)*8));
    //                                 ^Byte number                                ^Bit number
}

//Reads the priority of an interrupt or exception with configurable priority level. This function return the current priority level.
uint32_t NVIC_GetPriority(IRQn_t IRQn) 
{
    return ( NVIC_IPRx_VALUE_f( ((uint32_t)(IRQn/4))) ) >> ((IRQn%4)*8);        //returned value: priority range: 16 -> 240 
}




//Set the priority grouping
void NVIC_SetPriorityGrouping(uint32_t priority_grouping)
{
    // Must write on "Application interrupt and reset control register (AIRCR)"
    //To write to this register, you must write 0x5FA to the VECTKEY field, otherwise the processor ignores the write.
    AIRCR_REG |= ((0x5FA <<16) & ((priority_grouping & 0b111ul) << 8));
    
}

//Return the IRQ number of the active interrupt      
uint32_t NVIC_GetActive (IRQn_t IRQn)
{
    return READ_BIT(NVIC_IABRx_VALUE_f(((uint32_t)(IRQn/32))), IRQn%32);
    //                                               ^Byte number ^Bit number
}

//Reset the system
void NVIC_SystemReset (void)
{
    
}