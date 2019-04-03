/*
 * buttoneventhandler.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <button/buttoneventshandler.h>

ButtonEventsHandler::ButtonEventsHandler() {
	for (uint8_t i = 0; i < NB_BUTTONS; i++) {
		fsmButtons[i].setId(i);
		fsmButtons[i].setHandler(this);
	}
}

void ButtonEventsHandler::onBtnChanged(uint16_t btnIndex, bool isPressed) {
	fsmButtons[btnIndex].onBtnChanged(isPressed);
}

void ButtonEventsHandler::startStateMachines() {
	for (uint8_t i = 0; i < NB_BUTTONS; i++) {
		fsmButtons[i].startBehavior();
	}
}

bool ButtonEventsHandler::subscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	observers.push_back(observer);
}

void ButtonEventsHandler::unsubscribe(
		interface::ButtonEventsHandlerObserver* observer) {
	for (ObserversList::iterator it = observers.begin(); it != observers.end();
			it++) {
		if ((*it) == observer) {
			it = observers.erase(it);
		}
	}
}

void ButtonEventsHandler::notifyButtonShortPressed(ButtonIndex buttonIndex) {
	for (auto obs : observers) {
		obs->onButtonShortPressed(buttonIndex);
	}
}
void ButtonEventsHandler::notifyButtonLongPressed(ButtonIndex buttonIndex) {
	for (auto obs : observers) {
		obs->onButtonLongPressed(buttonIndex);
	}
}

ButtonEventsHandler::~ButtonEventsHandler() {
}

ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler* theButtonEventsHandler = nullptr;
	if (!theButtonEventsHandler) {
		theButtonEventsHandler = new ButtonEventsHandler();
	}
	return theButtonEventsHandler;
}

void ButtonEventsHandler::initRelations(interface::ButtonEventsHandlerObserver* observer) {
	subscribe(observer);
}
