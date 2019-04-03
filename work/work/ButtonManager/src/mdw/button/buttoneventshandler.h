/*
 * buttoneventhandler.h
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BUTTON_BUTTONEVENTSHANDLER_H_
#define BUTTON_BUTTONEVENTSHANDLER_H_

#include "interface/buttonscontrollercallbackprovider.h"
#include "interface/buttoneventshandlersubject.h"
#include "interface/buttoneventshandlerobserver.h"
#include "mdw/button/button_fsm.h"

#define NB_BUTTONS 4

class ButtonEventsHandler: public interface::ButtonsControllerCallbackProvider,
		public interface::ButtonEventsHandlerSubject

{
public:
	static ButtonEventsHandler* getInstance();

	//factory patterns
	void initRelations();

	//method to be called
	void onBtnChanged(uint16_t btnIndex, bool isPressed);

	//used from the factory to start the 4 fsm
	void startStateMachines();

	//from interface subject
	bool subscribe(interface::ButtonEventsHandlerObserver * observer);
	void unsubscribe(interface::ButtonEventsHandlerObserver * observer);

	void notifyButtonShortPressed(ButtonIndex buttonIndex);
	void notifyButtonLongPressed(ButtonIndex buttonIndex);

private:
	ButtonEventsHandler();
	virtual ~ButtonEventsHandler();

	ButtonFSM fsmButtons[NB_BUTTONS];
};

#endif /* BUTTON_BUTTONEVENTSHANDLER_H_ */
