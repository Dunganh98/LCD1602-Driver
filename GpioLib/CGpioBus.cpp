/*
 * CGpioPin.cpp
 *
 *  Created on: Apr 26, 2022
 *      Author: D.Anh
 */

#include "CGpioBus.h"
#include <cmath>

/**
 * Default constructor
 */
CGpioBus::CGpioBus() {
	m_pins = nullptr;
}

/**
 * Copy constructor (deep copy)
 *
 * @param orig original bus, that is deep copied
 */
CGpioBus::CGpioBus(const CGpioBus& orig){
	Pin* temp = new Pin;
	temp = orig.m_pins;
	// when it is not at the end of the original bus
	while(temp != nullptr)
	{
		// add a new pin from original bus to actual bus
		this->addPin(temp->port, log2(temp->mask));
		// next pin
		temp = temp->next;
	}
}

/**
 *	deep copy a bus
 *
 *	@param src the source bus to be copied
 *	@return the object representing the bus
 */
CGpioBus& CGpioBus::operator= (const CGpioBus& src){
	// clean the bus before copy
	this->~CGpioBus();
	Pin* temp = new Pin;
	temp = src.m_pins;
	// when it is not at the end of the source bus
	while(temp != nullptr)
	{
		// add a new pin from source bus to actual bus
		this->addPin(temp->port, log2(temp->mask));
		temp = temp->next;
	}
	return *this;
}

/**
 * Destructor
 */
CGpioBus::~CGpioBus(){
	// when it is not at the end of the bus
	while(m_pins != nullptr)
	{
		// delete and check next pin
		m_pins = m_pins->next;
		delete m_pins;
	}
}

/**
 * add a new pin to the bus
 *
 * @param port port of the pin
 * @param pinMask bit-position of pin
 * @return the object representing the bus
 */
CGpioBus& CGpioBus::addPin(GPIO_TypeDef* port, uint16_t pinMask){
	// save current value of port and pin to a new pin
	Pin* lastPin = new Pin;
	lastPin->port = port;
	lastPin->mask =  1 << pinMask;
	// next pointer point to NULL (end of bus)
	lastPin->next = nullptr;
	// if it is at the end of bus, assign the new value to bus
	if(m_pins == nullptr)
	{
		m_pins = lastPin;
	}
	// otherweis find the end of bus
	else
	{
		Pin* temp = new Pin;
		temp = m_pins;
		while(temp->next != nullptr)
		{
			temp = temp->next;
		}
		// assign new value to bus
		temp->next = lastPin;
	}
	return *this;
}

/**
 * write value to every pins of the bus
 *
 * @param value the value to be assigned to bus
 * @return the object representing the bus
 */
CGpioBus& CGpioBus::write(uint16_t value){
	Pin* temp = new Pin;
	temp = m_pins;
	uint8_t pos = 0;
	// while it is not at the end of bus
	while(temp != nullptr){
		// compare value and 2^pos, if it is 1 at the pos-bit, then set the
		// actual pin, else reset.
		((value & (1<<pos)) == (1<<pos))
					? HAL_GPIO_WritePin(temp->port,temp->mask,GPIO_PIN_SET)
					: HAL_GPIO_WritePin(temp->port,temp->mask,GPIO_PIN_RESET);
		// next pin
		temp = temp->next;
		// next position
		pos++;
	}
	return *this;
}

/**
 * delegates to write
 *
 * @param value the value to be assigned to bus
 * @return the object representing the bus
 */
CGpioBus& CGpioBus::operator=(uint16_t value){
	return (*this).write(value);
}

/**
 * read the value of all pins of bus in series
 *
 * @return value of all pins in bus
 */
uint16_t CGpioBus::read() const{
	uint16_t value = 0;
	uint8_t pos = 0;
	Pin*temp = new Pin;
	temp = m_pins;
	// while it is not at the end of bus
	while(temp != nullptr){
		// if the readed pin is set
		if(HAL_GPIO_ReadPin(temp->port,temp->mask)){
			// add value with 2^pos
			value+= (1<<pos);
		}
		temp = temp->next;
		pos++;
	}
	return value;
}

/**
 * delegates to read
 *
 * @return value of all pins in bus
 */
CGpioBus::operator uint16_t() const{
	return this->read();
}
