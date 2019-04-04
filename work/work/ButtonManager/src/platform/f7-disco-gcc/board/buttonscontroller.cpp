/*
 * buttonscontroller.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <board/buttonscontroller.h>

/***************************************************************************
 * public functions
 **************************************************************************/

/*
 * it returns the one and only one instance of a ButtonsController
 */
ButtonsController& ButtonsController::getInstance() {
	static ButtonsController* theButtonController = nullptr;
	if (!theButtonController) {
		theButtonController = new ButtonsController(); //will be destroyed by the factory
	}
	return *theButtonController;
}

/*
 * destructor
 */
ButtonsController::~ButtonsController() {
	if (evOnIrq) {
		delete evOnIrq;
		evOnIrq = nullptr;
	}
}

/*
 * this is called in build() from factory
 */
void ButtonsController::initRelations(
		interface::ButtonsControllerCallbackProvider* callbackProvider,
		interface::ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
	//register the called "button handler" from the factory
	registerCallback(callbackProvider, callbackMethod);
}

/*
 * called from initRelations()
 * it registers the provider and its callback function
 */
bool ButtonsController::registerCallback(
		interface::ButtonsControllerCallbackProvider* callbackProvider,
		interface::ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
	this->called = callbackProvider;
	this->cbMethodPtr = callbackMethod;
	return true;
}

/*
 * it is called from the isr routine
 * launch an event to go to state STATE_DEBOUNCE
 */
void ButtonsController::onIrq() {
	pushEvent(evOnIrq);
}

/*
 * Behavior of this reactive class
 */
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
	case STATE_WAIT: //waiting for an eventOnIrq
		if (getCurrentEvent()->getEventType() == XFEvent::Event
				&& getCurrentEvent()->getId() == evButtonIrqId) {
			currentState = STATE_DEBOUNCE;
			eventStatus = XFEventStatus::Consumed;
		}
		break;
	case STATE_DEBOUNCE: //waiting for the timeout
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
			checkButtons();
			break;
		default:
			break;
		}

		//on entry actions
		switch (currentState) {
		case STATE_DEBOUNCE:
			XFTimeoutManagerDefault::getInstance()->scheduleTimeout(
					EVENT_ID_DEBOUNCE, 10, this);
			break;
		default:
			break;
		}
	}
	return eventStatus;
}

/***************************************************************************
 * private functions
 **************************************************************************/

/*
 * constructor called from getInstance()
 */
ButtonsController::ButtonsController() {
	//buttons defined as pull-up, therefore released = '1'
	for (int i = 0; i < NB_BUTTONS; i++) {
		buttons[i] = 1;
	}
	//will be alive for the whole duration of the program
	evOnIrq = new evButtonIrq();
	currentState = STATE_INITIAL;
	cbMethodPtr = nullptr;
	called = nullptr;
}

/*
 * reads all the button and if there is a difference, notice it to the called
 * can't be done with a loop because of buttons that are not
 * contained in an array
 */
void ButtonsController::checkButtons() {
	GPIO_PinState val0 = HAL_GPIO_ReadPin(BUTTON0_GPIO_Port, BUTTON0_Pin);
	if (buttons[0] != (uint8_t) val0) {
		call(0, val0);
		buttons[0] = val0;
	}
	GPIO_PinState val1 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin);
	if (buttons[1] != (uint8_t) val1) {
		call(1, val1);
		buttons[1] = val1;
	}
	GPIO_PinState val2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
	if (buttons[2] != (uint8_t) val2) {
		call(2, val2);
		buttons[2] = val2;
	}
	GPIO_PinState val3 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
	if (buttons[3] != (uint8_t) val3) {
		call(3, val3);
		buttons[3] = val3;
	}
}

/*
 * calling the method provided by the called
 */
void ButtonsController::call(uint16_t index, GPIO_PinState state) {
	bool isPressed = (state == 0); //isPressed is true if state is '0' because of the pull up
	if (called != nullptr && cbMethodPtr != nullptr) {
		(called->*cbMethodPtr)(index, isPressed); //call the method into the buttonhandler
	}
}
