/*
 * buttoneventslogger.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/buttoneventslogger.h>

#define debugMode 1

ButtonEventsLogger::ButtonEventsLogger() {
	// TODO Auto-generated constructor stub
	currentState = STATE_INITIAL;
}

ButtonEventsLogger::~ButtonEventsLogger() {
	// TODO Auto-generated destructor stub
}

void ButtonEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex) {

}

void ButtonEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex) {

}

XFEventStatus ButtonEventsLogger::processEvent() {
	XFEventStatus eventStatus = XFEventStatus::Unknown;
	STATE_LOGGER oldState = this->currentState;

	switch (currentState) {
	case STATE_INITIAL:
		if (getCurrentEvent()->getEventType() == XFEvent::Initial) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}

		break;
	case STATE_WAIT:
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == EVENT_ID_SHORT) {
			currentState = STATE_SHORT_PRESS;
			eventStatus = XFEventStatus::Consumed;
		} else if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == EVENT_ID_LONG) {
			currentState = STATE_LONG_PRESS;
			eventStatus = XFEventStatus::Consumed;
		}
#if (debugMode == 1)
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout
				&& getCurrentEvent()->getId() == EVENT_DB_SHORT) {
			currentState = STATE_SHORT_PRESS;
			eventStatus = XFEventStatus::Consumed;
		}
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout
				&& getCurrentEvent()->getId() == EVENT_DB_LONG) {
			currentState = STATE_LONG_PRESS;
			eventStatus = XFEventStatus::Consumed;
		}
#endif
		break;
	case STATE_SHORT_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == EVENT_ID_WAIT) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
#if (debugMode == 1)
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout
				&& getCurrentEvent()->getId() == EVENT_DB_WAIT) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
#endif
		break;
	case STATE_LONG_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == EVENT_ID_WAIT) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
#if (debugMode == 1)
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout
				&& getCurrentEvent()->getId() == EVENT_DB_WAIT) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
#endif
		break;
	default:
		break;
	}

	//on entry
	if (oldState != this->currentState) {
		switch (currentState) {
		case STATE_INITIAL:
			Trace::out("[ButtonEventsLogger] : state wait");
			break;
		case STATE_WAIT:
			Trace::out("[ButtonEventsLogger] : state short press");
#if (debugMode == 1)
			static bool inv = true;
			if (inv)
				XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
						EVENT_DB_SHORT, 500, this);
			else
				XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
						EVENT_DB_SHORT, 500, this);
			inv = !inv;
#endif
			break;
		case STATE_SHORT_PRESS:
			Trace::out("[ButtonEventsLogger] : state wait");
#if (debugMode == 1)
			XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
					EVENT_DB_WAIT, 500, this);
#endif
			break;
		case STATE_LONG_PRESS:
			Trace::out("[ButtonEventsLogger] : state wait");
#if (debugMode == 1)
			XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
					EVENT_DB_WAIT, 500, this);
#endif
			break;
		default:
			break;
		}
	}

	return eventStatus;
}
