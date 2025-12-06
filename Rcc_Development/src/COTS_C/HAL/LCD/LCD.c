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

static void sendCommand_synch (LCD_cfg_t* LCD, COMMAND_enm_t command);
static void sendData_synch (LCD_cfg_t* LCD, uint32_t data);

/******************************** init function ******************************/

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

// Asynchronus LCD functions
#include "Sched.h"

// static LCD_states_enm_t LCD_curState [LCD_NUMBER] = {LCD_NO_ACTION};
// static LCD_initSeq_enu_t LCD_initSeq [LCD_NUMBER] = {NO_ACTION};

void LCD_RunnableFunction_sch (void* arg);

static Runnable_t LCD_0_Runnable;

void LCD_RunnableFunction_sch (void* arg)
{
    LCD_cfg_t* LCD = ((LCD_cfg_t*)arg);
    switch (LCD->LCD_curState)
    {
    case LCD_INIT:
        switch (LCD->LCD_initSeq)
        {
        case FUNCTION_SET_start:
            sendCommand_synch(LCD,INIT0_8B_FUNCTION_SET__LINEtwo_5X7);
            GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
            LCD->LCD_initSeq ++;
            break;
        case FUNCTION_SET_end:
            GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
            LCD->LCD_initSeq ++;
            break;
        case DISPLAY_ON_start:
            sendCommand_synch(LCD,INIT1_DISPLAY_CONTROL__DISon_CURSon_BLINKon);
            GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
            LCD->LCD_initSeq ++;
            break;
        case DISPLAY_ON_end:
            GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
            LCD->LCD_initSeq ++;
            break;
        case CLEAR_start:
            sendCommand_synch(LCD,INIT2_8B_DISPLAY__CLEAR);
            GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
            LCD->LCD_initSeq ++;
            break;
        case CLEAR_end:
            GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
            LCD->LCD_initSeq ++;
            break;
        case ENTRY_MODE_start:
            sendCommand_synch(LCD,INIT3_8B_ENTRY_MODE_SET__INC_SHoff);
            GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
            LCD->LCD_initSeq ++;
            break;
        case ENTRY_MODE_end:
            GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
            LCD->LCD_initSeq ++;
            break;
        case INIT_DONE:
            LCD->LCD_curState = LCD_NO_ACTION;
            // notify_cbf();
            break;
        default:
            break;
        }
        break;
    case LCD_WRITE:
        switch (LCD->LCD_writeState)
        {
        case LCDw_SET_CURSOR_start:
            if (positionStart != 0xffff)
            {
                sendCommand_synch(LCD, SET_DD_RAM_ADDRESS(positionStart));
                LCD->cursorPosition = positionStart;
            }
            // wrap to next line automatically
            else if (LCD->cursorPosition == 0x10)      
            {
                LCD->cursorPosition = 0x40; // move to line 2 start
                sendCommand_synch(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));    //39 microSec   
            }
            else if (LCD->cursorPosition == 0x50) 
            {
                LCD->cursorPosition = 0x00; // wrap to line 1
                sendCommand_synch(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));  //39 microSec   
            }
            else
            {
                sendCommand_synch(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));    //39 microSec
                (LCD->cursorPosition)++;
            }
            LCD->LCD_writeState++; 
            break;
        case LCDw_SET_CURSOR_end:
            GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
            LCD->LCD_writeState++; 
            break;
        case LCDw_WRITE_start:
            if (requiredString_buff != NULLPTR)
            {
                if ((*requiredString_buff) != '\0')
                {
                    sendData_synch(LCD, WRITEDATA_CGorDD_RAM(*requiredString_buff));    //43 microSec
                    (LCD->cursorPosition)++;
                    requiredString_buff++;
                    LCD->LCD_writeState++;  
                }
                else
                {
                    LCD->LCD_curState = LCD_NO_ACTION;
                }
            }
            else
            {
                LCD->LCD_curState = LCD_NO_ACTION; //go out of this switch case "error"
            }
            break;
        case LCDw_WRITE_end:
            GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
            if ((*requiredString_buff) != '\0')
            {
                if (LCD->cursorPosition == 0x10)      
                {
                    LCD->LCD_writeState = LCDw_SET_CURSOR_start;
                }
                else if (LCD->cursorPosition == 0x50) 
                {
                    LCD->LCD_writeState = LCDw_SET_CURSOR_start;
                }
                else
                {
                    LCD->LCD_writeState = LCDw_WRITE_start;
                }
            }
            else
            {
                LCD->LCD_curState = LCD_NO_ACTION;
            }
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}


