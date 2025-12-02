#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "LCD/LCD_interface.h"
#include "GPIO/GPIO.h"

typedef enum{
    PORTA_LCD,
    PORTB_LCD,
    PORTC_LCD,
    PORTD_LCD,
    PORTE_LCD,
    PORTH_LCD
}PORT_enm_t;

// typedef struct{
//     uint32_t pin;
//     PORT_enm_t port;
// }GPIO_Pin_t;

typedef enum{
    D0,
    D1,
    D2,
    D3,
    D4,
    D5,
    D6,
    D7,
    RW,
    RS,
    EN,
    LCD_PINNUMBER
}LCD_pinName_enu_t;

// the definition in GPIO.h
// typedef struct {
//     uint32_t pin;   // pin number
//     GPIO_port_enu_t port;    // give the number of the element in the array of pointer to the register address "this array implemented in GPIO.C"
//     uint8_t mode;      // binary contain the GPIO config
//     GPIO_af_t alternateFunction;
// }GPIO_pinCfg_t;

typedef struct  
{
    GPIO_pinCfg_t LCD_pins[LCD_PINNUMBER];
    uint8_t mode;
}LCD_cfg_t;

#define SET_CG_RAM_ADDRESS(address) (0b0001u << 6u) | (0b111111u & address)
#define SET_DD_RAM_ADDRESS(address) (0b001u << 7u) | (0b1111111u & address)

#define WRITEDATA_CGorDD_RAM(data) (0b10u << 8u) | (0b1111111u & data)

typedef enum{
    SEND_DATA,
    SEND_COMMAND,
    INIT0_8B_FUNCTION_SET__LINEone_5X7 = (0b000011u << 4u) | (0U<<3u) | (0U<<2u),   //(0b000011u << 4u) | (N<<3u) | (F<<2u)    //N = 0 : 1 line display (1/8 duty)     //F = 0 : 5 x 7 dots
    INIT0_8B_FUNCTION_SET__LINEtwo_5X7 = (0b000011u << 4u) | (1U<<3u) | (0U<<2u),   //(0b000011u << 4u) | (N<<3u) | (F<<2u)    //N = 1 : 2 line display (1/16 duty)    //F = 0 : 5 x 7 dots
    INIT1_DISPLAY_CONTROL__DISon_CURSon_BLINKon = (0b0000001u << 3u) | (1U<<2u) | (1U<<1u) | (1U<<0u), 
    INIT2_8B_DISPLAY__CLEAR = 0b1u,
    INIT3_8B_ENTRY_MODE_SET__INC_SHoff = (0b00000001u << 2u) | (1U<<1u) | (0U<<0u),
    INIT3_8B_ENTRY_MODE_SET__INC_SHon = (0b00000001u << 2u) | (1U<<1u) | (1U<<0u),
    
    CLEAR_DISPLAY = 0b1u,
    RETURN_HOME = 0b10U,

    //6.9 Read Busy Flag & Address
}COMMAND_enm_t;



void LCD_init (LCD_cfg_t* LCD);
void LCD_writeChar (LCD_cfg_t* LCD, char character); 
void LCD_writeString (LCD_cfg_t* LCD, char* string);
void LCD_clearLCD (LCD_cfg_t* LCD);
void LCD_setCursorPosition (LCD_cfg_t* LCD);
void LCD_saveCustomCharacter (LCD_cfg_t* LCD);

// void sendCommand (LCD_cfg_t* LCD, COMMAND_enm_t command);
// void sendData (LCD_cfg_t* LCD, uint32_t data);
// void triggerEnable(LCD_cfg_t* LCD);
//    //void nibbleHandling ();

#endif