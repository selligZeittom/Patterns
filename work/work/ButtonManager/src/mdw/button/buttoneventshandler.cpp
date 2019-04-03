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

ButtonEventsHandler::~ButtonEventsHandler() {
}

ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler* theButtonEventsHandler = nullptr;
	if (!theButtonEventsHandler) {
		theButtonEventsHandler = new ButtonEventsHandler();
	}
	return theButtonEventsHandler;
}

void ButtonEventsHandler::initRelations() {
}
