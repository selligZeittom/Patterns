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
#include "xf/behavior.h"

//interface::ButtonsControllerCallbackCaller,
class ButtonsController : public interface::ButtonIrq,  XFBehavior
{
public:
	//get the single instance
	static ButtonsController* getInstance();

	//from the interface ButtonIrq
	virtual void onIrq();

	//factory patterns
	void initRelations();

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

private:
	ButtonsController();
	virtual ~ButtonsController();
};

#endif /* BOARD_BUTTONSCONTROLLER_H_ */
