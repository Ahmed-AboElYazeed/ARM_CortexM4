#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>
#include <stdio.h>


//for also compiling with g++ 
#ifdef __cplusplus
namspace MCAL {
    namespace GPIO{
        extern "C" {
#endif


#define GPIOA_BASEADDRESS (0x40020000)
#define GPIOB_BASEADDRESS (0x40020400)
#define GPIOC_BASEADDRESS (0x40020800)
#define GPIOD_BASEADDRESS (0x40020C00)
#define GPIOE_BASEADDRESS (0x40021000)
#define GPIOH_BASEADDRESS (0x40021C00)

#define GPIOA ((void*)GPIOA_BASEADDRESS)
#define GPIOB ((void*)GPIOB_BASEADDRESS)
#define GPIOC ((void*)GPIOC_BASEADDRESS)
#define GPIOD ((void*)GPIOD_BASEADDRESS)
#define GPIOE ((void*)GPIOE_BASEADDRESS)
#define GPIOH ((void*)GPIOH_BASEADDRESS)




/*  // 1. mode
00: Input (reset state)
01: General purpose output mode
10: Alternate function mode
11: Analog mode*/
#define INPUT               0b00u
#define OUTPUT              0b01u
#define ALTERNATE_FUNCTION  0b10u
#define ANALOG              0b11u



/*  //2. output type
0: Output push-pull (reset state)
1: Output open-drain*/
#define PUSH_PULL   0b0u
#define OPEN_DRAIN  0b1U

/*  //3. output speed
00: Low speed
01: Medium speed
10: High speed
11: Very high speed*/
#define LOW_SPEED       0b00u
#define MEDIAM_SPEED    0b01u
#define HIGH_SPEED      0b10u
#define VERY_HIGH_SPEED 0b11u

/*  //4. pull-up/pull-down
00: No pull-up, pull-down
01: Pull-up
10: Pull-down
11: Reserved*/
#define NO_PULL     0b00u
#define PULL_UP     0b01u
#define PULL_DOWN   0b10u

// GPIO PIN MODES                   //speed                 push up/down        output type     mode/dir
#define GPIO_MODE_OUT_PP_PU_LS  (LOW_SPEED << 6)        | (PULL_UP << 4)    | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PD_LS  (LOW_SPEED << 6)        | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PU_MS  (MEDIAM_SPEED << 6)     | (PULL_UP << 4)    | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PD_MS  (MEDIAM_SPEED << 6)     | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PU_HS  (HIGH_SPEED << 6)       | (PULL_UP << 4)    | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PD_HS  (HIGH_SPEED << 6)       | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PU_VS  (VERY_HIGH_SPEED << 6)  | (PULL_UP << 4)    | (PUSH_PULL << 2) | OUTPUT
#define GPIO_MODE_OUT_PP_PD_VS  (VERY_HIGH_SPEED << 6)  | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | OUTPUT


#define GPIO_MODE_OUT_OD_PU_LS  (LOW_SPEED << 6)        | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PD_LS  (LOW_SPEED << 6)        | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PU_MS  (MEDIAM_SPEED << 6)     | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PD_MS  (MEDIAM_SPEED << 6)     | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PU_HS  (HIGH_SPEED << 6)       | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PD_HS  (HIGH_SPEED << 6)       | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PU_VS  (VERY_HIGH_SPEED << 6)  | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | OUTPUT
#define GPIO_MODE_OUT_OD_PD_VS  (VERY_HIGH_SPEED << 6)  | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | OUTPUT


#define GPIO_MODE_IN_PP_PU_LS   (LOW_SPEED << 6)        | (PULL_UP << 4)    | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PD_LS   (LOW_SPEED << 6)        | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PU_MS   (MEDIAM_SPEED << 6)     | (PULL_UP << 4)    | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PD_MS   (MEDIAM_SPEED << 6)     | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PU_HS   (HIGH_SPEED << 6)       | (PULL_UP << 4)    | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PD_HS   (HIGH_SPEED << 6)       | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PU_VS   (VERY_HIGH_SPEED << 6)  | (PULL_UP << 4)    | (PUSH_PULL << 2) | INPUT
#define GPIO_MODE_IN_PP_PD_VS   (VERY_HIGH_SPEED << 6)  | (PULL_DOWN << 4)  | (PUSH_PULL << 2) | INPUT


#define GPIO_MODE_IN_OD_PU_LS   (LOW_SPEED << 6)        | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PD_LS   (LOW_SPEED << 6)        | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PU_MS   (MEDIAM_SPEED << 6)     | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PD_MS   (MEDIAM_SPEED << 6)     | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PU_HS   (HIGH_SPEED << 6)       | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PD_HS   (HIGH_SPEED << 6)       | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PU_VS   (VERY_HIGH_SPEED << 6)  | (PULL_UP << 4)    | (OPEN_DRAIN << 2) | INPUT
#define GPIO_MODE_IN_OD_PD_VS   (VERY_HIGH_SPEED << 6)  | (PULL_DOWN << 4)  | (OPEN_DRAIN << 2) | INPUT


/*
// alternate function
0000: AF0
0001: AF1
0010: AF2
0011: AF3
0100: AF4
0101: AF5
0110: AF6
0111: AF7
1000: AF8
1001: AF9
1010: AF10
1011: AF11
1100: AF12
1101: AF13
1110: AF14
1111: AF15
*/
typedef enum {
    system=0,
    DIO =0,
    GPIO=0,
    TIM1 =1,
    TIM2 =1,
    TIM3 =2,
    TIM4 =2,
    TIM5 =2,
    TIM9 =3,
    TIM10 =3,
    TIM11 =3,
    I2C1_I2C3,
    SPI1_SPI2_SPI3,
    SPI4_GPIOs,
    USART1_USART2_USART3,
    USART4_USART5,
    USART6_GPIOs,
    UART7_UART8,
    CAN1_CAN2,
    OTG_FS_OTG_HS,
    ETH,
    FSMC_SDIO,
    DCMI
}GPIO_af_t;

typedef struct {
    uint32_t pin;   // pin number
    void * port;    // pointer to the register address
    uint8_t mode;      // binary contain the GPIO config
    GPIO_af_t alternateFunction;
}GPIO_pinCfg_t;


/*
1. initialize the struct
2. call the helper functions to set the desired config
3. call the creat pin (setPinonfig) function*/


/*          struct filler functions        */
uint8_t GPIO_identfyPin(GPIO_pinCfg_t * pinConfig, void * port, uint32_t pin); //GPIOA/B/C/D/E , pin number 0-15
uint8_t GPIO_setPinDirMode(GPIO_pinCfg_t * pinConfig, uint8_t dir);    //input, output, alternate, analog
uint8_t GPIO_setOutPinMode(GPIO_pinCfg_t * pinConfig, uint8_t outType, uint8_t pullType);  //push-pull/open-drain , pull-up/pull-down

/*          user core functions          */
uint8_t GPIO_creatPin(GPIO_pinCfg_t * pinConfig);

uint8_t GPIO_selectAlternateFunc(GPIO_pinCfg_t * pinConfig, GPIO_af_t altFunc);
uint8_t GPIO_setPinVal(GPIO_pinCfg_t * pinConfig, uint8_t value);
uint8_t GPIO_readPinVal(GPIO_pinCfg_t * pinConfig, uint8_t *value); 
uint8_t GPIO_togglePin(GPIO_pinCfg_t * pinConfig);

uint8_t GPIO_togglePin_Atomic(GPIO_pinCfg_t * pinConfig);
 
// uint8_t GPIO_setPinDir(void * port,  uint32_t pin, uint32_t mode);
// void GPIO_setPinDir(port, uint8_t pinNum);

// void GPIO_setPin(port, uint8_t pinNum);
// void GPIO_clearPin(port, uint8_t pinNum);
// void GPIO_togglePin(port, uint8_t pinNum);

// void GPIO_enablePinPullUP(port, uint8_t pinNum);
// void GPIO_enablePinPullDOWN(port, uint8_t pinNum);

//for also compiling with g++ 
#ifdef __cplusplus
        }
    }
}
#endif

#endif