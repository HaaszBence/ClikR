#ifndef GAME_H
#define GAME_H

#include "menu.h"
#include "settings.h"

// Frissíti és kirajzolja a játékot (és a szünet almenüt)
Scene Game_UpdateAndDraw(GameSettings *settings, Sound clickSound);

#endif