/*
 * factory.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/factory.h>

app::Factory::Factory() {

}

void app::Factory::initialize() {
	theButtonController = ButtonsController::getInstance();
	theButtonEventsHandler = ButtonEventsHandler::getInstance();
	theButtonEventsLogger = new ButtonEventsLogger();
}

void app::Factory::build() {
	theButtonController->initRelations();
	theButtonEventsHandler->initRelations();
	theButtonEventsLogger->initRelations();
}

void Factory_initialize() {
	app::Factory::initialize();
}

void Factory_build() {
	app::Factory::build();
}