void LCD_asych_init (LCD_cfg_t* LCD)
{
    for (int i=0; i<LCD_PINNUMBER; i++) //INITIALIZING pins form D0 to EN
    {
        GPIO_identfyPin(&LCD->LCD_pins[i],LCD->LCD_pins[i].port,LCD->LCD_pins[i].pin); //GPIOA/B/C/D/E , pin number 0-15
        GPIO_setPinDirMode(&LCD->LCD_pins[i],OUTPUT);  //input, output, alternate, analog
        GPIO_setOutPinMode(&LCD->LCD_pins[i],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
        GPIO_selectAlternateFunc(&LCD->LCD_pins[i], DIO);
        GPIO_creatPin(&LCD->LCD_pins[i]);
    }
    // is every runnable should global?   later
    // filling the LCD Runnable
        LCD_0_Runnable.func= LCD_RunnableFunction_sch;
        LCD_0_Runnable.priority = LCD_RUNNABLE_PRIORITY;
        LCD_0_Runnable.priodicity_ticks=5;   //ms
        LCD_0_Runnable.first_delay=30; //ms
        LCD_0_Runnable.arg = (void*)LCD;
    Sched_registerRunnable(&LCD_0_Runnable);
    LCD->LCD_initSeq = FUNCTION_SET_start; 
    LCD->LCD_curState = LCD_INIT;
}

// send 0xffff in the position to keep the cursor as it is
uint8_t LCD_writeString_asynch (LCD_cfg_t* LCD, char* string, uint32_t position)
{
    // sendCommand_synch(LCD, SET_DD_RAM_ADDRESS(LCD->cursorPosition));
    // SYSTICK_WaitBlocking_ms(WRITE_DELAY);    //39 microSec
    if (LCD->LCD_initSeq == INIT_DONE && LCD->LCD_curState == LCD_NO_ACTION)
    {
        if (string!=NULL)
        {
            if (requiredString_buff == NULLPTR)
            {                
                requiredString_buff = (uint8_t *) string;
                LCD->LCD_curState = LCD_WRITE;
                LCD->LCD_writeState = LCDw_SET_CURSOR_start;
                return LCD_PRINTING;                
            }
            
        }
        if (position != 0xffff)
        {
            positionStart = position;
        }
    }
    return LCD_BUSY;
}


static void sendCommand_synch (LCD_cfg_t* LCD, COMMAND_enm_t command)
{
    for (int i=0; i<LCD_PINNUMBER-1; i++)   //write on all lcd pins (D0->RS) exept EN
    {
        GPIO_setPinVal(&LCD->LCD_pins[i], ((command >> i) & 0b1u));
    }
    GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
}

static void sendData_synch (LCD_cfg_t* LCD, uint32_t data)
{
    for (int i=0; i<LCD_PINNUMBER-1; i++)   //write on all lcd pins (D0->RS) exept EN
    {
        GPIO_setPinVal(&LCD->LCD_pins[i], ((data >> i) & 0b1u));
    }
    GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
}

static inline void triggerEnable_synch_high (LCD_cfg_t* LCD)
{
   GPIO_setPinVal(&LCD->LCD_pins[EN], 1);
}

static inline void triggerEnable_synch_low (LCD_cfg_t* LCD)
{
   GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
}

static inline void LCD_setCursorPosition_synch (LCD_cfg_t* LCD, uint32_t position)
{
    sendCommand_synch(LCD, SET_DD_RAM_ADDRESS(position));
    LCD->cursorPosition = position;
}
