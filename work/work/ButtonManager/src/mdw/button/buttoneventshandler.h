/*
 * buttoneventhandler.h
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BUTTON_BUTTONEVENTSHANDLER_H_
#define BUTTON_BUTTONEVENTSHANDLER_H_

#include "interface/buttonscontrollercallbackprovider.h"

class ButtonEventsHandler : public interface::ButtonsControllerCallbackProvider

{
public:
	static ButtonEventsHandler* getInstance();

	//factory patterns
	void initRelations();

    //method to be called
    void onBtnChanged(uint16_t btnIndex, bool isPressed);

private:
	ButtonEventsHandler();
	virtual ~ButtonEventsHandler();
};

#endif /* BUTTON_BUTTONEVENTSHANDLER_H_ */
