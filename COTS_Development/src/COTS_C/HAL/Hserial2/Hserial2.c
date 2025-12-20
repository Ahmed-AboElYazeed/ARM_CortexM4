#include "Hserial/Hserial.h"
#include "std_int.h"
#include "rcc/rcc.h"
#include "NVIC/NVIC.h"
#include "GPIO/GPIO.h"
#include "UART2/uart2.h"
#include "DMA/DMA.h"

Buffer_t* user_TxBuf = NULLPTR;
Buffer_t* user_RxBuf = NULLPTR;

/*********************************************/
// call back functions (notification)
void Hserial_sendEndNotify(void)
{
}
void Hserial_recieveEndNotify(void)
{
    uint8_t str[13] = "stm recieve: ";
    Buffer_t tempBuf = {
        .buf = str,
        .len = 13,
        .transmettedLen =0,
    };
    for(uint32_t i=0; i<10000; i++)
    {
        asm("NOP");
    } 
    Hserial_sendBuffer(&tempBuf);
    for(uint32_t i=0; i<10000; i++)
    {
        asm("NOP");
    } 
    Hserial_sendBuffer(user_RxBuf);
}
/*********************************************/

void Hserial_init()
{
    USART_cfg_t USART_cfg ={
        .baudrate =115200,
        .parity = 0,
        .cbf_Rx = Hserial_recieveEndNotify,
        .cbf_Tx = Hserial_sendEndNotify,
        .enable_DMA_mode = 1,
    };
    USART_init(USART1, &USART_cfg);    
    DMA_init(USART1_TX_STRM7);
    DMA_init(USART1_RX_STRM5);
}

void Hserial_sendBuffer(Buffer_t* TxBuf)
{
    user_TxBuf = TxBuf;
    //check if not first time
    DMA_STREAM_cfg_t TxStreamCfg ={
        .memAddress = (uint32_t)(TxBuf->buf),   //src
        .perphAddress = USART_addressGetter(USART1),  //dest
        .NofDataItems = TxBuf->len,
        .MBURST = SINGLE_TRANSFER,
        .PBURST = SINGLE_TRANSFER,
        .priority = PL_LOW,
        .MSIZE = BYTE_8bit,
        .PSIZE = BYTE_8bit,
        .MINC = INCREMENTING_POINTER,
        .PINC = FIXED_POINTER,
        .DIR = MEMORY_TO_PERIPH,
        .flow_control = FC_DMA,
        .half_transfer = DISABLE_HTF,
    };
    DMA_configureStream(USART1_TX_STRM7, &TxStreamCfg);
    USART1_enable_DMAtransmitter();
    DMA_start(USART1_TX_STRM7);
}

void Hserial_recieveBuffer(Buffer_t* RxBuf)
{
    user_RxBuf = RxBuf;
    DMA_STREAM_cfg_t RxStreamCfg ={
        .memAddress = (uint32_t)(RxBuf->buf), //dest
        .perphAddress = USART_addressGetter(USART1),  //src
        .NofDataItems = RxBuf->len,
        .MBURST = SINGLE_TRANSFER,
        .PBURST = SINGLE_TRANSFER,
        .priority = PL_LOW,
        .MSIZE = BYTE_8bit,
        .PSIZE = BYTE_8bit,
        .MINC = INCREMENTING_POINTER,
        .PINC = FIXED_POINTER,
        .DIR = PERIPH_TO_MEMORY,
        .flow_control = FC_DMA,    // FC_PERIPH,
        .half_transfer = DISABLE_HTF,
    };
    DMA_configureStream(USART1_RX_STRM5, &RxStreamCfg);
    NVIC_EnableIRQ(IRQ_DMA2_Stream5);
    USART1_enable_DMAreciever();
    DMA_start(USART1_RX_STRM5);
}

// the USART1_RX_STRM5 IRQHandler 
void DMA2_Stream5_IRQHandler()
{
    // if (DMA_getTransferStatus(USART1_RX_STRM5) == 1u)    //is the interrupt is caussed by this event?
    {
        USART1_disable_DMAreciever();
        NVIC_DisableIRQ(IRQ_DMA2_Stream5);
        Hserial_recieveEndNotify(); //NOTIFY the user.
    }
}