#include "game.h"
#include "pause.h"
#include "ui.h"

static bool isPaused = false;

Scene Game_UpdateAndDraw(GameSettings *settings, Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    if (IsKeyPressed(KEY_ESCAPE)) {
        PlaySound(clickSound);
        isPaused = !isPaused;
    }

    DrawText("Game (ESC to pause)", (int)(sw * 0.04f), (int)(sh * 0.05f), (int)(sh * 0.03f), PALETTE_GOLD);

    if (isPaused) {
        switch (Pause_UpdateAndDraw(clickSound)) {
            case PAUSE_ACTION_RESUME:
                isPaused = false;
                break;
            case PAUSE_ACTION_SETTINGS:
                settings->returnScene = SCENE_GAME;
                return SCENE_SETTINGS;
            case PAUSE_ACTION_MAIN_MENU:
                isPaused = false;
                return SCENE_MENU;
            case PAUSE_ACTION_EXIT:
                isPaused = false;
                return SCENE_EXIT;
            case PAUSE_ACTION_NONE:
                break;
        }
    }

    return SCENE_GAME;
}