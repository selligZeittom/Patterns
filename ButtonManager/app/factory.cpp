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

/**************************************************************************
 * Public c++ functions
 **************************************************************************/

/*
 * constructor
 */
app::Factory::Factory() {
}

/*
 * destructor
 * responsible to delete the object it created
 * but also the 2 singletons from others class
 */
app::Factory::~Factory() {
	if (theButtonEventsLogger) {
		delete theButtonEventsLogger;
		theButtonEventsLogger = nullptr;
	}

	/*
	 * those 2 objects are singleton created in their getInstance()
	 * they must be deleted here
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

/*
 * initialize
 */
void app::Factory::initialize() {
}

/*
 * building relations between objects
 * starting reactive objects
 * starting the dispatcher
 */
void app::Factory::build() {
	theButtonController->initRelations(theButtonEventsHandler,
			(interface::ButtonsControllerCallbackProvider::CallbackMethod) &ButtonEventsHandler::onBtnChanged);
	theButtonEventsHandler->initRelations(theButtonEventsLogger);
	theButtonEventsLogger->initRelations();

	//start the dispatcher before launching any event
	XFResourceFactoryDefault::getInstance()->getDefaultDispatcher()->start();
	theButtonController->startBehavior();
	//it will call startBehavior() of the 4 fsm inside the handler
	theButtonEventsHandler->startStateMachines();
	theButtonEventsLogger->startBehavior();
}

/**************************************************************************
 * c functions, called from the main
 **************************************************************************/

void Factory_initialize() {
	app::Factory::initialize();
}

void Factory_build() {
	app::Factory::build();
}
