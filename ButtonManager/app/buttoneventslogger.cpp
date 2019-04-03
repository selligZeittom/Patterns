/*
 * buttoneventslogger.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/buttoneventslogger.h>

#define debugMode 0

ButtonEventsLogger::ButtonEventsLogger() {
	currentState = STATE_INITIAL;
}

ButtonEventsLogger::~ButtonEventsLogger() {
}

void ButtonEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex) {
	pushEvent(new XFEvent(XFEvent::Event, buttonIndex, this));
}

void ButtonEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex) {
	pushEvent(new XFEvent(XFEvent::Event, buttonIndex + 10, this));
}

void ButtonEventsLogger::initRelations() {
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
				&& (getCurrentEvent()->getId() == EVENT_ID_SHORT0
						|| getCurrentEvent()->getId() == EVENT_ID_SHORT1
						|| getCurrentEvent()->getId() == EVENT_ID_SHORT2
						|| getCurrentEvent()->getId() == EVENT_ID_SHORT3)) {
			currentState = STATE_SHORT_PRESS;
			eventStatus = XFEventStatus::Consumed;
		} else if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& (getCurrentEvent()->getId() == EVENT_ID_LONG0
						|| getCurrentEvent()->getId() == EVENT_ID_LONG1
						|| getCurrentEvent()->getId() == EVENT_ID_LONG2
						|| getCurrentEvent()->getId() == EVENT_ID_LONG3)) {
			currentState = STATE_LONG_PRESS;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_SHORT_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::NullTransition
				&& getCurrentEvent()->getId() == EVENT_ID_WAIT) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}

		break;
	case STATE_LONG_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::NullTransition
				&& getCurrentEvent()->getId() == EVENT_ID_WAIT) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	default:
		break;
	}

	//on entry
	if (oldState != this->currentState) {
		switch (currentState) {
		case STATE_WAIT:
			Trace::out("[ButtonEventsLogger] : state wait");
			break;
		case STATE_SHORT_PRESS:
			Trace::out("[ButtonEventsLogger] : state short press");
			pushEvent(new XFNullTransition());
			break;
		case STATE_LONG_PRESS:
			Trace::out("[ButtonEventsLogger] : state long press");
			pushEvent(new XFNullTransition());
			break;
		default:
			break;
		}
	}

	return eventStatus;
}
