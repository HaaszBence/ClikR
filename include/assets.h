#ifndef ASSETS_H
#define ASSETS_H

#include <raylib.h>

typedef struct {
    // Textúrák
    Texture2D cursorIdle;
    Texture2D cursorClick;

    // Hangok
    Sound bgm;
    Sound clickSfx;
} GameAssets;

GameAssets Assets_Load(void);
void Assets_Unload(GameAssets *assets);

#endif