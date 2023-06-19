/* --------------------------------------------------------------------------------------
* Author : Gabriel Wulveryck.
* Year : 2023
* for any information, please contact : wulveryck.gabriel@gmail.com
*
* This file is a part of the SubMerge project.
*
* SubMerge is a free software, and is published under the terms of the GNU General Public Licence, version 3.
* You can redistribute it and/or modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3 of the License,
* or (at your option) any later version.
* You should have recived a copy of the licence with the project.
*
* SubMerge is distributed as a contribution to the open-source and free software community,
* in the hope it'll be usefull.
* SubMerge is distributed without ANY WARRANTY, without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* See the GNU General Public License for more details.
*
*-------------------------------------------------------------------------------------- */

/*
	Usefull macros for debugging, and keeping code clean beetween debug and release configuration.
*/

#ifndef DEBUG_MACRO_H
#define DEBUG_MACRO_H


#include <qdebug.h>

	// Debug Macro for calling qDebug without an endl
	// Macro is disabled in Release mode for Optimisation
#ifdef SUBM_DEBUG
#define QLOG(x) qDebug() << x
#endif // SM_DEBUG

#ifdef SUBM_RELEASE
#define QLOG(x)
#endif // SM_RELEASE


	// Macro used for "encapsulating" code, and compiling it in debug mode only
#ifdef SUBM_DEBUG
#define FOR_DEBUG(y) y
#endif // SM_DEBUG

#ifdef SUBM_RELEASE
#define FOR_DEBUG(y)
#endif // SM_DEBUG





#endif // !DEBUG_MACRO_H