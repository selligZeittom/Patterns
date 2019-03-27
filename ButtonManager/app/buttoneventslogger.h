/*
 * buttoneventslogger.h
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BUTTONEVENTSLOGGER_H_
#define BUTTONEVENTSLOGGER_H_

#include <interface/buttoneventshandlerobserver.h>
#include "mdw/trace/trace.h"
#include "xf/behavior.h"
#include "xf/port/default/timeoutmanager-default.h"


class ButtonEventsLogger: public interface::ButtonEventsHandlerObserver, XFBehavior
{
public:
	ButtonEventsLogger();
	virtual ~ButtonEventsLogger();

	//from the interface
	virtual void onButtonShortPressed(ButtonIndex buttonIndex); ///< @brief Called by the subject upon a button short pressed.
	virtual void onButtonLongPressed(ButtonIndex buttonIndex); ///< @brief Called by the subject upon a button long pressed.

	//from the state machine class
	virtual XFEventStatus processEvent();

protected:

	typedef enum {
		STATE_INITIAL = 0,
		STATE_WAIT = 1,
		STATE_SHORT_PRESS = 2,
		STATE_LONG_PRESS = 3
	} STATE_LOGGER;

	enum {
		EVENT_ID_SHORT = 0,
		EVENT_ID_LONG = 1,
		EVENT_ID_WAIT = 2
	};

	enum {
		EVENT_DB_SHORT = 0,
		EVENT_DB_LONG = 1,
		EVENT_DB_WAIT = 2
	};

	STATE_LOGGER currentState;
};

#endif /* BUTTONEVENTSLOGGER_H_ */
