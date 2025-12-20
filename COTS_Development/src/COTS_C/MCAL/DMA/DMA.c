#include "DMA/DMA.h"
#include "rcc/rcc.h"
#include "NVIC/NVIC.h"
/*
    This DMA Driver will:
        give all the generic calls specialy PERIPHERAL TO MEMORY 
            & MEMORY TO PERIPHERAL copying to the DMA1 Only.
        Where, the DMA2 will get the direct MEMORY TO MEMORY 
            copying throught the "DMA_memCopy" function only. 
*/

#define DMA1_BASEADDRESS ((volatile DMA_reg_t*)0x40026000U)
#define DMA2_BASEADDRESS ((volatile DMA_reg_t*)0x40026400U)

typedef struct{
    volatile uint32_t CR;   /*!< DMA stream x configuration register      */
    volatile uint32_t NDTR; /*!< DMA stream x number of data register     */
    volatile uint32_t PAR;  /*!< DMA stream x peripheral address register */
    volatile uint32_t M0AR; /*!< DMA stream x memory 0 address register   */
    volatile uint32_t M1AR; /*!< DMA stream x memory 1 address register   */
    volatile uint32_t FCR;  /*!< DMA stream x FIFO control register       */
}DMA_stream_reg_t;

typedef struct{
    volatile uint32_t LISR;     /*!< DMA low interrupt status register,      Address offset: 0x00 */
    volatile uint32_t HISR;     /*!< DMA high interrupt status register,     Address offset: 0x04 */
    volatile uint32_t LIFCR;    /*!< DMA low interrupt flag clear register,  Address offset: 0x08 */
    volatile uint32_t HIFCR;    /*!< DMA high interrupt flag clear register, Address offset: 0x0C */
    volatile DMA_stream_reg_t stream[8];
}DMA_reg_t;

volatile DMA_reg_t* DMA[2] ={
    DMA1_BASEADDRESS,
    DMA2_BASEADDRESS
};

/****************************************************************
 * 
 * DMA interrupt status register
 *  
 ****************************************************************/
#define STREAM_FLAG_BITS_SHIFT 6U

#define TCIFx_BIT_LOCATION 5
// YOU MUST HANDEL if it is in the LOW or the HIGH register
#define CLEAR_TC_INTERRUPT_FLAG(reg,s) (reg &= ((1U<<((s%4U)*8))<<TCIFx_BIT_LOCATION))
#define READ_TC_INTERRUPT_FLAG(reg,s)  (((reg>>((s%4U)*8))>>TCIFx_BIT_LOCATION)&1UL)
//////////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ WRONG METHOD ^^^^^^^^^^^^^^^^^^^//////////////

// DMA Interrupt Flag Bit Positions for each stream
typedef enum {
    DMA_FLAG_FEIF  = 0,  // FIFO Error Interrupt Flag
    DMA_FLAG_DMEIF = 2,  // Direct Mode Error Interrupt Flag
    DMA_FLAG_TEIF  = 3,  // Transfer Error Interrupt Flag
    DMA_FLAG_HTIF  = 4,  // Half Transfer Interrupt Flag
    DMA_FLAG_TCIF  = 5   // Transfer Complete Interrupt Flag
} DMA_FlagType_t;
static uint8_t DMA_GetFlag(EVENT_enu_t event, DMA_FlagType_t flagType);
static void DMA_ClearFlag(EVENT_enu_t event, DMA_FlagType_t flagType);

/****************************************************************
 * 
 * DMA stream x configuration register (DMA_SxCR) (x = 0..7)
 * 
 ****************************************************************/
#define EN_bitLOCATION          (0U)
#define DMEIE_bitLOCATION       (1U)
#define TEIE_bitLOCATION        (2U)
#define HTIE_bitLOCATION        (3U)
#define TCIE_bitLOCATION        (4U)
#define PFCTRL_bitLOCATION      (5U)
#define DIR_2B_bitLOCATION      (6U)
#define CIRC_bitLOCATION        (8U)
#define PINC_bitLOCATION        (9U)
#define MINC_bitLOCATION        (10U)
#define PSIZE_2B_bitLOCATION    (11U)
#define MSIZE_2B_bitLOCATION    (13U)
#define PINCOS_bitLOCATION      (15U)
#define PL_2B_bitLOCATION       (16U)
#define DBM_bitLOCATION         (18U)
#define CT_bitLOCATION          (19U)
#define PBURST_2B_bitLOCATION   (21U)
#define MBURST_2B_bitLOCATION   (23U)
#define CHSEL_3B_bitLOCATION    (25U)

#define ENABLE_STREAM (1U<<EN_bitLOCATION)
#define DISABLE_STREAM (0U<<EN_bitLOCATION)

#define CHANAL_SELECT(ch) ((ch&0b111U)<<CHSEL_3B_bitLOCATION)

#define MEMORY_BURST_CFG(b) ((b&0b11U)<<MBURST_2B_bitLOCATION)
#define PERIPH_BURST_CFG(b) ((b&0b11U)<<PBURST_2B_bitLOCATION)

