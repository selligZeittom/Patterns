/*
 * buttonscontroller.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <board/buttonscontroller.h>

ButtonsController::ButtonsController() {
	// TODO Auto-generated constructor stub
	for (int i = 0; i < NB_BUTTONS; i++) {
		buttons[i] = 0;
	}
	evOnIrq = new evButtonIrq();
	currentState = STATE_INITIAL;
}

ButtonsController::~ButtonsController() {
	// TODO Auto-generated destructor stub
}

void ButtonsController::onIrq() {
	//launch an event to go to state debounce
	pushEvent(evOnIrq);
}

ButtonsController* ButtonsController::getInstance() {
	static ButtonsController* theButtonController = nullptr;
	if (!theButtonController) {
		theButtonController = new ButtonsController();
	}
	return theButtonController;
}

XFEventStatus ButtonsController::processEvent() {
	XFEventStatus eventStatus = XFEventStatus::Unknown;
	STATE_CONTROLLER oldState = this->currentState;

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
				&& getCurrentEvent()->getId() == evButtonIrqId) {
			currentState = STATE_DEBOUNCE;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_DEBOUNCE:
		if (getCurrentEvent()->getEventType() == XFEvent::Timeout
				&& getCurrentEvent()->getId() == EVENT_ID_DEBOUNCE) {
			currentState = STATE_WAIT;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	default:
		break;
	}
	if (oldState != this->currentState) {
		//on exit actions
		switch (oldState) {
		case STATE_DEBOUNCE:
			Trace::out("[ButtonsController] : /onExit actions");
			checkButtons(); //polling of the buttons
			break;
		default:
			break;
		}

		//on entry actions
		switch (currentState) {
		case STATE_INITIAL:
			Trace::out("[ButtonsController] : state initial");
			break;
		case STATE_WAIT:
			Trace::out("[ButtonsController] : state wait");
			break;
		case STATE_DEBOUNCE:
			Trace::out("[ButtonsController] : state debouncer");
			XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
					EVENT_ID_DEBOUNCE, 100, this);
			break;
		default:
			break;
		}
	}
	return eventStatus;
}

void ButtonsController::initRelations() {
}

bool ButtonsController::registerCallback(
		interface::ButtonsControllerCallbackProvider* callbackProvider,
		interface::ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
	this->called = callbackProvider;
	this->cbMethodPtr = callbackMethod;
	return true;
}

void ButtonsController::call(uint16_t index, GPIO_PinState state) {
	bool isPressed = (state == 1); //isPresse is true if state is '1'
	(called->*cbMethodPtr)(index, isPressed);

}

void ButtonsController::checkButtons() {
	GPIO_PinState val0 = HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin);
	if ((GPIO_PinState) (buttons[0]) != val0) {
		call(0, val0);
	}
	GPIO_PinState val1 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
	if ((GPIO_PinState) (buttons[1]) != val1) {
		call(1, val1);
	}
	GPIO_PinState val2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
	if ((GPIO_PinState) (buttons[2]) != val2) {
		call(2, val2);
	}
	GPIO_PinState val3 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
	if ((GPIO_PinState) (buttons[3]) != val3) {
		call(3, val3);
	}
}
