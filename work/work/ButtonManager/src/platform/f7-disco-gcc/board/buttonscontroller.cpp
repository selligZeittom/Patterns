/*
 * buttonscontroller.cpp
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#include <board/buttonscontroller.h>

ButtonsController::ButtonsController() {
	// TODO Auto-generated constructor stub

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
