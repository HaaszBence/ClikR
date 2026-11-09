#include <raylib.h>
#include "menu.h"
#include "settings.h"
#include "game.h"

int main(void) {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1200, 900, "ClikR");

    SetExitKey(KEY_NULL);
    
    InitAudioDevice();
    SetTargetFPS(240);

    Sound bgm = LoadSound("assets/menu/music/music.mp3");
    Sound clickSfx = LoadSound("assets/menu/sfx/click.mp3");

    // default settings
    GameSettings settings = { 0.5f, 0.8f, false };
    SetSoundVolume(bgm, settings.musicVolume);
    SetSoundVolume(clickSfx, settings.sfxVolume);
    PlaySound(bgm);

    Scene currentScene = SCENE_MENU;

    while (!WindowShouldClose() && currentScene != SCENE_EXIT) {
        if (!IsSoundPlaying(bgm)) {
            PlaySound(bgm);
        }

        BeginDrawing();
        ClearBackground((Color){ 30, 30, 45, 255 });

        if (currentScene == SCENE_MENU) {
            currentScene = Menu_UpdateAndDraw(clickSfx);
            if (currentScene == SCENE_SETTINGS) {
                settings.returnScene = SCENE_MENU; // Főmenüből nyitottuk meg
            }
        }
        else if (currentScene == SCENE_SETTINGS) {
            currentScene = Settings_UpdateAndDraw(&settings, bgm, clickSfx);
        }
        else if (currentScene == SCENE_GAME) {
            currentScene = Game_UpdateAndDraw(&settings, clickSfx);
        }

        EndDrawing();
    }

    UnloadSound(clickSfx);
    UnloadSound(bgm);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}