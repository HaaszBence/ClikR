#ifndef SETTINGS_H
#define SETTINGS_H

#include "menu.h" // A Scene enum miatt

typedef struct {
    float musicVolume; // 0.0f - 1.0f (0% - 100%)
    float sfxVolume;   // 0.0f - 1.0f (0% - 100%)
    bool isFullscreen;
    Scene returnScene;
} GameSettings;

// Frissíti és kirajzolja a beállítások menüt, és azonnal alkalmazza a változtatásokat
Scene Settings_UpdateAndDraw(GameSettings *settings, Sound bgm, Sound clickSound);

#endif