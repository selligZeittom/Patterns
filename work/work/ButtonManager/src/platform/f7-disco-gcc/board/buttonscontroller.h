/*
 * buttonscontroller.h
 *
 *  Created on: 26 mars 2019
 *      Author: Gilles Mottiez
 */

#ifndef BOARD_BUTTONSCONTROLLER_H_
#define BOARD_BUTTONSCONTROLLER_H_

class ButtonsController {
public:
	ButtonsController();
	virtual ~ButtonsController();

	struct GPIO_Pins {
		uint16_t BUTTON0_Pin = 0x00,
		uint16_t BUTTON1_Pin = 0x00,
		uint16_t BUTTON2_Pin = 0x00,
		uint16_t BUTTON3_Pin = 0x00
	};
};

#endif /* BOARD_BUTTONSCONTROLLER_H_ */
