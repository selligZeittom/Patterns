/*
 * button_fsm.cpp
 *
 *  Created on: 3 avr. 2019
 *      Author: Gilles Mottiez
 */

#include <button/button_fsm.h>
#include "mdw/button/buttoneventshandler.h"

ButtonFSM::ButtonFSM() {
	this->currentState = STATE_INITIAL;
	this->idFsm = -1;
	this->theHandler = nullptr;
}

ButtonFSM::ButtonFSM(int id, ButtonEventsHandler* parent) {
	this->currentState = STATE_INITIAL;
	this->idFsm = id;
	this->theHandler = parent;
}

ButtonFSM::~ButtonFSM() {
}

XFEventStatus ButtonFSM::processEvent() {
	XFEventStatus eventStatus = XFEventStatus::Unknown;
	STATE_BTN oldState = this->currentState;

	//on transitions actions
	switch (currentState) {
	case STATE_INITIAL:
		if (getCurrentEvent()->getEventType() == XFEvent::Initial) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_WAIT:
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == evButtonPressedId) {
			currentState = STATE_BTN_PRESSED;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_BTN_PRESSED:
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout
				&& getCurrentEvent()->getId() == EVENT_ID_LONG) {
			currentState = STATE_LONG_PRESS;
			eventStatus = XFEventStatus::Consumed;
		}
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == evButtonReleasedId) {
			currentState = STATE_SHORT_PRESS;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_LONG_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::NullTransition) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_SHORT_PRESS:
		if (getCurrentEvent()->getEventType() == XFEvent::NullTransition) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	default:
		break;
	}
	if (oldState != this->currentState) {
		//on entry actions
		switch (currentState) {
		case STATE_INITIAL:
			Trace::out("[buttonFsm] : state initial");
			break;
		case STATE_WAIT:
			Trace::out("[buttonFsm] : state wait");
			break;
		case STATE_BTN_PRESSED:
			Trace::out("[buttonFsm] : state btn pressed");
			XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
					EVENT_ID_LONG, 1000, this);
			break;
		case STATE_SHORT_PRESS:
			Trace::out("[buttonFsm] : state short press");
			XFTimeoutManagerDefault::getInstance()->unscheduleTimeout(
					EVENT_ID_LONG, this);

			//let the handler know that the button's state changed
			if (theHandler) {
				theHandler->notifyShortPress(this->idFsm);
			}

			//back to wait state
			pushEvent(new XFNullTransition());
			break;
		case STATE_LONG_PRESS:
			Trace::out("[buttonFsm] : state long press");

			//let the handler know that the button's state changed
			if (theHandler) {
				theHandler->notifyLongPress(this->idFsm);
			}

			//back to wait state
			pushEvent(new XFNullTransition());
			break;
		default:
			break;
		}
	}
	return eventStatus;
}

void ButtonFSM::onBtnChanged(bool isPressed) {
	Trace::out("[buttonFsm] : onBtnChanged()");
	if (isPressed) {
		pushEvent(new evButtonPressed());
	} else {
		pushEvent(new evButtonReleased());
	}
}

void ButtonFSM::setId(int id) {
	this->idFsm = id;
}

void ButtonFSM::setHandler(ButtonEventsHandler* parent) {
	this->theHandler = parent;
}

int ButtonFSM::getId() const {
	return this->idFsm;
}
