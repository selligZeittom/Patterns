/*
 * buttoneventslogger.h
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BUTTONEVENTSLOGGER_H_
#define BUTTONEVENTSLOGGER_H_

#include <interface/buttoneventshandlerobserver.h>

class ButtonEventsLogger: public interface::ButtonEventsHandlerObserver {
public:
	ButtonEventsLogger();
	virtual ~ButtonEventsLogger();

	//from the interface
	void onButtonShortPressed(ButtonIndex buttonIndex); ///< @brief Called by the subject upon a button short pressed.
	void onButtonLongPressed(ButtonIndex buttonIndex); ///< @brief Called by the subject upon a button long pressed.

};

#endif /* BUTTONEVENTSLOGGER_H_ */
