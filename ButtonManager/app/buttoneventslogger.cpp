/*
 * buttoneventslogger.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/buttoneventslogger.h>
#include <string.h>

#define debugMode 0

/*
 * constructor
 */
ButtonEventsLogger::ButtonEventsLogger() {
	currentState = STATE_INITIAL;
}

/*
 * destructor
 */
ButtonEventsLogger::~ButtonEventsLogger() {
}

/*
 * notified by a subject
 */
void ButtonEventsLogger::onButtonShortPressed(ButtonIndex buttonIndex) {
	pushEvent(new XFEvent(XFEvent::Event, buttonIndex, this));
}

/*
 * notified by a subject
 */
void ButtonEventsLogger::onButtonLongPressed(ButtonIndex buttonIndex) {
	pushEvent(new XFEvent(XFEvent::Event, buttonIndex + 10, this));
}

/*
 * called from build() in factory
 */
void ButtonEventsLogger::initRelations() {
}

/*
 * describes the behavior of the state machine
 */
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
	case STATE_WAIT: //waiting for an event with a press id
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& (getCurrentEvent()->getId() == EVENT_ID_SHORT0
						|| getCurrentEvent()->getId() == EVENT_ID_SHORT1
						|| getCurrentEvent()->getId() == EVENT_ID_SHORT2
						|| getCurrentEvent()->getId() == EVENT_ID_SHORT3))
		{
			currentState = STATE_SHORT_PRESS;
			Trace::out("[ButtonEventsLogger] : short press on buttonId %d", (getCurrentEvent()->getId() % 10));
			eventStatus = XFEventStatus::Consumed;
		}
		else if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& (getCurrentEvent()->getId() == EVENT_ID_LONG0
						|| getCurrentEvent()->getId() == EVENT_ID_LONG1
						|| getCurrentEvent()->getId() == EVENT_ID_LONG2
						|| getCurrentEvent()->getId() == EVENT_ID_LONG3))
		{
			currentState = STATE_LONG_PRESS;
			Trace::out("[ButtonEventsLogger] : long press on buttonId %d", (getCurrentEvent()->getId() % 10));
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_SHORT_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::NullTransition) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}

		break;
	case STATE_LONG_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::NullTransition) {
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
		case STATE_SHORT_PRESS:
			pushEvent(new XFNullTransition());
			break;
		case STATE_LONG_PRESS:
			pushEvent(new XFNullTransition());
			break;
		default:
			break;
		}
	}
	return eventStatus;
}
