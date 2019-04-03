/*
 * buttoneventhandler.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <button/buttoneventshandler.h>

ButtonEventsHandler::ButtonEventsHandler() {
	// TODO Auto-generated constructor stub

}

void ButtonEventsHandler::onBtnChanged(uint16_t btnIndex, bool isPressed) {
}

ButtonEventsHandler::~ButtonEventsHandler() {
	// TODO Auto-generated destructor stub
}

ButtonEventsHandler* ButtonEventsHandler::getInstance() {
	static ButtonEventsHandler* theButtonEventsHandler = nullptr;
	if(!theButtonEventsHandler)
	{
		theButtonEventsHandler = new ButtonEventsHandler();
	}
	return theButtonEventsHandler;
}

void ButtonEventsHandler::initRelations() {
}
