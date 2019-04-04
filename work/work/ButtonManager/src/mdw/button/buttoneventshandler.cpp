/*
 * buttoneventhandler.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <button/buttoneventshandler.h>

/**************************************************************************
 * Public functions
 **************************************************************************/

/*
 * getIntance is the only way to get an instance of ButtonEventsHandler
 */
ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler* theButtonEventsHandler = nullptr;
	if (!theButtonEventsHandler) {
		theButtonEventsHandler = new ButtonEventsHandler(); //will be destroyed by the factory
	}
	return theButtonEventsHandler;
}

/*
 * init relations between an observer and a subject
 * more observers can be added thanks to subscribe(...)
 */
void ButtonEventsHandler::initRelations(
		interface::ButtonEventsHandlerObserver* observer) {
	subscribe(observer);
}

/*
 * this is the callback method called by the caller
 */
void ButtonEventsHandler::onBtnChanged(uint16_t btnIndex, bool isPressed) {
	fsmButtons[btnIndex].onBtnChanged(isPressed);
}

/*
 * starts the behavior of the fsm for the buttons
 */
void ButtonEventsHandler::startStateMachines() {
	for (uint8_t i = 0; i < NB_BUTTONS; i++) {
		fsmButtons[i].startBehavior();
	}
}

/*
 * add one observer to the list
 */
bool ButtonEventsHandler::subscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	observers.push_back(observer);
	return true;
}

/*
 * remove an observer from the list
 */
void ButtonEventsHandler::unsubscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	for (ObserversList::iterator it = observers.begin(); it != observers.end();
			it++) {
		if ((*it) == observer) {
			it = observers.erase(it);
		}
	}
}

/*
 * notify all the observers that a short press occurred
 */
void ButtonEventsHandler::notifyButtonShortPressed(ButtonIndex buttonIndex) {
	for (auto obs : observers) {
		obs->onButtonShortPressed(buttonIndex);
	}
}

/*
 * notify all the observers that a long press occurred
 */
void ButtonEventsHandler::notifyButtonLongPressed(ButtonIndex buttonIndex) {
	for (auto obs : observers) {
		obs->onButtonLongPressed(buttonIndex);
	}
}

/*
 * destructor
 */
ButtonEventsHandler::~ButtonEventsHandler() {
}

/**************************************************************************
 * Private functions
 **************************************************************************/

/*
 * constructor called from getInstance()
 */
ButtonEventsHandler::ButtonEventsHandler() {
	for (uint8_t i = 0; i < NB_BUTTONS; i++) {
		fsmButtons[i].setId(i);
		fsmButtons[i].setHandler(this);
	}
}
