#include "std_int.h"
#include "UART/uart.h"
#include "GPIO/GPIO.h"
#include "rcc/rcc.h"
#include "NVIC/NVIC.h"

#define _USART1 (USART_reg_t*)0x40011000U
#define _USART2 (USART_reg_t*)0x40004400U
#define _USART6 (USART_reg_t*)0x40011400U

#define USART1_PORT GPIOA
#define USART1_TX_PIN 9
#define USART1_RX_PIN 10

#define USART2_PORT GPIOA
#define USART2_TX_PIN 2
#define USART2_RX_PIN 3

#define USART6_PORT GPIOA
#define USART6_TX_PIN 11
#define USART6_RX_PIN 12

typedef struct{
    volatile uint32_t PE : 1;
    volatile uint32_t FE : 1;
    volatile uint32_t NF : 1;
    volatile uint32_t ORE : 1;
    volatile uint32_t IDLE : 1;
    volatile uint32_t RXNE : 1;
    volatile uint32_t TC : 1;
    volatile uint32_t TXE : 1;
    volatile uint32_t LBD : 1;
    volatile uint32_t CTS : 1;
}SR_bits_t;

typedef struct
{
    volatile uint32_t SBK :1 ;     // Send break
    volatile uint32_t RWU :1 ;     // Receiver wakeup
    volatile uint32_t RE :1 ;      // Receiver enable
    volatile uint32_t TE :1 ;      // Transmitter enable
    volatile uint32_t IDLEIE :1 ;  // IDLE interrupt enable
    volatile uint32_t RXNEIE :1 ;  // RXNE interrupt enable
    volatile uint32_t TCIE :1 ;    // Transmission complete interrupt enable
    volatile uint32_t TXEIE :1 ;   // TXE interrupt enable
    volatile uint32_t PEIE :1 ;    // PE interrupt enable
    volatile uint32_t PS :1 ;      // Parity selection
    volatile uint32_t PCE :1 ;     // Parity control enable
    volatile uint32_t WAKE :1 ;    // Wakeup method
    volatile uint32_t M :1 ;       // Word length
    volatile uint32_t UE :1 ;      // USART enable
    volatile uint32_t RESERVED0:1; // Reserved bits
    volatile uint32_t OVER8 :1 ;   // Oversampling mode
    volatile uint32_t RESERVED1:15;// Reserved bits
}CR1_bits_t;

typedef struct{
    union{
        volatile uint32_t SR;
        volatile SR_bits_t SR_bits;
    };
    volatile uint32_t DR;
    volatile uint32_t BRR;
    union{
        volatile uint32_t CR1;
        volatile CR1_bits_t CR1_bits;
    };
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
}USART_reg_t;

USART_reg_t* const USART[] ={
    _USART1,
    _USART2,
    _USART6
};


void (*cbf_Rx)(void);
void (*cbf_Tx)(void);

static Buffer_t sendBuffer;
static Buffer_t reciveBuffer;

static void UART_Configure_BaudRate(USART_id_t USART_id, uint32_t BaudRate);


