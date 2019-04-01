/*
 * factory.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/factory.h>

//must be done here as it is static attributes
ButtonEventsHandler* app::Factory::theButtonEventsHandler = ButtonEventsHandler::getInstance();
ButtonEventsLogger* app::Factory::theButtonEventsLogger = new ButtonEventsLogger();
ButtonsController* app::Factory::theButtonController = ButtonsController::getInstance();

app::Factory::Factory() {

}

void app::Factory::initialize() {
}



void app::Factory::build() {
	theButtonController->initRelations();
	theButtonEventsHandler->initRelations();
	theButtonEventsLogger->initRelations();

	theButtonController->startBehavior();
	theButtonEventsLogger->startBehavior();
}

void Factory_initialize() {
	app::Factory::initialize();
}

void Factory_build() {
	app::Factory::build();
}
