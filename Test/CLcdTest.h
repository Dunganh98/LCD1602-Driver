/*
 * CLcdTest.h
 *
 *  Created on: May 2, 2022
 *      Author: D.Anh
 */

#ifndef SRC_CLCDTEST_H_
#define SRC_CLCDTEST_H_

class CLcdTest {
public:
	void run();
};

#endif /* SRC_CLCDTEST_H_ */

extern "C" void runLcdTest(){
	CLcdTest().run();
}