void USART_init(USART_id_t USART_id, USART_cfg_t* cfg)
{ 
    GPIO_pinCfg_t GPIO_USARTPin[2];     //TX -> 0,  RX -> 1
    Rcc_enablePeripheralClk(Rcc_GPIOA);
    switch (USART_id)
    {
        case USART1:
            Rcc_enablePeripheralClk(Rcc_USART1);
            NVIC_EnableIRQ(IRQ_USART1);

            GPIO_identfyPin(&GPIO_USARTPin[0],USART1_PORT,USART1_TX_PIN); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_selectAlternateFunc(&GPIO_USARTPin[0], USART1_PA9_10_PB6_7); 
            
            GPIO_identfyPin(&GPIO_USARTPin[1],USART1_PORT,USART1_RX_PIN); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_selectAlternateFunc(&GPIO_USARTPin[1], USART1_PA9_10_PB6_7); 
            break;
        case USART2:
            Rcc_enablePeripheralClk(Rcc_USART2);
            NVIC_EnableIRQ(IRQ_USART2);
            
            GPIO_identfyPin(&GPIO_USARTPin[0],USART2_PORT,USART2_TX_PIN); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_selectAlternateFunc(&GPIO_USARTPin[0], USART2_PA2_3); 
            
            GPIO_identfyPin(&GPIO_USARTPin[1],USART2_PORT,USART2_RX_PIN); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_selectAlternateFunc(&GPIO_USARTPin[1], USART2_PA2_3); 
            break;
        case USART6:
            Rcc_enablePeripheralClk(Rcc_USART6);
            NVIC_EnableIRQ(IRQ_USART6);
            
            GPIO_identfyPin(&GPIO_USARTPin[0],USART6_PORT,USART6_TX_PIN); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_selectAlternateFunc(&GPIO_USARTPin[0], USART6_PA11_12); 
            
            GPIO_identfyPin(&GPIO_USARTPin[1],USART6_PORT,USART6_RX_PIN); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_selectAlternateFunc(&GPIO_USARTPin[1], USART6_PA11_12); 
            break;
        default:
            break;
    }
    GPIO_setPinDirMode(&GPIO_USARTPin[0],ALTERNATE_FUNCTION);  //input, output, alternate, analog
    GPIO_setOutPinMode(&GPIO_USARTPin[0],PUSH_PULL,PULL_UP);   //push-pull/open-drain , pull-up/pull-down
    GPIO_creatPin(&GPIO_USARTPin[0]);
    
    GPIO_setPinDirMode(&GPIO_USARTPin[1],ALTERNATE_FUNCTION);  //input, output, alternate, analog
    GPIO_setOutPinMode(&GPIO_USARTPin[1],PUSH_PULL,PULL_UP);   //push-pull/open-drain , pull-up/pull-down
    GPIO_creatPin(&GPIO_USARTPin[1]);

    
    USART[USART_id]->CR1 = 0x0000200C;  //0b10 0000 0000 1100   UE, TE, RE enabled
    // USART[USART_id]->BRR = 0x8B; //115200 @16MHz
    // // USART[USART_id]->BRR = 0x341; //9600 @16MHz
    UART_Configure_BaudRate(USART_id,115200);

    // update user call back functions to the global call back functions
    cbf_Tx = cfg->cbf_Tx;
    cbf_Rx = cfg->cbf_Rx;
}

static void UART_Configure_BaudRate(USART_id_t USART_id, uint32_t BaudRate)
{
    uint32_t pclk;          /* Peripheral clock frequency */
    uint32_t usartdiv;      /* USARTDIV value (scaled by 100) */
    uint32_t mantissa;      /* Mantissa part of BRR */
    uint32_t fraction;      /* Fraction part of BRR */
    uint32_t brr_value;     /* Final BRR register value */
    
    /* Determine peripheral clock based on UART */
            pclk = 16000000;    /* 16 MHz APB2 clock */

    
    /* Calculate USARTDIV (multiply by 100 to preserve decimal precision) */
    /* USARTDIV = (pclk × 100) / (16 × BaudRate) */
    usartdiv = (pclk * 100) / (16 * BaudRate);
    
    /* Extract mantissa (integer part) */
    mantissa = usartdiv / 100;
    
    /* Calculate fraction (decimal part × 16) */
    /* fraction = (usartdiv % 100) × 16 / 100 */
    fraction = ((usartdiv % 100) * 16 + 50) / 100;  /* +50 for rounding */
    
    /* Handle fraction overflow (if fraction >= 16) */
    if (fraction >= 16)
    {
        mantissa++;
        fraction = 0;
    }
    
    /* Construct BRR value: Mantissa[15:4] | Fraction[3:0] */
    mantissa = 8;
    fraction = 11;
    brr_value = (mantissa << 4) | (fraction & 0x0F);
    
    /* Write to BRR register */
    USART[USART_id]->BRR = brr_value;
}


