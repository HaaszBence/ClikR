#include "pause.h"
#include "ui.h"

PauseAction Pause_UpdateAndDraw(Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    DrawRectangle(0, 0, (int)sw, (int)sh, (Color){ PALETTE_DARK_OLIVE.r, PALETTE_DARK_OLIVE.g, PALETTE_DARK_OLIVE.b, 170 });

    float btnW = sw * 0.28f;
    float btnH = sh * 0.065f;
    float btnX = (sw - btnW) / 2.0f;
    int fontSize = (int)(btnH * 0.4f);
    int titleSize = (int)(sh * 0.045f);

    const char *title = "PAUSED";
    int titleW = MeasureText(title, titleSize);
    DrawText(title, (int)((sw - titleW) / 2.0f), (int)(sh * 0.22f), titleSize, PALETTE_GOLD);

    Rectangle continueButton = { btnX, sh * 0.34f, btnW, btnH };
    Rectangle settingsButton = { btnX, sh * 0.43f, btnW, btnH };
    Rectangle menuButton = { btnX, sh * 0.52f, btnW, btnH };
    Rectangle exitButton = { btnX, sh * 0.61f, btnW, btnH };

    if (UI_DrawButton(continueButton, "CONTINUE", fontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) {
        return PAUSE_ACTION_RESUME;
    }
    if (UI_DrawButton(settingsButton, "SETTINGS", fontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) {
        return PAUSE_ACTION_SETTINGS;
    }
    if (UI_DrawButton(menuButton, "MAIN MENU", fontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) {
        return PAUSE_ACTION_MAIN_MENU;
    }
    if (UI_DrawButton(exitButton, "SAVE AND EXIT", fontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) {
        return PAUSE_ACTION_EXIT;
    }

    return PAUSE_ACTION_NONE;
}
