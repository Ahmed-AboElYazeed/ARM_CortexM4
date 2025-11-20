#include "GPIO/GPIO.h"



typedef struct {
    volatile uint32_t MODER;    // GPIO port mode register,               Address offset: 0x00
    volatile uint32_t OTYPER;   // GPIO port output type register,        Address offset: 0x04
    volatile uint32_t OSPEEDR;  // GPIO port output speed register,       Address offset: 0x08
    volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register,  Address offset: 0x0C
    volatile uint32_t IDR;      // GPIO port input data register,         Address offset: 0x10
    volatile uint32_t ODR;      // GPIO port output data register,        Address offset: 0x14
    volatile uint32_t BSRR;     // GPIO port bit set/reset register,      Address offset: 0x18
    volatile uint32_t LCKR;     // GPIO port configuration lock register, Address offset: 0x1C
    volatile uint32_t AFR[2];   // GPIO alternate function registers,     Address offset: 0x20-0x24
}GPIO_REG_t;

/*  //three methods for GPIO:
1. using enum and array
2. using macros and bit masking
3. using struct
*/




// GPIO MODE MASKS
#define ModeMSK_SHIFT       0
#define OutTypeMSK_SHIFT    2
#define PullMSK_SHIFT       4
#define SpeedMSK_SHIFT      6
#define GPIO_ModeMSK_BITS     0b11u
#define GPIO_OutTypeMSK_BITS  0b1u
#define GPIO_PullMSK_BITS     0b11u
#define GPIO_SpeedMSK_BITS    0b11u

#define GPIO_ModeMSK    (GPIO_ModeMSK_BITS      << ModeMSK_SHIFT)
#define GPIO_OutTypeMSK (GPIO_OutTypeMSK_BITS   << OutTypeMSK_SHIFT)
#define GPIO_PullMSK    (GPIO_PullMSK_BITS      << PullMSK_SHIFT)
#define GPIO_SpeedMSK   (GPIO_SpeedMSK_BITS     << SpeedMSK_SHIFT)





/*
typedef struct {
    uint32_t pin;   // pin number
    void * port;    // pointer to the register address
    uint8_t mode;      // binary contain the GPIO config
    GPIO_af_t alternateFunction;
}GPIO_pinCfg_t;
*/
/*          struct filler functions        */

uint8_t GPIO_identfyPin(GPIO_pinCfg_t * pinConfig, void * port, uint32_t pin) //GPIOA/B/C/D/E , pin number 0-15
{
    pinConfig->port = port;
    pinConfig->pin = pin;
    return 0;
}
uint8_t GPIO_setPinDirMode(GPIO_pinCfg_t * pinConfig, uint8_t dir)    //input, output, alternate, analog
{
    pinConfig->mode &= ~GPIO_ModeMSK; //clear the mode bits first
    pinConfig->mode |= (dir & GPIO_ModeMSK); //set the mode bits
    return 0;
}
uint8_t GPIO_setOutPinMode(GPIO_pinCfg_t * pinConfig, uint8_t outType, uint8_t pullType)  //push-pull/open-drain , pull-up/pull-down
{
    pinConfig->mode &= ~GPIO_OutTypeMSK; //clear the out type bits first
    pinConfig->mode |= ((outType << OutTypeMSK_SHIFT) & GPIO_OutTypeMSK); //set the out type bits


    pinConfig->mode &= ~GPIO_PullMSK; //clear the pull type bits first
    pinConfig->mode |= ((pullType << PullMSK_SHIFT) & GPIO_PullMSK); //set the pull type bits
    return 0;
}
// uint8_t GPIO_setPinSpeed(GPIO_pinCfg_t * pinConfig, uint8_t speed)
// {

// }


