#ifndef DEBUG_MACRO_H
#define DEBUG_MACRO_H


#include <qdebug.h>


	// Debug Macro for calling qDebug without an endl
	// Macro is disabled in Release mode for Optimisation

#ifdef SM_DEBUG
#define QLOG(x) qDebug() << x
#endif // SM_DEBUG

#ifdef SM_RELEASE
#define QLOG(x)
#endif // SM_RELEASE


	// Macro used for "encapsulating" code, and compiling it in debug mode only
#ifdef SM_DEBUG
#define FOR_DEBUG(y) y
#endif // SM_DEBUG

#ifdef SM_RELEASE
#define FOR_DEBUG(y)
#endif // SM_DEBUG





#endif // !DEBUG_MACRO_H