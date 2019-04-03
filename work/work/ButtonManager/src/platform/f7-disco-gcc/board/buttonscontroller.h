/*
 * buttonscontroller.h
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BOARD_BUTTONSCONTROLLER_H_
#define BOARD_BUTTONSCONTROLLER_H_

#include "interface/buttonirq.h"
#include "interface/buttonscontrollercallbackcaller.h"
#include "interface/buttonscontrollercallbackprovider.h"
#include "xf/behavior.h"
#include "xf/port/default/timeoutmanager-default.h"
#include "xf/port/default/resourcefactory-default.h"
#include "mdw/trace/trace.h"
#include "event/evbuttonirq.h"
#include "event/events.h"

#define NB_BUTTONS 4

class ButtonsController: public interface::ButtonIrq,
		public XFBehavior,
		public interface::ButtonsControllerCallbackCaller {
public:
	//get the single instance
	static ButtonsController* getInstance();

	//from the interface ButtonIrq
	virtual void onIrq();

	//factory pattern
	void initRelations(
			interface::ButtonsControllerCallbackProvider* callbackProvider,
			interface::ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);

	//from the interface ButtonsControllerCallbackCaller
	virtual bool registerCallback(
			interface::ButtonsControllerCallbackProvider * callbackProvider,
			interface::ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);

	//from the state machine class
	virtual XFEventStatus processEvent();

private:
	ButtonsController();
	virtual ~ButtonsController();
	void checkButtons();

	//callback to the called
	void call(uint16_t index, GPIO_PinState state);

	//store the state of the buttons
	uint8_t buttons[NB_BUTTONS];

	//states for the state machine
	typedef enum {
		STATE_INITIAL = 0,
		STATE_WAIT = 1,
		STATE_DEBOUNCE = 2
	} STATE_CONTROLLER;

	enum {
		EVENT_ID_DEBOUNCE = 0
	};

	//current state of the state machine
	STATE_CONTROLLER currentState;

	//event to be pushed from the isr
	evButtonIrq* evOnIrq;

	//called object and method
	interface::ButtonsControllerCallbackProvider* called;
	interface::ButtonsControllerCallbackProvider::CallbackMethod cbMethodPtr;
};

#endif /* BOARD_BUTTONSCONTROLLER_H_ */
