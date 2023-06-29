#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>

uint8_t DISPLAY_W[3];
uint8_t DISPLAY_T[3];
uint8_t DISPLAY_DATA[10] = {0x7D, 0x41, 0xDC, 0xD5, 0xE1, 0xB5, 0xBD, 0x51, 0xFD, 0xF5};

void loop(void)
{
    LED_Toggle();
    memcpy(DISPLAY_T, DISPLAY_W, 3);
    CSE_SetLow();
    SPI1_ExchangeBlock(DISPLAY_T, 3);
    CSE_SetHigh();
}

uint8_t display_data(uint8_t SEGMENT, uint8_t NUMBER)
{
    if(SEGMENT <= 7)
    {
        DISPLAY_W[1] = 0x01 << SEGMENT;
        DISPLAY_W[0] &= 0xF0;
    }
    else 
    {
        DISPLAY_W[1] = 0x00;
        uint8_t tmp = DISPLAY_W[0] & 0xF0;
        DISPLAY_W[0] = 0x1 << (SEGMENT - 8);
        DISPLAY_W[0] |= tmp;
    }
    
    DISPLAY_W[2] = DISPLAY_DATA[NUMBER];
    
    return 0;
    
}

uint8_t display_leds(uint8_t LED_NUMBER, uint8_t VALUE)
{
    
}

void main(void)
{
    SYSTEM_Initialize();
    
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    TMR1_SetInterruptHandler(loop);
    
    while (1)
    {
        display_data(11, 3);
//        DISPLAY_W[0] = 0x70;
//        DISPLAY_W[1] = 0x00 << 7;
//        for(uint8_t i = 0; i < 10; i++)
//        {
//            DISPLAY_W[2] = DISPLAY_DATA[i];
//            __delay_ms(500);
//        }
    }
}