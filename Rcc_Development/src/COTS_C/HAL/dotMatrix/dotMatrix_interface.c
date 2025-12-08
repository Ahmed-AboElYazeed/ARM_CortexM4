#include "dotMatrix/dotMatrix.h"

const DotMat_interfacePins_t DotMat_interfacePins [DOTMAT_MAXNUM]
= {
    [DOTMAT_0]
    ={
        .RowPin[0] = 0,
        .RowPort[0] = DOTMAT_PORTB,
        .RowPin[1] = 1,
        .RowPort[1] = DOTMAT_PORTB,
        .RowPin[2] = 2,
        .RowPort[2] = DOTMAT_PORTB,
        .RowPin[3] = 13,
        .RowPort[3] = DOTMAT_PORTC,
        .RowPin[4] = 14,
        .RowPort[4] = DOTMAT_PORTC,
        .RowPin[5] = 5,
        .RowPort[5] = DOTMAT_PORTB,
        .RowPin[6] = 6,
        .RowPort[6] = DOTMAT_PORTB,
        .RowPin[ROW_MAXNUM-1] = 7,
        .RowPort[ROW_MAXNUM-1] = DOTMAT_PORTB,
        
        .ColPin[0] = 8,
        .ColPort[0] = DOTMAT_PORTB,
        .ColPin[1] = 9,
        .ColPort[1] = DOTMAT_PORTB,
        .ColPin[2] = 10,
        .ColPort[2] = DOTMAT_PORTB,
        .ColPin[3] = 12,
        .ColPort[3] = DOTMAT_PORTB,
        .ColPin[4] = 13,
        .ColPort[4] = DOTMAT_PORTB,
        .ColPin[5] = 14,
        .ColPort[5] = DOTMAT_PORTB,
        .ColPin[6] = 15,
        .ColPort[6] = DOTMAT_PORTB,
        .ColPin[COL_MAXNUM-1] = 15,
        .ColPort[COL_MAXNUM-1] = DOTMAT_PORTC,       
    }
};

const uint8_t pattarn [ROW_MAXNUM]
={
    0b000000001,
    0b000000011,
    0b000001111,
    0b000011111,
    0b000011111,
    0b000001111,
    0b000000011,
    0b000000001,
};