#include <raylib.h>
#include <time.h>
#include "menu.h"
#include "settings.h"
#include "game.h"
#include "assets.h"
#include "ui.h"

int main(void) {
    GameSettings settings = Settings_Load("data/config.txt");

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(settings.windowWidth, settings.windowHeight, "ClikR");
    if (settings.isFullscreen) ToggleFullscreen();

    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(settings.targetFps);
    SetRandomSeed((unsigned int)time(NULL));
    HideCursor();

    GameAssets assets = Assets_Load();
    SetSoundVolume(assets.bgm, settings.musicVolume);
    SetSoundVolume(assets.clickSfx, settings.sfxVolume);
    PlaySound(assets.bgm);

    Scene currentScene = SCENE_MENU;

    while (!WindowShouldClose() && currentScene != SCENE_EXIT) {
        if (!IsSoundPlaying(assets.bgm)) PlaySound(assets.bgm);

        BeginDrawing();
        ClearBackground(PALETTE_DARK_OLIVE);

        switch (currentScene) {
            case SCENE_MENU:
                currentScene = Menu_UpdateAndDraw(assets.clickSfx);
                if (currentScene == SCENE_SETTINGS) settings.returnScene = SCENE_MENU;
                break;
            case SCENE_SETTINGS:
                currentScene = Settings_UpdateAndDraw(&settings, &assets);
                break;
            case SCENE_GAME:
                currentScene = Game_UpdateAndDraw(&settings, assets.clickSfx);
                break;
            default:
                break;
        }

        UI_DrawCursor(&assets);
        EndDrawing();
    }

    Assets_Unload(&assets);
    ShowCursor();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}