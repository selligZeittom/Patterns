/*
 * factory.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/factory.h>
#include "xf/port/default/resourcefactory-default.h"

//must be done here as it is static attributes
ButtonEventsHandler* app::Factory::theButtonEventsHandler =
		ButtonEventsHandler::getInstance();
ButtonEventsLogger* app::Factory::theButtonEventsLogger =
		new ButtonEventsLogger();
ButtonsController* app::Factory::theButtonController =
		&(ButtonsController::getInstance());

app::Factory::Factory() {
}

app::Factory::~Factory() {
	if (theButtonEventsLogger) {
		delete theButtonEventsLogger;
		theButtonEventsLogger = nullptr;
	}

	/*
	 * those 2 objects are singleton created in their getInstance()
	 * but they're deleted here when the factory is killed
	 */
	if (theButtonController) {
		delete theButtonController;
		theButtonController = nullptr;
	}
	if (theButtonEventsHandler) {
		delete theButtonEventsHandler;
		theButtonEventsHandler = nullptr;
	}
}

void app::Factory::initialize() {
}

void app::Factory::build() {
	theButtonController->initRelations(theButtonEventsHandler,
			(interface::ButtonsControllerCallbackProvider::CallbackMethod) &ButtonEventsHandler::onBtnChanged);
	theButtonEventsHandler->initRelations(theButtonEventsLogger);
	theButtonEventsLogger->initRelations();

	//start the dispatcher before launching any event
	XFResourceFactoryDefault::getInstance()->getDefaultDispatcher()->start();
	theButtonController->startBehavior();
	theButtonEventsHandler->startStateMachines(); //it will call startBehavior() of the 4 fsm
	theButtonEventsLogger->startBehavior();
}

void Factory_initialize() {
	app::Factory::initialize();
}

void Factory_build() {
	app::Factory::build();
}
