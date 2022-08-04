/*
 * CLcd1602.cpp
 *
 *  Created on: May 2, 2022
 *      Author: D.Anh
 */

#include "CLcd1602.h"
#include "tim.h"

CLcd1602::CLcd1602(CGpioPin* rs,CGpioPin* enable, CGpioBus* data)
{
	// default constructor assign parameter to class attribute
	m_rs = rs;
	m_enable = enable;
	m_data = data;
}

void CLcd1602::writeNibble(uint8_t rs,uint8_t data){
	*m_rs = rs;
	*m_data = data;
	// set E pin high to process data
	*m_enable = 1;
	// E pulse width must min = 250ns --> it is necessary to delay (1 ms)
	// for processing data and easier to decode with logic analyzer
	HAL_Delay(1);
	// reset E pin
	*m_enable = 0;
	HAL_Delay(1);
}

void CLcd1602::writeByte(uint8_t rs,uint8_t data){
    // send 4 high bits
    writeNibble(rs,((data >> 4)&0x0f));
    // send 4 low bits
    writeNibble(rs, ((data)&0x0f));
}

void CLcd1602::init(){
	// LCD contrast 30%
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_Delay(15);
	// first and second soft reset
	writeByte(0,0x33);
	HAL_Delay(5);
	// third soft reset and 4-Bit mode
	writeByte(0,0x32);
	// Function set N =1, F = 0
	writeByte(0,0x28);
	// Display off
	writeByte(0,0x08);
	// Display clear
	writeByte(0,0x01);
	// Entry mode set
	writeByte(0,0x06);
	// Display on, cursor on, blink on
	writeByte(0,0x0F);
}

void CLcd1602::setCursor(int row, int column){
    switch (row)
    {
    	// first line
        case 0:
        	// first line start from 0x80 + actual column
            column |= 0x80;
            break;
        // second line
        case 1:
        	// second line start from 0xC0 + actual column
            column |= 0xC0;
            break;
    }
    // send command to set cursor
    writeByte(0,column);
}

void CLcd1602::write(const char* text){
	// if *text not "/0", write text to lcd and increment
	while (*text) writeByte(1,*text++);
}
