#ifndef NVIC_H
#define NVIC_H

/*
    The input parameter IRQn is the IRQ number. Possible “n” values depend on product. Refer to reference
   manual/datasheet of relevant STM32 product for related information
*/
//Intera Vector Table:
//Interrupt Vector Table for STM32F401xB/D/E
typedef enum {
    IRQ_WWDG = 0,                    // Window Watchdog interrupt
    IRQ_EXTI16_PVD = 1,              // EXTI Line 16 interrupt / PVD through EXTI line detection interrupt
    IRQ_EXTI21_TAMP_STAMP = 2,       // EXTI Line 21 interrupt / Tamper and TimeStamp interrupts through the EXTI line
    IRQ_EXTI22_RTC_WKUP = 3,         // EXTI Line 22 interrupt / RTC Wakeup interrupt through the EXTI line
    IRQ_FLASH = 4,                   // Flash global interrupt
    IRQ_RCC = 5,                     // RCC global interrupt
    IRQ_EXTI0 = 6,                   // EXTI Line0 interrupt
    IRQ_EXTI1 = 7,                   // EXTI Line1 interrupt
    IRQ_EXTI2 = 8,                   // EXTI Line2 interrupt
    IRQ_EXTI3 = 9,                   // EXTI Line3 interrupt
    IRQ_EXTI4 = 10,                  // EXTI Line4 interrupt
    IRQ_DMA1_Stream0 = 11,           // DMA1 Stream0 global interrupt
    IRQ_DMA1_Stream1 = 12,           // DMA1 Stream1 global interrupt
    IRQ_DMA1_Stream2 = 13,           // DMA1 Stream2 global interrupt
    IRQ_DMA1_Stream3 = 14,           // DMA1 Stream3 global interrupt
    IRQ_DMA1_Stream4 = 15,           // DMA1 Stream4 global interrupt
    IRQ_DMA1_Stream5 = 16,           // DMA1 Stream5 global interrupt
    IRQ_DMA1_Stream6 = 17,           // DMA1 Stream6 global interrupt
    IRQ_ADC = 18,                    // ADC1 global interrupts
    IRQ_EXTI9_5 = 23,                // EXTI Line[9:5] interrupts
    IRQ_TIM1_BRK_TIM9 = 24,          // TIM1 Break interrupt and TIM9 global interrupt
    IRQ_TIM1_UP_TIM10 = 25,          // TIM1 Update interrupt and TIM10 global interrupt
    IRQ_TIM1_TRG_COM_TIM11 = 26,     // TIM1 Trigger and Commutation interrupts and TIM11 global interrupt
    IRQ_TIM1_CC = 27,                // TIM1 Capture Compare interrupt
    IRQ_TIM2 = 28,                   // TIM2 global interrupt
    IRQ_TIM3 = 29,                   // TIM3 global interrupt
    IRQ_TIM4 = 30,                   // TIM4 global interrupt
    IRQ_I2C1_EV = 31,                // I2C1 event interrupt
    IRQ_I2C1_ER = 32,                // I2C1 error interrupt
    IRQ_I2C2_EV = 33,                // I2C2 event interrupt
    IRQ_I2C2_ER = 34,                // I2C2 error interrupt
    IRQ_SPI1 = 35,                   // SPI1 global interrupt
    IRQ_SPI2 = 36,                   // SPI2 global interrupt
    IRQ_USART1 = 37,                 // USART1 global interrupt
    IRQ_USART2 = 38,                 // USART2 global interrupt
    IRQ_EXTI15_10 = 40,              // EXTI Line[15:10] interrupts
    IRQ_EXTI17_RTC_Alarm = 41,       // EXTI Line 17 interrupt / RTC Alarms (A and B) through EXTI line interrupt
    IRQ_EXTI18_OTG_FS_WKUP = 42,     // EXTI Line 18 interrupt / USB On-The-Go FS Wakeup through EXTI line interrupt
    IRQ_DMA1_Stream7 = 47,           // DMA1 Stream7 global interrupt
    IRQ_SDIO = 49,                   // SDIO global interrupt
    IRQ_TIM5 = 50,                   // TIM5 global interrupt
    IRQ_SPI3 = 51,                   // SPI3 global interrupt
    IRQ_DMA2_Stream0 = 56,           // DMA2 Stream0 global interrupt
    IRQ_DMA2_Stream1 = 57,           // DMA2 Stream1 global interrupt
    IRQ_DMA2_Stream2 = 58,           // DMA2 Stream2 global interrupt
    IRQ_DMA2_Stream3 = 59,           // DMA2 Stream3 global interrupt
    IRQ_DMA2_Stream4 = 60,           // DMA2 Stream4 global interrupt
    IRQ_OTG_FS = 67,                 // USB On The Go FS global interrupt
    IRQ_DMA2_Stream5 = 68,           // DMA2 Stream5 global interrupt
    IRQ_DMA2_Stream6 = 69,           // DMA2 Stream6 global interrupt
    IRQ_DMA2_Stream7 = 70,           // DMA2 Stream7 global interrupt
    IRQ_USART6 = 71,                 // USART6 global interrupt
    IRQ_I2C3_EV = 72,                // I2C3 event interrupt
    IRQ_I2C3_ER = 73,                // I2C3 error interrupt
    IRQ_FPU = 81,                    // FPU global interrupt
    IRQ_SPI4 = 84                    // SPI4 global interrupt
} IRQn_t;

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