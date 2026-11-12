#include "menu.h"
#include "ui.h"
#include <math.h>
#include <stddef.h>

typedef struct {
    const char *text;
    float x;
    float y;
    float driftSpeed;
    float phase;
    float sway;
} MenuSymbol;

static const MenuSymbol symbols[] = {
    { "Q.E.D.",       0.08f, 0.88f, 0.020f, 0.3f, 0.014f },
    { "lim",          0.22f, 0.70f, 0.016f, 1.1f, 0.012f },
    { "dx",           0.38f, 0.93f, 0.024f, 2.0f, 0.016f },
    { "f(x)",         0.54f, 0.76f, 0.018f, 2.8f, 0.012f },
    { "E!",           0.72f, 0.90f, 0.022f, 3.6f, 0.014f },
    { "V",            0.91f, 0.66f, 0.015f, 4.4f, 0.012f },
    { "n -> oo",      0.14f, 0.48f, 0.019f, 5.1f, 0.015f },
    { "O(n log n)",   0.82f, 0.52f, 0.017f, 5.8f, 0.014f },
    { "dx",           0.31f, 0.34f, 0.021f, 0.7f, 0.013f },
    { "Q.E.D.",       0.65f, 0.42f, 0.016f, 1.8f, 0.015f },
    { "f(x)",         0.95f, 0.30f, 0.023f, 2.5f, 0.013f },
    { "lim",          0.48f, 0.22f, 0.018f, 3.3f, 0.016f },
    { "O(n log n)",   0.05f, 0.15f, 0.020f, 4.1f, 0.012f },
    { "V",            0.77f, 0.12f, 0.015f, 4.9f, 0.014f },
    { "E!",           0.43f, 0.55f, 0.022f, 5.6f, 0.013f },
    { "n -> oo",      0.88f, 0.82f, 0.019f, 0.1f, 0.016f }
};

static void DrawMenuBackdrop(float screenWidth, float screenHeight) {

    // Draw a subtle grid and floating symbols in the background
    Color gridColor = { PALETTE_CHALK.r, PALETTE_CHALK.g, PALETTE_CHALK.b, 18 };
    Color symbolColor = { PALETTE_CHALK.r, PALETTE_CHALK.g, PALETTE_CHALK.b, 28 };
    const int gridSpacing = 48;

    for (int x = 0; x < (int)screenWidth; x += gridSpacing) {
        DrawLine(x, 0, x, (int)screenHeight, gridColor);
    }
    for (int y = 0; y < (int)screenHeight; y += gridSpacing) {
        DrawLine(0, y, (int)screenWidth, y, gridColor);
    }

    float time = (float)GetTime();
    int symbolFontSize = (int)(screenHeight * 0.018f);
    if (symbolFontSize < 12) symbolFontSize = 12;

    for (size_t i = 0; i < sizeof(symbols) / sizeof(symbols[0]); i++) {
        const MenuSymbol *symbol = &symbols[i];
        float y = fmodf(symbol->y - time * symbol->driftSpeed, 1.0f);
        if (y < 0.0f) y += 1.0f;
        float x = symbol->x + sinf(time * 0.7f + symbol->phase) * symbol->sway;
        DrawText(symbol->text, (int)(x * screenWidth), (int)(y * screenHeight), symbolFontSize, symbolColor);
    }
}

Scene Menu_UpdateAndDraw(Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();
    DrawMenuBackdrop(sw, sh);

    float btnW = sw * 0.25f;
    float btnH = sh * 0.067f;
    float btnX = (sw - btnW) / 2.0f;

    int titleSize = (int)(sh * 0.07f);
    int btnFontSize = (int)(btnH * 0.4f);

    const char *title = "ClikR";
    int titleW = MeasureText(title, titleSize);
    float titleY = sh * 0.16f + sinf((float)GetTime() * 2.5f) * 6.0f;
    DrawText(title, (int)((sw - titleW) / 2.0f) + 3, (int)titleY + 4, titleSize, (Color){ 32, 46, 14, 170 });
    DrawText(title, (int)((sw - titleW) / 2.0f), (int)titleY, titleSize, PALETTE_GOLD);

    const char *subtitle = "Learn ";
    int subtitleSize = (int)(sh * 0.025f);
    int subtitleW = MeasureText(subtitle, subtitleSize);
    DrawText(subtitle, (int)((sw - subtitleW) / 2.0f), (int)(sh * 0.27f), subtitleSize, PALETTE_LEMON);

    Rectangle startBtn    = { btnX, sh * 0.38f, btnW, btnH };
    Rectangle settingsBtn = { btnX, sh * 0.49f, btnW, btnH };
    Rectangle exitBtn     = { btnX, sh * 0.60f, btnW, btnH };

    if (UI_DrawButton(startBtn, "START", btnFontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) return SCENE_GAME;
    if (UI_DrawButton(settingsBtn, "SETTINGS", btnFontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) return SCENE_SETTINGS;
    if (UI_DrawButton(exitBtn, "EXIT", btnFontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, clickSound)) return SCENE_EXIT;

    DrawText("v0.1 Alpha", 14, (int)sh - 28, (int)(sh * 0.02f), PALETTE_CHALK);

    return SCENE_MENU;
}