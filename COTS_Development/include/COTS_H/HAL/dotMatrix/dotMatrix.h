#ifndef DOTMATRIX_H
#define DOTMATRIX_H

#include "std_int.h"
#include "dotMatrix/dotMatrix_interface.h"

typedef enum{
    DOTMAT_PORTA,
    DOTMAT_PORTB,
    DOTMAT_PORTC,
    DOTMAT_PORTD,
    DOTMAT_PORTE,
    DOTMAT_PORTH
}DotMat_port_enu_t;

typedef struct{
    uint32_t RowPin[ROW_MAXNUM];
    DotMat_port_enu_t RowPort[ROW_MAXNUM];
    uint32_t ColPin[COL_MAXNUM];
    DotMat_port_enu_t ColPort[COL_MAXNUM];    
}DotMat_interfacePins_t;

// instead of implementing the Demux equation
typedef enum{
    ROW_0 =        0b1,
    ROW_1 =       0b10,
    ROW_2 =      0b100,
    ROW_3 =     0b1000,
    ROW_4 =    0b10000,
    ROW_5 =   0b100000,
    ROW_6 =  0b1000000,
    ROW_7 = 0b10000000,
}DotMat_rows_enu_t;

// the column will be inverted using (~)
typedef enum{
    COL_0 =        0b1,
    COL_1 =       0b10,
    COL_2 =      0b100,
    COL_3 =     0b1000,
    COL_4 =    0b10000,
    COL_5 =   0b100000,
    COL_6 =  0b1000000,
    COL_7 = 0b10000000,
}DotMat_cols_enu_t;

void DotMat_init (DotMat_name_enu_t DotMat_name);
void DotMat_writeRow (DotMat_name_enu_t DotMat_indx, uint32_t data, DotMat_rows_enu_t rowNum);
// void DotMat_writeCol (DotMat_name_enu_t DotMat_name, DotMat_cols_enu_t colNum, uint32_t data);


#endif