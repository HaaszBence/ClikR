#include "settings.h"
#include "ui.h"

Scene Settings_UpdateAndDraw(GameSettings *settings, Sound bgm, Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    float elemW = sw * 0.30f;
    float elemH = sh * 0.05f;
    float centerX = (sw - elemW) / 2.0f;
    int titleSize = (int)(sh * 0.05f);
    int fontSize = (int)(sh * 0.025f);

    const char *title = "SETTINGS";
    int titleW = MeasureText(title, titleSize);
    DrawText(title, (int)((sw - titleW) / 2.0f), (int)(sh * 0.15f), titleSize, GOLD);

    Rectangle musicBar = { centerX, sh * 0.32f, elemW, elemH * 0.6f };
    settings->musicVolume = UI_DrawSlider(musicBar, settings->musicVolume, "Music Volume", fontSize);
    SetSoundVolume(bgm, settings->musicVolume);

    Rectangle sfxBar = { centerX, sh * 0.46f, elemW, elemH * 0.6f };
    settings->sfxVolume = UI_DrawSlider(sfxBar, settings->sfxVolume, "SFX Volume", fontSize);
    SetSoundVolume(clickSound, settings->sfxVolume);

    Rectangle fsBtn = { centerX, sh * 0.58f, elemW, elemH * 1.3f };
    const char *fsText = settings->isFullscreen ? "Fullscreen: ON" : "Fullscreen: OFF";
    if (UI_DrawButton(fsBtn, fsText, fontSize, BLUE, SKYBLUE, clickSound)) {
        settings->isFullscreen = !settings->isFullscreen;
        ToggleFullscreen();
    }

    Rectangle backBtn = { centerX, sh * 0.72f, elemW, elemH * 1.3f };
    if (UI_DrawButton(backBtn, "BACK", fontSize, DARKGRAY, GRAY, clickSound) || IsKeyPressed(KEY_ESCAPE)) {
        if (IsKeyPressed(KEY_ESCAPE)) PlaySound(clickSound);
        return settings->returnScene;
    }

    return SCENE_SETTINGS;
}