#ifndef DMA_H
#define DMA_H
#include "std_int.h"

/****************************************************************
 * 
 *      DMA streams
 * 
 ****************************************************************/
#define DMA1_NUM 0U
#define DMA2_NUM 1U

#define STREAM0_NUM 0U
#define STREAM1_NUM 1U
#define STREAM2_NUM 2U
#define STREAM3_NUM 3U
#define STREAM4_NUM 4U
#define STREAM5_NUM 5U
#define STREAM6_NUM 6U
#define STREAM7_NUM 7U

#define CHANAL0_NUM 0U
#define CHANAL1_NUM 1U
#define CHANAL2_NUM 2U
#define CHANAL3_NUM 3U
#define CHANAL4_NUM 4U
#define CHANAL5_NUM 5U
#define CHANAL6_NUM 6U
#define CHANAL7_NUM 7U

// EVENT_enu_t event = (DMA_NUM<<6U)&(STREAM_NUM<<3U)&(CHANAL_NUM<<0U)
typedef enum{
    // USART1 (DMA2, Channel 4)
    USART1_RX_STRM2 = ((DMA2_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL4_NUM<<0U)),
    USART1_RX_STRM5 = ((DMA2_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL4_NUM<<0U)),
    USART1_TX_STRM7 = ((DMA2_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL4_NUM<<0U)),
    // USART2 (DMA1, Channel 4)
    USART2_RX_STRM5 = ((DMA1_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL4_NUM<<0U)),
    USART2_TX_STRM6 = ((DMA1_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL4_NUM<<0U)),
    // USART6 (DMA2, Channel 5)
    USART6_RX_STRM1 = ((DMA2_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL5_NUM<<0U)),
    USART6_RX_STRM2 = ((DMA2_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL5_NUM<<0U)),
    USART6_TX_STRM6 = ((DMA2_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL5_NUM<<0U)),
    USART6_TX_STRM7 = ((DMA2_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL5_NUM<<0U)),  
    // SPI1 (DMA2, Channel 3)
    SPI1_RX_STRM0 = ((DMA2_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL3_NUM<<0U)),
    SPI1_RX_STRM2 = ((DMA2_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL3_NUM<<0U)),
    SPI1_TX_STRM3 = ((DMA2_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL3_NUM<<0U)),
    SPI1_TX_STRM5 = ((DMA2_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL3_NUM<<0U)),
    // SPI2 (DMA1, Channel 0)
    SPI2_RX_STRM3 = ((DMA1_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL0_NUM<<0U)),
    SPI2_TX_STRM4 = ((DMA1_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL0_NUM<<0U)),
    // SPI3 (DMA1, Channel 0)
    SPI3_RX_STRM0 = ((DMA1_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL0_NUM<<0U)),
    SPI3_RX_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL0_NUM<<0U)),
    SPI3_TX_STRM5 = ((DMA1_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL0_NUM<<0U)),
    SPI3_TX_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL0_NUM<<0U)),
    // SPI4 (DMA2, Channel 4 & 5)
    SPI4_RX_STRM0 = ((DMA2_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL4_NUM<<0U)),
    SPI4_TX_STRM1 = ((DMA2_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL4_NUM<<0U)),
    SPI4_RX_STRM3 = ((DMA2_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL5_NUM<<0U)),
    SPI4_TX_STRM4 = ((DMA2_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL5_NUM<<0U)),
    // I2C1 (DMA1, Channel 1)
    I2C1_RX_STRM0 = ((DMA1_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL1_NUM<<0U)),
    I2C1_RX_STRM5 = ((DMA1_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL1_NUM<<0U)),
    I2C1_TX_STRM6 = ((DMA1_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL1_NUM<<0U)),
    I2C1_TX_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL1_NUM<<0U)),
    // I2C2 (DMA1, Channel 7)
    I2C2_RX_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL7_NUM<<0U)),
    I2C2_RX_STRM3 = ((DMA1_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL7_NUM<<0U)),
    I2C2_TX_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL7_NUM<<0U)),
    // I2C3 (DMA1, Channel 3 & 1)
    I2C3_RX_STRM1 = ((DMA1_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL3_NUM<<0U)),
    I2C3_RX_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL3_NUM<<0U)),
    I2C3_TX_STRM4 = ((DMA1_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL3_NUM<<0U)),
    I2C3_TX_STRM5 = ((DMA2_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL6_NUM<<0U)),
    // I2S2 (DMA1, Channel 2)
    I2S2_EXT_RX_STRM3 = ((DMA1_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL2_NUM<<0U)),
    I2S2_EXT_TX_STRM4 = ((DMA1_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL2_NUM<<0U)),
    // I2S3 (DMA1, Channel 0 & 2 & 3)
    I2S3_EXT_RX_STRM0 = ((DMA1_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL3_NUM<<0U)),
    I2S3_EXT_RX_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL2_NUM<<0U)),
    I2S3_EXT_TX_STRM5 = ((DMA1_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL2_NUM<<0U)),
    // TIM1 (DMA2, Channel 0 & 6)
    TIM1_CH1_STRM1 = ((DMA2_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_CH1_STRM3 = ((DMA2_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_CH2_STRM2 = ((DMA2_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_CH2_STRM6 = ((DMA2_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL0_NUM<<0U)),
    TIM1_CH3_STRM6 = ((DMA2_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_CH4_STRM4 = ((DMA2_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_TRIG_STRM0 = ((DMA2_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_TRIG_STRM4 = ((DMA2_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_COM_STRM4 = ((DMA2_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM1_UP_STRM5 = ((DMA2_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL6_NUM<<0U)),
    // TIM2 (DMA1, Channel 3)
    TIM2_UP_STRM1 = ((DMA1_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL3_NUM<<0U)),
    TIM2_UP_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL3_NUM<<0U)),
    TIM2_CH1_STRM5 = ((DMA1_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL3_NUM<<0U)),
    TIM2_CH2_STRM6 = ((DMA1_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL3_NUM<<0U)),
    TIM2_CH3_STRM1 = ((DMA1_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL3_NUM<<0U)),
    TIM2_CH4_STRM6 = ((DMA1_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL3_NUM<<0U)),
    TIM2_CH4_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL3_NUM<<0U)),
    // TIM3 (DMA1, Channel 5)
    TIM3_CH1_STRM4 = ((DMA1_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL5_NUM<<0U)),
    TIM3_CH2_STRM5 = ((DMA1_NUM<<6U)|(STREAM5_NUM<<3U)|(CHANAL5_NUM<<0U)),
    TIM3_CH3_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL5_NUM<<0U)),
    TIM3_CH4_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL5_NUM<<0U)),
    TIM3_UP_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL5_NUM<<0U)),
    TIM3_TRIG_STRM4 = ((DMA1_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL5_NUM<<0U)),
    // TIM4 (DMA1, Channel 2)
    TIM4_CH1_STRM0 = ((DMA1_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL2_NUM<<0U)),
    TIM4_CH2_STRM3 = ((DMA1_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL2_NUM<<0U)),
    TIM4_CH3_STRM7 = ((DMA1_NUM<<6U)|(STREAM7_NUM<<3U)|(CHANAL2_NUM<<0U)),
    TIM4_UP_STRM6 = ((DMA1_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL2_NUM<<0U)),
    // TIM5 (DMA1, Channel 6)
    TIM5_CH1_STRM2 = ((DMA1_NUM<<6U)|(STREAM2_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_CH2_STRM4 = ((DMA1_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_CH3_STRM0 = ((DMA1_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_CH4_STRM1 = ((DMA1_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_CH4_STRM3 = ((DMA1_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_TRIG_STRM1 = ((DMA1_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_TRIG_STRM3 = ((DMA1_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_UP_STRM0 = ((DMA1_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL6_NUM<<0U)),
    TIM5_UP_STRM6 = ((DMA1_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL6_NUM<<0U)),
    // ADC1 (DMA2, Channel 0)
    ADC1_STRM0 = ((DMA2_NUM<<6U)|(STREAM0_NUM<<3U)|(CHANAL0_NUM<<0U)),
    ADC1_STRM4 = ((DMA2_NUM<<6U)|(STREAM4_NUM<<3U)|(CHANAL0_NUM<<0U)),
    // SDIO (DMA2, Channel 4)
    SDIO_STRM3 = ((DMA2_NUM<<6U)|(STREAM3_NUM<<3U)|(CHANAL4_NUM<<0U)),
    SDIO_STRM6 = ((DMA2_NUM<<6U)|(STREAM6_NUM<<3U)|(CHANAL4_NUM<<0U)),
    // Memory-to-memory (MUST BE DMA2 & could be any stream, as it is forced by the hardware)
    MEM_TO_MEM_STRM1_CH1 = ((DMA2_NUM<<6U)|(STREAM1_NUM<<3U)|(CHANAL1_NUM<<0U)),
} EVENT_enu_t;


/****************************************************************
 * 
 *      DMA stream configuration 
 * 
 ****************************************************************/
typedef enum{
    CH_0 = 0U,
    CH_1 = 1U,
    CH_2 = 2U,
    CH_3 = 3U,
    CH_4 = 4U,
    CH_5 = 5U,
    CH_6 = 6U,
    CH_7 = 7U,
}channal_t;

typedef enum{
    SINGLE_TRANSFER = 0b00U,
    INCR4           = 0b01U,
    INCR8           = 0b10U,
    INCR16          = 0b11U
}burst_cfg_t;

typedef enum{
    PL_LOW       = 0b00U,
    PL_MEDIUM    = 0b01U,
    PL_HIGH      = 0b10U,
    PL_VERY_HIGH = 0b11U, 
}priority_t;

typedef enum{
    BYTE_8bit       = 0b00U,
    HALF_WORD_16bit = 0b01U,
    WORD_32bit      = 0b10U,
}data_size_t;

typedef enum{
    FIXED_POINTER,
    INCREMENTING_POINTER
}increment_mode_t;

typedef enum{
    PERIPH_TO_MEMORY = 0b00U,
    MEMORY_TO_PERIPH = 0b01U,
    MEMORY_TO_MEMORY = 0b10U,
}data_transfer_direction_t;

typedef enum{
    FC_DMA,
    FC_PERIPH
}flow_control_t;

typedef enum{
    DISABLE_HTF,
    ENABLE_HTF
}half_transfer_t;

typedef struct{
    uint16_t NofDataItems;  // (0 up to 65535)item
    uint32_t memAddress;
    uint32_t perphAddress;
    // channal_t chanal;
    burst_cfg_t MBURST;
    burst_cfg_t PBURST;
    // DOUBLE_BUFFER_CONFIG should be added
    priority_t priority;
    data_size_t MSIZE;
    data_size_t PSIZE;
    increment_mode_t MINC;
    increment_mode_t PINC;
    data_transfer_direction_t DIR;
    flow_control_t flow_control;
    half_transfer_t half_transfer;
}DMA_STREAM_cfg_t;

void DMA_init(EVENT_enu_t event);
void DMA_configureStream(EVENT_enu_t event, DMA_STREAM_cfg_t* STREAM_cfg);
void DMA_start(EVENT_enu_t event);
uint32_t DMA_getNumOfTransferedData(EVENT_enu_t event);
uint8_t DMA_getTransferStatus(EVENT_enu_t event);
void DMA_clearTCflag(EVENT_enu_t event);
void DMA_memCopy(uint32_t dest, uint32_t src, uint64_t length);

#endif