#define PRIORITY_LEVEL(p)   ((p&0b11U)<<PL_2B_bitLOCATION)

#define MEMORY_DATA_SIZE(m)   ((m&0b11U)<<MSIZE_2B_bitLOCATION)
#define PERIPH_DATA_SIZE(m)   ((m&0b11U)<<PSIZE_2B_bitLOCATION)

#define MEMORY_INCREMENT_MODE(i) (i<<MINC_bitLOCATION)
#define PERIPH_INCREMENT_MODE(i) (i<<PINC_bitLOCATION)

#define DATA_TRANSFER_DIR(d) ((d&0b11U)<<DIR_2B_bitLOCATION)

#define PERIPH_FLOW_CONTROL(f) (f<<PFCTRL_bitLOCATION)

#define ENABLE_TRANSGER_COMPLETE_INTERRUPT (1U<<TCIE_bitLOCATION)
#define ENABLE_HALF_TRANSGER_COMPLETE_INTERRUPT(h) (h<<HTIE_bitLOCATION)


static void DMA_calling_NVIC_RCC (uint8_t DMANumber, uint8_t streamNumber)
{
    switch (DMANumber)
    {
    case DMA1_NUM:
        Rcc_enablePeripheralClk(Rcc_DMA1);
        /*
        // instead of switching on all the stream numbers 0 to 7
        //as all the IRQs are ordered except Stream7:
        if (streamNumber == 7)
        {
            NVIC_EnableIRQ(IRQ_DMA1_Stream7);  //as all the IRQs are ordered except Stream7
        }
        else if (streamNumber < 7)
        {
            NVIC_EnableIRQ(IRQ_DMA1_Stream0+streamNumber);  //add the stream number to shift to the correct IRQ
        }*/
        break;
    case DMA2_NUM:
        Rcc_enablePeripheralClk(Rcc_DMA2);
        /*
        // instead of switching on all the stream numbers 0 to 7
        //as all the IRQs are ordered except Stream7:
        if (streamNumber == 7)
        {
            NVIC_EnableIRQ(IRQ_DMA1_Stream7);  //as all the IRQs are ordered except Stream7
        }
        else if (streamNumber < 7)
        {
            NVIC_EnableIRQ(IRQ_DMA1_Stream0+streamNumber);  //add the stream number to shift to the correct IRQ
        }*/
        break;
    default:
        break;
    }
}

void DMA_init(EVENT_enu_t event)
{
    //because:::: EVENT_enu_t event = (DMA_NUM<<6U)&(STREAM_NUM<<3U)&(CHANAL_NUM<<0U)
    uint8_t DMANumber =     ((event >> 6U)& 0b111u);
    uint8_t streamNumber =  ((event >> 3U)& 0b111u);
    DMA_calling_NVIC_RCC(DMANumber,streamNumber);
}

void DMA_configureStream(EVENT_enu_t event, DMA_STREAM_cfg_t* stream_cfg)
{
    //because:::: STREAM_enu_t stream = (DMA_NUM<<6U)&(STREAM_NUM<<3U)&(CHANAL_NUM<<0U)
    uint8_t DMANumber =     ((event >> 6U)& 0b111u);
    uint8_t streamNumber =  ((event >> 3U)& 0b111u);
    uint8_t chanalNumber =  ((event)      & 0b111u);

    // Before setting an Enable control bit to ‘1’, the corresponding event flag should be cleared, otherwise an interrupt is immediately generated.
    DMA_clearTCflag(event);    // Clearing the event flag
    
    /*
    YOU MUST clear the register before appling the next MASKING method (AS it can't actully clear any set bit)
    and clear EN bit to enable writing on other DMA config bits :::: "write only if EN is ‘0’"
    */
    DMA[DMANumber]->stream[streamNumber].CR = 0;  // clearing the register.
    DMA[DMANumber]->stream[streamNumber].NDTR = stream_cfg->NofDataItems;
    DMA[DMANumber]->stream[streamNumber].M0AR = stream_cfg->memAddress;
    DMA[DMANumber]->stream[streamNumber].PAR = stream_cfg->perphAddress;
    DMA[DMANumber]->stream[streamNumber].CR = CHANAL_SELECT(chanalNumber) |
                                              PERIPH_BURST_CFG(stream_cfg->PBURST) |
                                              MEMORY_BURST_CFG(stream_cfg->MBURST) |
                                              PRIORITY_LEVEL(stream_cfg->priority) |
                                              MEMORY_DATA_SIZE(stream_cfg->MSIZE) |
                                              PERIPH_DATA_SIZE(stream_cfg->PSIZE) |
                                              PERIPH_INCREMENT_MODE(stream_cfg->PINC) |
                                              MEMORY_INCREMENT_MODE(stream_cfg->MINC) |
                                              DATA_TRANSFER_DIR(stream_cfg->DIR) |
                                              PERIPH_FLOW_CONTROL(stream_cfg->flow_control) |
                                              ENABLE_TRANSGER_COMPLETE_INTERRUPT |
                                              ENABLE_HALF_TRANSGER_COMPLETE_INTERRUPT(stream_cfg->half_transfer);
}

