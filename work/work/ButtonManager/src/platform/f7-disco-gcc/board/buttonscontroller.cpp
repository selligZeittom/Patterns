/*
 * buttonscontroller.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <board/buttonscontroller.h>

ButtonsController::ButtonsController() {
	// TODO Auto-generated constructor stub
	for(int i  = 0; i < NB_BUTTONS; i++)
	{
		buttons[i] = 0;
	}
}

ButtonsController::~ButtonsController() {
	// TODO Auto-generated destructor stub
}

void ButtonsController::onIrq() {

}

ButtonsController* ButtonsController::getInstance()
{
	static ButtonsController* theButtonController = nullptr;
	if(!theButtonController)
	{
		theButtonController = new ButtonsController();
	}
	return theButtonController;
}

/*
bool ButtonsController::registerCallback(
		ButtonsControllerCallbackProvider* callbackProvider,
		ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
}
*/

XFEventStatus ButtonsController::processEvent() {

}

void ButtonsController::initRelations()
{
}

bool ButtonsController::registerCallback(
		interface::ButtonsControllerCallbackProvider* callbackProvider,
		interface::ButtonsControllerCallbackProvider::CallbackMethod callbackMethod) {
}
