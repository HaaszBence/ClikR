#include "menu.h"
#include "ui.h"

Scene Menu_UpdateAndDraw(Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    float btnW = sw * 0.25f;
    float btnH = sh * 0.067f;
    float btnX = (sw - btnW) / 2.0f;

    int titleSize = (int)(sh * 0.05f);
    int btnFontSize = (int)(btnH * 0.4f);

    const char *title = "ClikR";
    int titleW = MeasureText(title, titleSize);
    DrawText(title, (int)((sw - titleW) / 2.0f), (int)(sh * 0.22f), titleSize, GOLD);

    Rectangle startBtn    = { btnX, sh * 0.37f, btnW, btnH };
    Rectangle settingsBtn = { btnX, sh * 0.47f, btnW, btnH };
    Rectangle exitBtn     = { btnX, sh * 0.57f, btnW, btnH };

    if (UI_DrawButton(startBtn, "START", btnFontSize, BLUE, SKYBLUE, clickSound)) return SCENE_GAME;
    if (UI_DrawButton(settingsBtn, "SETTINGS", btnFontSize, BLUE, SKYBLUE, clickSound)) return SCENE_SETTINGS;
    if (UI_DrawButton(exitBtn, "EXIT", btnFontSize, BLUE, SKYBLUE, clickSound)) return SCENE_EXIT;

    return SCENE_MENU;
}