/*
 * CLcd1602.h
 *
 *  Created on: May 2, 2022
 *      Author: D.Anh
 */

#ifndef SRC_CLCD1602_H_
#define SRC_CLCD1602_H_

#include "CGpioPin.h"
#include "CGpioBus.h"

/**
 * class describe many defined behavior of Lcd in form of function
 * for easier usage
 */

class CLcd1602 {
private:
	// private Attribute
	CGpioPin* m_rs;		// pin register selector
	CGpioPin* m_enable; // pin enable
	CGpioBus* m_data;	// data bus

	/**
	 * write 4-bits data value to data bus and rs value to rs pin.
	 * rs = 0 is command, rs = 1 write to lcd.
	 *
	 * @param rs value of rs pin
	 * @param data data to send
	 */
	void writeNibble(uint8_t rs,uint8_t data);

	/**
	 * write 8-bits data (2 times 4-bits) and rs value, send the upper
	 * nibble first and then send the lower nibble.
	 * rs = 0 is command, rs = 1 write to lcd.
	 *
	 * @param rs value of rs pin
	 * @param data data to send
	 */
	void writeByte(uint8_t rs,uint8_t data);
public:
	/**
	 * parameterized constructor
	 *
	 * @param rs pointer to CGpioPin
	 * @param enable pointer to CGpioPin
	 * @param data pointer to CGpioBus
	 */
	CLcd1602(CGpioPin* rs,CGpioPin* enable, CGpioBus* data);

	/**
	 * initialize lcd
	 */
	void init();

	/**
	 * set cursor to specific row and column
	 *
	 * @param row value of row
	 * @param column value of column
	 */
	void setCursor(int row, int column);

	/**
	 * write string to lcd
	 *
	 * @param text string to write
	 */
	void write(const char* text);
};

#endif /* SRC_CLCD1602_H_ */