/*          user core functions          */
uint8_t GPIO_creatPin(GPIO_pinCfg_t * pinConfig)
{
    //casting the void pointer to a GPIO_REG_t pointer.
    volatile GPIO_REG_t *CastedPort =(volatile GPIO_REG_t *)pinConfig->port;

    //configure the pin according to the pinConfig struct values
    CastedPort->MODER &= ~(GPIO_ModeMSK_BITS << (pinConfig->pin * 2)); //clear the two bits first
    CastedPort->MODER |= (pinConfig->mode & GPIO_ModeMSK) << (pinConfig->pin * 2); //set the mode bits

    CastedPort->OTYPER &= ~(GPIO_OutTypeMSK_BITS << (pinConfig->pin)); //clear the output type bit first
    CastedPort->OTYPER |= ((pinConfig->mode & GPIO_OutTypeMSK) >> OutTypeMSK_SHIFT) << (pinConfig->pin); //set the output type bit

    CastedPort->PUPDR &= ~(GPIO_PullMSK_BITS << (pinConfig->pin * 2)); //clear the two bits first
    CastedPort->PUPDR |= ((pinConfig->mode & GPIO_PullMSK) >> PullMSK_SHIFT) << (pinConfig->pin * 2); //set the pull-up/pull-down bits

    CastedPort->OSPEEDR &= ~(GPIO_SpeedMSK_BITS << (pinConfig->pin * 2)); //clear the two bits first
    CastedPort->OSPEEDR |= ((pinConfig->mode & GPIO_SpeedMSK) >> SpeedMSK_SHIFT) << (pinConfig->pin * 2); //set the speed bits

    return 0;
}
uint8_t GPIO_setPinVal(GPIO_pinCfg_t * pinConfig, uint8_t value)
{
    //casting the void pointer to a GPIO_REG_t pointer.
    volatile GPIO_REG_t* CastedPort = (volatile GPIO_REG_t*) pinConfig->port;

    CastedPort->ODR &= ~(0b1u << pinConfig->pin);  // insert the last bit in the value into the ODR
    CastedPort->ODR |= ((value & 0b1u)<< pinConfig->pin);  // insert the last bit in the value into the ODR
    return 0;
}
uint8_t GPIO_readPinVal(GPIO_pinCfg_t * pinConfig, uint8_t *value)
{
    //casting the void pointer to a GPIO_REG_t pointer.
    volatile GPIO_REG_t* CastedPort = (volatile GPIO_REG_t*) pinConfig->port;

    *value = ((CastedPort->IDR) >> pinConfig->pin) & 0b1u;  //read bit
    return 0;
}

// NOTE: This assumes GPIO_REG_t has a member named 'ODR' for Output Data Register.
uint8_t GPIO_togglePin(GPIO_pinCfg_t * pinConfig)
{
    // Casting the void pointer to a GPIO_REG_t pointer (to access the register structure).
    volatile GPIO_REG_t* CastedPort = (volatile GPIO_REG_t*) pinConfig->port;
    CastedPort->ODR ^= (0b1u << pinConfig->pin);
    
    return 0;
}

// Atomic toggle using BSRR (Recommended for STM32)
uint8_t GPIO_togglePin_Atomic(GPIO_pinCfg_t * pinConfig)
{
    volatile GPIO_REG_t* CastedPort = (volatile GPIO_REG_t*) pinConfig->port;
    uint32_t pin_mask = (1U << pinConfig->pin);

    // Read the current state from the ODR
    // and write to the corresponding Set (BSx) or Reset (BRx) half of BSRR.
    if ((CastedPort->ODR & pin_mask) == 0)
    {
        // If the pin is LOW, write to the BSx (SET) section (low 16 bits)
        CastedPort->BSRR = pin_mask;
    }
    else
    {
        // If the pin is HIGH, write to the BRx (RESET) section (high 16 bits)
        CastedPort->BSRR = (pin_mask << 16);
    }
    
    return 0;
}
// uint8_t GPIO_selectAlternateFunc(GPIO_pinCfg_t * pinConfig, GPIO_af_t altFunc)
// {}


