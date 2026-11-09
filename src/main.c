#include <raylib.h>
#include "menu.h"
#include "settings.h"
#include "game.h"
#include "assets.h"

int main(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1200, 900, "ClikR");

    SetExitKey(KEY_NULL);
    
    InitAudioDevice();
    SetTargetFPS(240);

    HideCursor();

    Scene currentScene = SCENE_MENU;

    // default settings
    GameSettings settings = { 0.5f, 0.8f, false };
    
    // load assets
    GameAssets assets = Assets_Load();
    SetSoundVolume(assets.bgm, settings.musicVolume);
    SetSoundVolume(assets.clickSfx, settings.sfxVolume);
    PlaySound(assets.bgm);

    while (!WindowShouldClose() && currentScene != SCENE_EXIT) {
        if (!IsSoundPlaying(assets.bgm)) {
            PlaySound(assets.bgm);
        }

        BeginDrawing();
        ClearBackground((Color){ 30, 30, 45, 255 });

        if (currentScene == SCENE_MENU) {
            currentScene = Menu_UpdateAndDraw(assets.clickSfx);
            if (currentScene == SCENE_SETTINGS) {
                settings.returnScene = SCENE_MENU; // Főmenüből nyitottuk meg
            }
        }
        else if (currentScene == SCENE_SETTINGS) {
            currentScene = Settings_UpdateAndDraw(&settings, assets.bgm, assets.clickSfx);
        }
        else if (currentScene == SCENE_GAME) {
            currentScene = Game_UpdateAndDraw(&settings, assets.clickSfx);
        }

        Vector2 mouse = GetMousePosition();
        float size = GetScreenHeight() * 0.045f;
        Texture2D activeTex = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? assets.cursorClick : assets.cursorIdle;

        Rectangle src  = { 0.0f, 0.0f, (float)activeTex.width, (float)activeTex.height };
        Rectangle dest = { mouse.x, mouse.y, size, size };
        DrawTexturePro(activeTex, src, dest, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);

        EndDrawing();
    }

    Assets_Unload(&assets);
    ShowCursor();

    CloseAudioDevice();

    CloseWindow();

    return 0;
}