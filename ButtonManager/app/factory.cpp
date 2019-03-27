/*
 * factory.cpp
 *
 *  Created on: 27 mars 2019
 *      Author: Gilles Mottiez
 */

#include <app/factory.h>

app::Factory::Factory() {
	this->theButtonController = ButtonsController::getInstance();
}

void app::Factory::initialize() {
}

void app::Factory::build() {
}

void Factory_initialize() {
}

void Factory_build() {
}
