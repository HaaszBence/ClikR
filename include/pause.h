#ifndef PAUSE_H
#define PAUSE_H

#include <raylib.h>

typedef enum {
    PAUSE_ACTION_NONE,
    PAUSE_ACTION_RESUME,
    PAUSE_ACTION_SETTINGS,
    PAUSE_ACTION_MAIN_MENU,
    PAUSE_ACTION_EXIT
} PauseAction;

PauseAction Pause_UpdateAndDraw(Sound clickSound);

#endif
