#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>

uint8_t DISPLAY_W[3] ;// = {0xFF, 0x00, 0x00};
uint8_t DISPLAY_T[3];
uint8_t DISPLAY_DATA[10] = {0x7D, 0x41, 0xDC, 0xD5, 0xE1, 0xB5, 0xBD, 0x51, 0xFD, 0xF5};


uint8_t display_data(uint8_t SEGMENT, uint8_t NUMBER)
{
//    DISPLAY_W[0] = 0x10;
    SEGMENT -= 1;
    if(SEGMENT < 8)
    {
        DISPLAY_W[1] = 0x01 << SEGMENT;
        DISPLAY_W[0] &= 0xF0;
    }
    else 
    {
        DISPLAY_W[1] = 0x00;
        uint8_t tmp = DISPLAY_W[0] & 0xF0;
        DISPLAY_W[0] = 0x01 << (SEGMENT - 8);
        DISPLAY_W[0] |= tmp;
    }
    
    DISPLAY_W[2] = DISPLAY_DATA[NUMBER];
    memcpy(DISPLAY_T, DISPLAY_W, 3);

    
    return 0;
    
}

uint8_t display_leds(uint8_t LED_NUMBER, uint8_t VALUE)
{   
    LED_NUMBER -= 1;
    uint8_t tmp = DISPLAY_W[0] & 0xF0;
//    DISPLAY_W[0] = 0x1F;
    if (VALUE == 1)
    {
        DISPLAY_W[0] = 0x10 << LED_NUMBER;
        DISPLAY_W[0] |= tmp;
    }
    else if (VALUE == 0)
    {
        DISPLAY_W[0] &= (0x10 << LED_NUMBER) ^ 0xF0;
        
    }
    
    memcpy(DISPLAY_T, DISPLAY_W, 3);

    return 0;

}
uint8_t i = 1;
void loop(void)
{
//    LED_Toggle();
    
//    memcpy(DISPLAY_T, DISPLAY_W, 3);
    CSE_SetLow();    
    display_leds(1, 1);    
    display_leds(2, 1);
    display_leds(3, 1);
    
    display_data(i, 5);
    i++;
    if(i >= 13)
    {
        i = 1;
    }

    
    SPI1_ExchangeBlock(DISPLAY_T, 3);
    
    CSE_SetHigh();
}

void main(void)
{
    SYSTEM_Initialize();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_SetInterruptHandler(loop);
           
    while (1)
    {
        
    }
}