void DMA_start(EVENT_enu_t event)
{
    uint8_t DMANumber =     ((event >> 6U)& 0b111u);
    uint8_t streamNumber =  ((event >> 3U)& 0b111u);
    DMA[DMANumber]->stream[streamNumber].CR |= ENABLE_STREAM;
}

uint32_t DMA_getNumOfTransferedData(EVENT_enu_t event)
{
    uint8_t DMANumber =     ((event >> 6U)& 0b111u);
    uint8_t streamNumber =  ((event >> 3U)& 0b111u);
    return DMA[DMANumber]->stream[streamNumber].NDTR;
}

uint8_t DMA_getTransferStatus(EVENT_enu_t event)
{
    return DMA_GetFlag(event,DMA_FLAG_TCIF);
}
void DMA_clearTCflag(EVENT_enu_t event)
{
    return DMA_ClearFlag(event,DMA_FLAG_TCIF);
}

void DMA_memCopy(uint32_t dest, uint32_t src, uint64_t length)
{
    // Only the DMA2 controller is able to perform memory-to-memory transfers.
    DMA_STREAM_cfg_t memCopyCfg ={
        .memAddress = dest,
        .perphAddress = src,
        .NofDataItems = length,
        .MBURST = SINGLE_TRANSFER,
        .PBURST = SINGLE_TRANSFER,
        .priority = PL_LOW,
        .MSIZE = BYTE_8bit,
        .PSIZE = BYTE_8bit,
        .MINC = INCREMENTING_POINTER,
        .PINC = INCREMENTING_POINTER,
        .DIR = MEMORY_TO_MEMORY,
        .flow_control = FC_DMA,
        .half_transfer = DISABLE_HTF,
    };
    DMA_init(MEM_TO_MEM_STRM1_CH1);

    DMA_configureStream(MEM_TO_MEM_STRM1_CH1, &memCopyCfg);
    
    DMA_start(MEM_TO_MEM_STRM1_CH1);
}


/****************************************************************
 * 
 *          DMA interrupt status register
 *  
 ****************************************************************/

// Calculate bit position for a given stream and flag type
#define DMA_FLAG_BIT_POS(stream, flag) \
    ((stream & 0x03) == 0 ? (flag) : \
     (stream & 0x03) == 1 ? ((flag) + 6) : \
     (stream & 0x03) == 2 ? ((flag) + 16) : \
                             ((flag) + 22))

/**
 * @brief Get DMA interrupt flag status
 * @param DMANumber: 0 for DMA1, 1 for DMA2
 * @param streamNumber: Stream number (0-7)
 * @param flagType: Type of flag to check (DMA_FLAG_FEIF, DMA_FLAG_TCIF, etc.)
 * @return uint8_t: 1 if flag is set, 0 if clear
 */
static uint8_t DMA_GetFlag(EVENT_enu_t event, DMA_FlagType_t flagType)
{
    uint8_t DMANumber =     ((event >> 6U)& 0b111u);
    uint8_t streamNumber =  ((event >> 3U)& 0b111u);
    uint32_t bitPosition;
    uint32_t statusRegister;
        if (streamNumber < 4)
    {
        statusRegister = DMA[DMANumber]->LISR;// Use LISR for streams 0-3
    }
    else
    {
        statusRegister = DMA[DMANumber]->HISR;  // Use HISR for streams 4-7
        streamNumber -= 4; // Adjust to 0-3 range for bit calculation
    }
    bitPosition = DMA_FLAG_BIT_POS(streamNumber, flagType);
    return (statusRegister >> bitPosition) & 0x01;
}

/**
 * @brief Clear DMA interrupt flag
 * @param DMANumber: 0 for DMA1, 1 for DMA2
 * @param streamNumber: Stream number (0-7)
 * @param flagType: Type of flag to clear
 */
static void DMA_ClearFlag(EVENT_enu_t event, DMA_FlagType_t flagType)
{
    uint8_t DMANumber =     ((event >> 6U)& 0b111u);
    uint8_t streamNumber =  ((event >> 3U)& 0b111u);
    uint32_t bitPosition;
    
    // Calculate bit position based on stream number and flag type
    uint8_t adjustedStream = (streamNumber < 4) ? streamNumber : (streamNumber - 4);
    bitPosition = DMA_FLAG_BIT_POS(adjustedStream, flagType);
    
    if (streamNumber < 4)
    {
        // Clear flag in LIFCR for streams 0-3
        DMA[DMANumber]->LIFCR |= (1 << bitPosition);
    }
    else
    {
        // Clear flag in HIFCR for streams 4-7
        DMA[DMANumber]->HIFCR |= (1 << bitPosition);
    }
}