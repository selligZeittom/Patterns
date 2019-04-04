/*
 * button_fsm.h
 *
 *  Created on: 3 avr. 2019
 *      Author: Gilles Mottiez
 */

#ifndef BUTTON_BUTTON_FSM_H_
#define BUTTON_BUTTON_FSM_H_

#include "xf/behavior.h"
#include "xf/port/default/timeoutmanager-default.h"
#include "xf/port/default/resourcefactory-default.h"
#include "mdw/trace/trace.h"
#include "event/evbuttonirq.h"
#include "event/events.h"
#include "event/evbuttonpressed.h"
#include "event/evbuttonreleased.h"

class ButtonEventsHandler;

class ButtonFSM: public XFBehavior {
public:
	ButtonFSM();
	ButtonFSM(int id, ButtonEventsHandler* parent);
	virtual ~ButtonFSM();

	//from the state machine class
	virtual XFEventStatus processEvent();

	//called by theHandler
	void onBtnChanged(bool isPressed);

	//getter and setter for idFsm and theHandler
	void setId(int id);
	void setHandler(ButtonEventsHandler* parent);
	int getId() const;

private:
	//states for the state machine
	typedef enum {
		STATE_INITIAL = 0,
		STATE_WAIT,
		STATE_BTN_PRESSED,
		STATE_SHORT_PRESS,
		STATE_LONG_PRESS
	} STATE_BTN;

	enum {
		EVENT_ID_LONG = 0
		};

	//current state of the state machine
	STATE_BTN currentState;

	//each button has one of this fsm, with an unique id
	int idFsm;

	//connection to the container of the fsm
	ButtonEventsHandler* theHandler;
};

#endif /* BUTTON_BUTTON_FSM_H_ */
