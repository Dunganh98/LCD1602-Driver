/*
 * CLcdTest.cpp
 *
 *  Created on: May 2, 2022
 *      Author: D.Anh
 */

#include "CLcdTest.h"
#include "CLcd1602.h"

void CLcdTest::run(){
	// create a bus with 4 pins for DB-channel of LCD (DB4-DB7)
	CGpioBus dataBus = CGpioBus().addPin(GPIOA,11)
								.addPin(GPIOA,12)
								.addPin(GPIOB,1)
								.addPin(GPIOB,2);
	CGpioPin rsPin(GPIOD,2);
	CGpioPin enablePin(GPIOC,9);
	CLcd1602 LCD(&rsPin, &enablePin, &dataBus);
	LCD.init();
	while(true){
		LCD.setCursor(0, 3);
		LCD.write("Hello");
		LCD.setCursor(1, 7);
		LCD.write("World!");
	}
}

