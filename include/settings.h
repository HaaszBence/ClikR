#ifndef SETTINGS_H
#define SETTINGS_H

#include <raylib.h>
#include <stdbool.h>
#include "menu.h"
#include "assets.h"

typedef struct {
    int windowWidth;
    int windowHeight;
    int targetFps;
    float musicVolume;
    float sfxVolume;
    bool isFullscreen;
    Scene returnScene;
} GameSettings;

// Betölti a beállításokat a fájlból (ha nincs fájl, alapértékeket ad)
GameSettings Settings_Load(const char *filepath);

Scene Settings_UpdateAndDraw(GameSettings *settings, GameAssets *assets);

#endif