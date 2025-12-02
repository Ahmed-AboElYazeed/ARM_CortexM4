#include "LCD/LCD.h"
#include "GPIO/GPIO.h"
#include "SYSTICK/SYSTICK.h"

/************* helper functions ******************/
static void triggerEnable(LCD_cfg_t* LCD);
static void sendCommand (LCD_cfg_t* LCD, COMMAND_enm_t command);
static void sendData (LCD_cfg_t* LCD, uint32_t data);

/********************************init funxtion ******************************/

/*     method 1       */

    // extern LCD_cfg_t LCD_cfg[LCD_NUMBER];
    // void LCD_init ()
    // {
    //     // initialize pins (OUTPUT)
    //     for (int LCD_x = 0; LCD_x < LCD_NUMBER; LCD_x++)    //INITIALIZING LCD from LCD_0 to LCD_x
    //     {
    //         for (int i=0; i<LCD_PINNUMBER; i++) //INITIALIZING pins form D0 to EN
    //         {
    //             GPIO_identfyPin(&LCD_cfg[LCD_x].LCD_pins[i],LCD_cfg[LCD_x].LCD_pins[i].port,LCD_cfg[LCD_x].LCD_pins[i].pin); //GPIOA/B/C/D/E , pin number 0-15
    //             GPIO_setPinDirMode(&LCD_cfg[LCD_x].LCD_pins[i],OUTPUT);  //input, output, alternate, analog
    //             GPIO_setOutPinMode(&LCD_cfg[LCD_x].LCD_pins[i],PUSH_PULL,PULL_DOWN);   //push-pull/open-drain , pull-up/pull-down
    //             GPIO_selectAlternateFunc(&LCD_cfg[LCD_x].LCD_pins[i], DIO); 
    //             GPIO_creatPin(&LCD_cfg[LCD_x].LCD_pins[i]);
    //         }        
    //     }
        
    //     SYSTICK_WaitBlocking_ms(50); //30ms
    // }


/*     method 2       */

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
    SYSTICK_WaitBlocking_ms(50); //30ms

    sendCommand(LCD,INIT0_8B_FUNCTION_SET__LINEtwo_5X7);
    SYSTICK_WaitBlocking_ms(2);    //39 microSec
    
    sendCommand(LCD,INIT1_DISPLAY_CONTROL__DISon_CURSon_BLINKon);
    SYSTICK_WaitBlocking_ms(2);    //39 microSec
    
    sendCommand(LCD,INIT2_8B_DISPLAY__CLEAR);
    SYSTICK_WaitBlocking_ms(5);    //1.53ms

    sendCommand(LCD,INIT3_8B_ENTRY_MODE_SET__INC_SHoff);
    SYSTICK_WaitBlocking_ms(5);    //1.53ms
}

// static void changePinDirection (GPIO_pinCfg_t* pinConfig, uint8_t dir)
// {
//     GPIO_setPinDirMode(pinConfig,dir);  //input, output, alternate, analog
//     GPIO_creatPin(pinConfig);
// }

void LCD_writeChar (LCD_cfg_t* LCD, char character)
{
    //SYSTICK_WaitBlocking_ms(100);    //
    // sendCommand(LCD, RETURN_HOME);
    // SYSTICK_WaitBlocking_ms(2);    //39 microSec
    sendCommand(LCD, SET_DD_RAM_ADDRESS(1));
    SYSTICK_WaitBlocking_ms(2);    //39 microSec
    sendData(LCD, WRITEDATA_CGorDD_RAM(character));
    SYSTICK_WaitBlocking_ms(2);    //43 microSec
}

void LCD_writeString (LCD_cfg_t* LCD, char* string)
{
    sendCommand(LCD, RETURN_HOME);
    SYSTICK_WaitBlocking_ms(2);    //39 microSec
    sendCommand(LCD, SET_DD_RAM_ADDRESS(0));
    SYSTICK_WaitBlocking_ms(2);    //39 microSec
    int i=0;
    while (string[i]!='\0')
    {
        sendData(LCD, WRITEDATA_CGorDD_RAM(string[i]));
        SYSTICK_WaitBlocking_ms(2);    //43 microSec
        i++;
    }
}

void LCD_clearLCD (LCD_cfg_t* LCD)
{
    sendCommand(LCD,CLEAR_DISPLAY);
    SYSTICK_WaitBlocking_ms(5);    //1.53ms
}

void LCD_setCursorPosition (LCD_cfg_t* LCD)
{

}

void LCD_saveCustomCharacter (LCD_cfg_t* LCD)
{

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
   SYSTICK_WaitBlocking_ms(5);
   GPIO_setPinVal(&LCD->LCD_pins[EN], 0);
   SYSTICK_WaitBlocking_ms(5);
}