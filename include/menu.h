#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include <stdbool.h>

typedef enum {
    SCENE_MENU,
    SCENE_GAME,
    SCENE_SETTINGS,
    SCENE_EXIT
} Scene;

// Frissíti és kirajzolja a menü jelenetet, visszaadja a következő jelenetet
Scene Menu_UpdateAndDraw(Sound clickSound);

#endif