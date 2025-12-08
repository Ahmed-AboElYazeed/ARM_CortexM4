#include "dotMatrix/dotMatrix.h"
#include "GPIO/GPIO.h"
#include "Sched.h"

#define DOTMAT_NUMofNEEDED_PINs ((ROW_MAXNUM+COL_MAXNUM) *DOTMAT_MAXNUM)

extern const DotMat_interfacePins_t DotMat_interfacePins [DOTMAT_MAXNUM];
extern const uint8_t pattarn [ROW_MAXNUM];
const DotMat_rows_enu_t ROW_active[] 
={
    ROW_0,
    ROW_1,
    ROW_2,
    ROW_3,
    ROW_4,
    ROW_5,
    ROW_6,
    ROW_7
};

GPIO_pinCfg_t GPIO_DotMatPin[DOTMAT_NUMofNEEDED_PINs];
/*
            |--->  Rows_0_pins[ROW_MAXNUM]      :   0 -> 7
    DotMat0 |
            |--->  Cols_0_pins[COL_MAXNUM]      :   8 -> 15      =     ROW_MAXNUM + Col_pinNum

            |--->  Rows_1_pins[ROW_MAXNUM]      :   16 -> 23
    DotMat1 |
            |--->  Cols_1_pins[COL_MAXNUM]      :   24 -> 31


            |--->  Rows_n_pins[ROW_MAXNUM]      :   DotMat_num * (ROW_MAXNUM+COL_MAXNUM) + Row_pinNum
    DotMatn |
            |--->  Cols_n_pins[COL_MAXNUM]      :  {DotMat_num * ((2*ROW_MAXNUM)+COL_MAXNUM)} + Col_pinNum
*/
#define row_pin(n,i) ((n)*(ROW_MAXNUM+COL_MAXNUM) + (i))
#define col_pin(n,i) ((DotMat_indx)*(ROW_MAXNUM+COL_MAXNUM) + ROW_MAXNUM + (i))

void DotMat_sch (void * arg);

Runnable_t DOTMAT_Runnable =
{
    .func= DotMat_sch,
    .priority = DOTMAT_RUNNABLE_PRIORITY,
    .priodicity_ticks=2,   //ms
    .first_delay=0,
    .arg = (void*)DOTMAT_0,
};

void DotMat_sch (void * arg)
{
    static uint8_t rowCounter = 0;
    DotMat_writeRow((DotMat_name_enu_t)arg, pattarn[rowCounter],ROW_active[rowCounter]);
    if (rowCounter < ROW_MAXNUM)
    {
        rowCounter++;
    }
    else
    {
        rowCounter = 0;
    }
}
void DotMat_asynch_init ()
{
    Sched_registerRunnable(&DOTMAT_Runnable);
}

void DotMats_initAll ()
{
    for(int DotMat_indx=0; DotMat_indx< DOTMAT_MAXNUM; DotMat_indx++)
    {
        for(int i=0; i< ROW_MAXNUM; i++)
        {
            GPIO_identfyPin(&GPIO_DotMatPin[row_pin(DotMat_indx,i)],DotMat_interfacePins[DotMat_indx].RowPort[i],DotMat_interfacePins[DotMat_indx].RowPin[i]); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_setPinDirMode(&GPIO_DotMatPin[row_pin(DotMat_indx,i)],OUTPUT);  //input, output, alternate, analog
            GPIO_setOutPinMode(&GPIO_DotMatPin[row_pin(DotMat_indx,i)],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
            GPIO_selectAlternateFunc(&GPIO_DotMatPin[row_pin(DotMat_indx,i)], DIO); 
            GPIO_creatPin(&GPIO_DotMatPin[row_pin(DotMat_indx,i)]);
        }
        for(int i=0; i< COL_MAXNUM; i++)
        {
            GPIO_identfyPin(&GPIO_DotMatPin[col_pin(DotMat_indx,i)],DotMat_interfacePins[DotMat_indx].ColPort[i],DotMat_interfacePins[DotMat_indx].ColPin[i]); //GPIOA/B/C/D/E , pin number 0-15
            GPIO_setPinDirMode(&GPIO_DotMatPin[col_pin(DotMat_indx,i)],OUTPUT);  //input, output, alternate, analog
            GPIO_setOutPinMode(&GPIO_DotMatPin[col_pin(DotMat_indx,i)],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
            GPIO_selectAlternateFunc(&GPIO_DotMatPin[col_pin(DotMat_indx,i)], DIO); 
            GPIO_creatPin(&GPIO_DotMatPin[col_pin(DotMat_indx,i)]);
        }
    }
}

void DotMat_init (DotMat_name_enu_t DotMat_indx)
{
    for(int i=0; i< ROW_MAXNUM; i++)
    {
        GPIO_identfyPin(&GPIO_DotMatPin[row_pin(DotMat_indx,i)],DotMat_interfacePins[DotMat_indx].RowPort[i],DotMat_interfacePins[DotMat_indx].RowPin[i]); //GPIOA/B/C/D/E , pin number 0-15
        GPIO_setPinDirMode(&GPIO_DotMatPin[row_pin(DotMat_indx,i)],OUTPUT);  //input, output, alternate, analog
        GPIO_setOutPinMode(&GPIO_DotMatPin[row_pin(DotMat_indx,i)],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&GPIO_DotMatPin[row_pin(DotMat_indx,i)], DIO); 
        GPIO_creatPin(&GPIO_DotMatPin[row_pin(DotMat_indx,i)]);
    }
    for(int i=0; i< COL_MAXNUM; i++)
    {
        GPIO_identfyPin(&GPIO_DotMatPin[col_pin(DotMat_indx,i)],DotMat_interfacePins[DotMat_indx].ColPort[i],DotMat_interfacePins[DotMat_indx].ColPin[i]); //GPIOA/B/C/D/E , pin number 0-15
        GPIO_setPinDirMode(&GPIO_DotMatPin[col_pin(DotMat_indx,i)],OUTPUT);  //input, output, alternate, analog
        GPIO_setOutPinMode(&GPIO_DotMatPin[col_pin(DotMat_indx,i)],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&GPIO_DotMatPin[col_pin(DotMat_indx,i)], DIO); 
        GPIO_creatPin(&GPIO_DotMatPin[col_pin(DotMat_indx,i)]);
    }
}

void DotMat_writeRow (DotMat_name_enu_t DotMat_indx, uint32_t data, DotMat_rows_enu_t rowNum)
{
    for(int i=0; i< COL_MAXNUM; i++)
    {
        GPIO_setPinVal(&GPIO_DotMatPin[col_pin(DotMat_indx,i)], ~(data>>i)&(0b1u) );
    }
    for(int i=0; i< ROW_MAXNUM; i++)
    {
        GPIO_setPinVal(&GPIO_DotMatPin[row_pin(DotMat_indx,i)], (rowNum>>i)&(0b1u) );
    }
}

// void DotMat_writePattarn (DotMat_name_enu_t DotMat_indx, uint32_t data)
// {
//     for(int i=0; i< COL_MAXNUM; i++)
//     {
//         GPIO_setPinVal(&GPIO_DotMatPin[row(i)], (data>>i)&(0b1u) );
//     }
// }