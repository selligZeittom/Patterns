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

class ButtonsController : interface::ButtonIrq, interface::ButtonsControllerCallbackCaller
{
public:
	ButtonsController();
	virtual ~ButtonsController();

	//from the interface ButtonIrq
	void onIrq();

	//from the interface ButtonsControllerCallbackCaller
	bool registerCallback(ButtonsControllerCallbackProvider * callbackProvider,
	                                  ButtonsControllerCallbackProvider::CallbackMethod callbackMethod);

	enum GPIO{
		BUTTON0_Pin = 0,
		BUTTON1_Pin = 0,
		BUTTON2_Pin = 0,
		BUTTON3_Pin = 0
	};
};

#endif /* BOARD_BUTTONSCONTROLLER_H_ */
