#include "assets.h"

GameAssets Assets_Load(void) {
    GameAssets assets = { 0 };

    // Textúrák
    assets.cursorIdle  = LoadTexture("assets/ui/cursor/base.png");
    SetTextureFilter(assets.cursorIdle, TEXTURE_FILTER_BILINEAR);
    assets.cursorClick = LoadTexture("assets/ui/cursor/base_click.png");
    SetTextureFilter(assets.cursorClick, TEXTURE_FILTER_BILINEAR);

    // Hangok
    assets.bgm      = LoadSound("assets/music/music.mp3");
    assets.clickSfx = LoadSound("assets/sfx/click.mp3");

    return assets;
}

void Assets_Unload(GameAssets *assets) {
    UnloadTexture(assets->cursorIdle);
    UnloadTexture(assets->cursorClick);

    UnloadSound(assets->bgm);
    UnloadSound(assets->clickSfx);
}