// Interrupt Service Routine for USART1
void USART1_IRQHandler()
{
    // Check if TXE interrupt is enabled and TXE flag is set
    if (USART[USART1]->CR1_bits.TXEIE && USART[USART1]->SR_bits.TXE)
    {
        static uint32_t txIndex = 1;
        if (txIndex <= sendBuffer.len)
        {
            USART[USART1]->DR = sendBuffer.buf[txIndex];
            txIndex++;        
        }
        else
        {
            // All data sent, disable TXE interrupt
            USART[USART1]->CR1_bits.TXEIE = 0;
            txIndex = 0; // Reset index for next transmission
            cbf_Tx();
        }
    }

    // Check if RXNE interrupt is enabled and RXNE flag is set
    if (USART[USART1]->CR1_bits.RXNEIE && USART[USART1]->SR_bits.RXNE)
    {
        static uint32_t rxIndex = 0;
        if (rxIndex <= reciveBuffer.len)
        {
            reciveBuffer.buf[rxIndex] = (uint8_t)(USART[USART1]->DR & 0xFF);
            rxIndex++;
        }
        else
        {
            // All data received, disable RXNE interrupt
            USART[USART1]->CR1_bits.RXNEIE = 0;
            rxIndex = 0; // Reset index for next reception
            cbf_Rx();
        }
    }
}
// Interrupt Service Routine for USART2
void USART2_IRQHandler()
{
    // Check if TXE interrupt is enabled and TXE flag is set
    if (USART[USART2]->CR1_bits.TXEIE == 1 && USART[USART2]->SR_bits.TXE == 1)
    {
        static uint32_t txIndex = 1;    // starting from second byte
        if (txIndex <= sendBuffer.len)
        {
            USART[USART2]->DR = sendBuffer.buf[txIndex];
            txIndex++;
        }
        else
        {
            // sending is finished
            USART[USART2]->CR1_bits.TXEIE = 0; //disable TXE interrupt
            txIndex=0;
            cbf_Tx();
        }
    }
    // Check if RXNE interrupt is enabled and RXNE flag is set
    if (USART[USART2]->CR1_bits.RXNEIE == 1 && USART[USART2]->SR_bits.RXNE == 1)
    {
        static uint32_t rxIndex = 0;
        if (rxIndex <= reciveBuffer.len)
        {
            reciveBuffer.buf[rxIndex] = (uint8_t)(USART[USART2]->DR & 0xFF);
            rxIndex++;
        }
        else
        {
            // All data received, disable RXNE interrupt
            USART[USART2]->CR1_bits.RXNEIE = 0;
            rxIndex = 0; // Reset index for next reception
            cbf_Rx();
        }
    }
}
// Interrupt Service Routine for USART6
void USART6_IRQHandler()
{
    // Check if TXE interrupt is enabled and TXE flag is set
    if (USART[USART6]->CR1_bits.TXEIE == 1 && USART[USART6]->SR_bits.TXE == 1)
    {
        static uint32_t txIndex = 1;    // starting from second byte
        if (txIndex <= sendBuffer.len)
        {
            USART[USART6]->DR = sendBuffer.buf[txIndex];
            txIndex++;
        }
        else
        {
            // sending is finished
            USART[USART6]->CR1_bits.TXEIE = 0; //disable TXE interrupt
            txIndex=0;
            cbf_Tx();
        }
    }
    // Check if RXNE interrupt is enabled and RXNE flag is set
    if (USART[USART6]->CR1_bits.RXNEIE == 1 && USART[USART6]->SR_bits.RXNE == 1)
    {
        static uint32_t rxIndex = 0;
        if (rxIndex <= reciveBuffer.len)
        {
            reciveBuffer.buf[rxIndex] = (uint8_t)(USART[USART6]->DR & 0xFF);
            rxIndex++;
        }
        else
        {
            // All data received, disable RXNE interrupt
            USART[USART6]->CR1_bits.RXNEIE = 0;
            rxIndex = 0; // Reset index for next reception
            cbf_Rx();
        }
    }
}

void USART_sendBuffer(USART_id_t USART_id, Buffer_t buffer)
{
    if (buffer.buf != NULLPTR)
    {
        sendBuffer = buffer;
        USART[USART_id]->CR1_bits.TXEIE = 1; //enable TXE interrupt
        USART[USART_id]->DR = sendBuffer.buf[0]; //start sending the first byte
    }
    // //wait until TXE is set
    // while (USART[USART_id]->SR_bits.TXE == 0);
    // USART[USART_id]->DR = 0;
}

void USART_reciveBuffer(USART_id_t USART_id, Buffer_t buffer)
{
    if (buffer.buf != NULLPTR)
    {
        reciveBuffer = buffer;
        USART[USART_id]->CR1_bits.RXNEIE = 1; //enable RXNE interrupt
    }
}


void USART_sendByte(USART_id_t USART_id, uint8_t data)
{
    //wait until TXE is set
    while (USART[USART_id]->SR_bits.TXE == 0);
        USART[USART_id]->DR = data;
}





void USART_setCbf_Rx(void (*cbf)(void))
{
    cbf_Rx = cbf;
}

void USART_setCbf_Tx(void (*cbf)(void))
{
    cbf_Tx = cbf;
}

void USART_setParity(USART_id_t USART_id, uint32_t parity)
{
    switch (parity)
    {
        case 0: // no parity
            USART[USART_id]->CR1_bits.PCE = 0;
            break;
        case 1: // even parity
            USART[USART_id]->CR1_bits.PCE = 1;
            USART[USART_id]->CR1_bits.PS = 0;
            break;
        case 2: // odd parity
            USART[USART_id]->CR1_bits.PCE = 1;
            USART[USART_id]->CR1_bits.PS = 1;
            break;
        default:
            // handle invalid parity value
            break;
    }
}