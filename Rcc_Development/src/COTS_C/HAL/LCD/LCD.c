#include "LCD/LCD.h"
#include "GPIO/GPIO.h"
#include "SYSTICK/SYSTICK.h"

#define WRITE_DELAY 1
#define CLEAR_DELAY 2
#define ENABL_DELAY 2
#define INIT_DELAY  35

extern uint8_t LCD_CustomChars[8][8];

/************* helper functions ******************/
static void triggerEnable(LCD_cfg_t* LCD);
static void sendCommand (LCD_cfg_t* LCD, COMMAND_enm_t command);
static void sendData (LCD_cfg_t* LCD, uint32_t data);

/********************************init funxtion ******************************/

void LCD_init (LCD_cfg_t* LCD)
{
    for (int i=0; i<LCD_PINNUMBER; i++) //INITIALIZING pins form D0 to EN
    {
        GPIO_identfyPin(&LCD->LCD_pins[i],LCD->LCD_pins[i].port,LCD->LCD_pins[i].pin); //GPIOA/B/C/D/E , pin number 0-15
        GPIO_setPinDirMode(&LCD->LCD_pins[i],OUTPUT);  //input, output, alternate, analog
        GPIO_setOutPinMode(&LCD->LCD_pins[i],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&LCD->LCD_pins[i], DIO);
        GPIO_creatPin(&LCD->LCD_pins[i]);
    }
    SYSTICK_WaitBlocking_ms(INIT_DELAY); //30ms

    sendCommand(LCD,INIT0_8B_FUNCTION_SET__LINEtwo_5X7);
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    
    sendCommand(LCD,INIT1_DISPLAY_CONTROL__DISon_CURSon_BLINKon);
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    
    sendCommand(LCD,INIT2_8B_DISPLAY__CLEAR);
    SYSTICK_WaitBlocking_ms(CLEAR_DELAY);    //1.53ms

    sendCommand(LCD,INIT3_8B_ENTRY_MODE_SET__INC_SHoff);
    SYSTICK_WaitBlocking_ms(CLEAR_DELAY);    //1.53ms

    LCD->cursorPosition = 0;
}


void LCD_writeChar (LCD_cfg_t* LCD, char character)
{
    sendCommand(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    sendData(LCD, WRITEDATA_CGorDD_RAM(character));
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //43 microSec
    (LCD->cursorPosition)++;
    // wrap to next line automatically
    if (LCD->cursorPosition == 0x10)      LCD->cursorPosition = 0x40; // move to line 2 start
    else if (LCD->cursorPosition == 0x50) LCD->cursorPosition = 0x00; // wrap to line 1
}

void LCD_writeString (LCD_cfg_t* LCD, char* string)
{
    sendCommand(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    int i=0;
    while (string[i]!='\0')
    {
        sendData(LCD, WRITEDATA_CGorDD_RAM(string[i]));
        SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //43 microSec
        (LCD->cursorPosition)++;
        i++;
        // wrap to next line automatically
        if (LCD->cursorPosition == 0x10)      
        {
            LCD->cursorPosition = 0x40; // move to line 2 start
            sendCommand(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));
            SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec   
        }
        else if (LCD->cursorPosition == 0x50) 
        {
            LCD->cursorPosition = 0x00; // wrap to line 1
            sendCommand(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));
            SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec   
        }
    }
}

void LCD_clearLCD (LCD_cfg_t* LCD)
{
    sendCommand(LCD,CLEAR_DISPLAY);
    SYSTICK_WaitBlocking_ms(CLEAR_DELAY);    //1.53ms
    LCD->cursorPosition = 0;
}

void LCD_setCursorPosition (LCD_cfg_t* LCD, uint32_t position)
{
    sendCommand(LCD, SET_DD_RAM_ADDRESS(position));
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    LCD->cursorPosition = position;
}

// not importent   the array can be filled from the LCD_interface.c file
void LCD_writeCharPattern(uint8_t charIndex, uint8_t *pattern)
{
    if (charIndex > 7 || pattern == NULL)
        return; // invalid argument

    for (uint8_t r = 0; r < 8; r++)
    {
        LCD_CustomChars[charIndex][r] = pattern[r];
    }
}

void LCD_saveCustomCharacter (LCD_cfg_t* LCD, const uint8_t charIndex)
{
    if (charIndex > 7) return;
    
    uint8_t cgramAddr = charIndex * 8;
    
    // Set CGRAM address
    sendCommand(LCD, SET_CG_RAM_ADDRESS(cgramAddr));
    SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    

    for (uint8_t r = 0; r < 8; r++)
    {
        // Direct cast from struct to uint8_t (union ensures correct packing)
        uint8_t rowValue = (uint8_t)LCD_CustomChars[charIndex][r];

        sendData(LCD, WRITEDATA_CGorDD_RAM(rowValue));    // ready to send to CGRAM
        SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //43 microSec
    }
}

void LCD_saveAllCustomCharacter (LCD_cfg_t* LCD)
{
    for (uint8_t charIndex = 0; charIndex < 8; charIndex++)
    {
        LCD_saveCustomCharacter(LCD,charIndex);
    }
}


static void sendCommand (LCD_cfg_t* LCD, COMMAND_enm_t command)
{
    for (int i=0; i<LCD_PINNUMBER-1; i++)   //write on all lcd pins (D0->RS) exept EN
    {
        GPIO_setPinVal(&LCD->LCD_pins[i], ((command >> i) & 0b1u));
    }
    triggerEnable(LCD);
}

static void sendData (LCD_cfg_t* LCD, uint32_t data)
{
    for (int i=0; i<LCD_PINNUMBER-1; i++)   //write on all lcd pins (D0->RS) exept EN
    {
        GPIO_setPinVal(&LCD->LCD_pins[i], ((data >> i) & 0b1u));
    }
    triggerEnable(LCD);
}

static void triggerEnable(LCD_cfg_t* LCD)
{
   GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
   SYSTICK_WaitBlocking_ms(ENABL_DELAY);
   GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
   SYSTICK_WaitBlocking_ms(ENABL_DELAY);
}