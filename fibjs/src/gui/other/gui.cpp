/*
 * gui.cpp
 *
 *  Created on: Sep 23, 2016
 *      Author: lion
 */

#ifdef FIBJS_DISABLE_GUI

#include "object.h"

namespace fibjs {

void init_gui()
{
}

void run_gui()
{
    exlib::OSThread th;

    th.bindCurrent();
    th.suspend();
}

void putGuiPool(AsyncEvent* ac)
{
}
}

#endif // FIBJS_DISABLE_GUI
