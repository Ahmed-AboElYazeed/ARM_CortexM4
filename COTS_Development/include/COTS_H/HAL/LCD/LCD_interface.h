#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H


typedef enum{
    LCD_0,
    LCD_NUMBER //lcd number
}LCD_names_t;

// // for custom characters method 2 'bad'
// typedef struct {
//     unsigned b0 : 1;
//     unsigned b1 : 1;
//     unsigned b2 : 1;
//     unsigned b3 : 1;
//     unsigned b4 : 1;
// } LCD_RowBits_t;

// // Union to allow direct casting
// typedef union {
//     LCD_RowBits_t bits;
//     uint8_t byte;  // lower 5 bits store b0..b4
// } LCD_RowUnion_t;

#endif