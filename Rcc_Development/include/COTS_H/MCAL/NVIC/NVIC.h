#ifndef NVIC_H
#define NVIC_H

/*
    The input parameter IRQn is the IRQ number. Possible “n” values depend on product. Refer to reference
   manual/datasheet of relevant STM32 product for related information
*/
//Intera Vector Table:
typedef enum{
    WWDG,
    EXTI16_PVD

}IRQn_t;

//Enables an interrupt or exception.
void NVIC_EnableIRQ(IRQn_t IRQn);  

//Disables an interrupt or exception.
void NVIC_DisableIRQ(IRQn_t IRQn);

//Sets the pending status of interrupt or exception to 1.
void NVIC_SetPendingIRQ(IRQn_t IRQn);

//Clears the pending status of interrupt or exception to 0.       
void NVIC_ClearPendingIRQ(IRQn_t IRQn);      

//Reads the pending status of interrupt or exception. This function returns non-zero value if the pending status is set to 1.
uint32_t NVIC_GetPendingIRQ(IRQn_t IRQn);

 //Sets the priority of an interrupt or exception with configurable priority level to 1.
void NVIC_SetPriority(IRQn_t IRQn, uint32_t priority);       

//Reads the priority of an interrupt or exception with configurable priority level. This function return the current priority level.
uint32_t NVIC_GetPriority(IRQn_t IRQn);  



//Set the priority grouping
void NVIC_SetPriorityGrouping(uint32_t priority_grouping);

//Return the IRQ number of the active interrupt      
uint32_t NVIC_GetActive (IRQn_t IRQn); 

//Reset the system
void NVIC_SystemReset (void);                                   

#endif