#ifndef FACTORY_H
#define FACTORY_H

//
// What is seen only by the C++ compiler
//
#ifdef __cplusplus

#include "buttoneventslogger.h"
#include "mdw/button/buttoneventshandler.h"
#include "board/buttonscontroller.h"

namespace app {

class Factory {
public:
	Factory();

	static void initialize();           ///< Initializes the factory
	static void build();       ///< Creates components and initializes relations

protected:
	// TODO: Add static attributes here
	static ButtonEventsLogger* theButtonEventsLogger;
	static ButtonEventsHandler* theButtonEventsHandler; //it is a singleton
	static ButtonsController* theButtonController; //it is a singleton
};

} /* namespace app */
#endif // __cplusplus

//
// What is seen by the C and C++ compiler
//
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void Factory_initialize();
void Factory_build();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // FACTORY_H
