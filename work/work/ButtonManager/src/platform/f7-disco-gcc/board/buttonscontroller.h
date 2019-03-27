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

class ButtonsController : public interface::ButtonIrq, interface::ButtonsControllerCallbackCaller, XFBehavior
{
public:
	ButtonsController();
	virtual ~ButtonsController();

	//from the interface ButtonIrq
	virtual void onIrq();

	//from the interface ButtonsControllerCallbackCaller
	/*
	virtual bool registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
	                                  ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);
	*/

	//from the state machine class
	virtual XFEventStatus processEvent();

	enum GPIO{
		BUTTON0_Pin = 0,
		BUTTON1_Pin = 0,
		BUTTON2_Pin = 0,
		BUTTON3_Pin = 0
	};
};

#endif /* BOARD_BUTTONSCONTROLLER_H_ */
