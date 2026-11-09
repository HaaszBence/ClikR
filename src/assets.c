#include "assets.h"

GameAssets Assets_Load(void) {
    GameAssets assets = { 0 };
    
    // Textúrák
    assets.cursorIdle  = LoadTexture("assets/cursor/base.png");
    assets.cursorClick = LoadTexture("assets/cursor/base_click.png");

    // Hangok
    assets.bgm      = LoadSound("assets/menu/music/music.mp3");
    assets.clickSfx = LoadSound("assets/menu/sfx/click.mp3");

    return assets;
}

void Assets_Unload(GameAssets *assets) {
    UnloadTexture(assets->cursorIdle);
    UnloadTexture(assets->cursorClick);

    UnloadSound(assets->bgm);
    UnloadSound(assets->clickSfx);
}