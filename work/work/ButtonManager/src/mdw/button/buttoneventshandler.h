/*
 * buttoneventhandler.h
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BUTTON_BUTTONEVENTSHANDLER_H_
#define BUTTON_BUTTONEVENTSHANDLER_H_

class ButtonEventsHandler {
public:
	static ButtonEventsHandler* getInstance();

	//factory patterns
	void initRelations();

private:
	ButtonEventsHandler();
	virtual ~ButtonEventsHandler();
};

#endif /* BUTTON_BUTTONEVENTSHANDLER_H_ */
