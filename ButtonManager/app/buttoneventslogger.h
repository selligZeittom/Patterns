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


class ButtonEventsLogger: public interface::ButtonEventsHandlerObserver, public XFBehavior
{
public:
	ButtonEventsLogger();
	virtual ~ButtonEventsLogger();

	//factory patterns
	void initRelations();

	//from the interface
	virtual void onButtonShortPressed(ButtonIndex buttonIndex);
	virtual void onButtonLongPressed(ButtonIndex buttonIndex);

	//from the state machine class
	virtual XFEventStatus processEvent();

protected:

	typedef enum {
		STATE_INITIAL = 0,
		STATE_WAIT = 1,
		STATE_SHORT_PRESS = 2,
		STATE_LONG_PRESS = 3
	} STATE_LOGGER;

	/*
	 * this allows to know which button changed with only one fsm in the logger
	 * to create the right EVENT_ID :
	 * 	-	add the index of the button and 0 for a short press
	 * 	-	add the index of the button and 10  for a long press
	 *
	 * 	now to recover the index of the button from any EVENT_ID,
	 * 	simply do EVENT_ID % 10
	 */
	enum {
		EVENT_ID_SHORT0 = 0,
		EVENT_ID_SHORT1 = 1,
		EVENT_ID_SHORT2 = 2,
		EVENT_ID_SHORT3 = 3,
		EVENT_ID_LONG0 = 10,
		EVENT_ID_LONG1 = 11,
		EVENT_ID_LONG2 = 12,
		EVENT_ID_LONG3 = 13,
		EVENT_ID_WAIT = 20
	};

	STATE_LOGGER currentState;
};

#endif /* BUTTONEVENTSLOGGER_H_ */
