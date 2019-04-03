/*
 * callbackenabler.h
 *
 *  Created on: 3 avr. 2019
 *      Author: Gilles Mottiez
 */

#ifndef BOARD_CALLBACKENABLER_H_
#define BOARD_CALLBACKENABLER_H_

#include "mdw/button/buttoneventshandler.h"

class CallbackEnabler {
public:
	virtual ~CallbackEnabler();

	//definition
	typedef void (CallbackEnabler::*cbMethodPtr)();

	typedef struct CallbackElement {
		ButtonEventsHandler* called;
		cbMethodPtr cbmPtr;
	} CallbackElement;

protected:
	CallbackEnabler();
};

#endif /* BOARD_CALLBACKENABLER_H_ */
