#include "game.h"
#include "ui.h"

static bool isPaused = false;

Scene Game_UpdateAndDraw(GameSettings *settings, Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    if (IsKeyPressed(KEY_ESCAPE)) {
        PlaySound(clickSound);
        isPaused = !isPaused;
    }

    DrawText("Game (ESC to pause)", (int)(sw * 0.04f), (int)(sh * 0.05f), (int)(sh * 0.03f), WHITE);

    if (isPaused) {
        DrawRectangle(0, 0, (int)sw, (int)sh, (Color){ 0, 0, 0, 170 });

        float btnW = sw * 0.28f;
        float btnH = sh * 0.065f;
        float btnX = (sw - btnW) / 2.0f;
        int fontSize = (int)(btnH * 0.4f);
        int titleSize = (int)(sh * 0.045f);

        const char *title = "PAUSED";
        int titleW = MeasureText(title, titleSize);
        DrawText(title, (int)((sw - titleW) / 2.0f), (int)(sh * 0.22f), titleSize, GOLD);

        Rectangle contBtn = { btnX, sh * 0.34f, btnW, btnH };
        Rectangle settBtn = { btnX, sh * 0.43f, btnW, btnH };
        Rectangle menuBtn = { btnX, sh * 0.52f, btnW, btnH };
        Rectangle saveBtn = { btnX, sh * 0.61f, btnW, btnH };

        if (UI_DrawButton(contBtn, "CONTINUE", fontSize, BLUE, SKYBLUE, clickSound)) isPaused = false;
        if (UI_DrawButton(settBtn, "SETTINGS", fontSize, BLUE, SKYBLUE, clickSound)) {
            settings->returnScene = SCENE_GAME;
            return SCENE_SETTINGS;
        }
        if (UI_DrawButton(menuBtn, "MAIN MENU", fontSize, BLUE, SKYBLUE, clickSound)) {
            isPaused = false;
            return SCENE_MENU;
        }
        if (UI_DrawButton(saveBtn, "SAVE AND EXIT", fontSize, BLUE, SKYBLUE, clickSound)) {
            isPaused = false;
            return SCENE_EXIT;
        }
    }

    return SCENE_GAME;
}