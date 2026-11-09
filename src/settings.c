#include "settings.h"
#include "ui.h"
#include <stdio.h>

GameSettings Settings_Load(const char *filepath) {
    GameSettings s = { 1200, 900, 240, 0.5f, 0.8f, false, SCENE_MENU };

    FILE *f = fopen(filepath, "r");
    if (!f) return s;

    char line[128];
    int fsInt = 0;
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "width=%d", &s.windowWidth) == 1) continue;
        if (sscanf(line, "height=%d", &s.windowHeight) == 1) continue;
        if (sscanf(line, "fps=%d", &s.targetFps) == 1) continue;
        if (sscanf(line, "music=%f", &s.musicVolume) == 1) continue;
        if (sscanf(line, "sfx=%f", &s.sfxVolume) == 1) continue;
        if (sscanf(line, "fullscreen=%d", &fsInt) == 1) {
            s.isFullscreen = (fsInt != 0);
        }
    }

    fclose(f);
    return s;
}

void Settings_Save(const char *filepath, const GameSettings *s) {
    FILE *f = fopen(filepath, "w");
    if (!f) return;

    fprintf(f, "width=%d\n", s->windowWidth);
    fprintf(f, "height=%d\n", s->windowHeight);
    fprintf(f, "fps=%d\n", s->targetFps);
    fprintf(f, "music=%.2f\n", s->musicVolume);
    fprintf(f, "sfx=%.2f\n", s->sfxVolume);
    fprintf(f, "fullscreen=%d\n", s->isFullscreen ? 1 : 0);

    fclose(f);
}

Scene Settings_UpdateAndDraw(GameSettings *settings, GameAssets *assets) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    float elemW = sw * 0.30f;
    float elemH = sh * 0.05f;
    float centerX = (sw - elemW) / 2.0f;
    int titleSize = (int)(sh * 0.05f);
    int fontSize = (int)(sh * 0.025f);

    const char *title = "SETTINGS";
    int titleW = MeasureText(title, titleSize);
    DrawText(title, (int)((sw - titleW) / 2.0f), (int)(sh * 0.15f), titleSize, PALETTE_GOLD);

    Rectangle musicBar = { centerX, sh * 0.32f, elemW, elemH * 0.6f };
    settings->musicVolume = UI_DrawSlider(musicBar, settings->musicVolume, "Music Volume", fontSize);
    SetSoundVolume(assets->bgm, settings->musicVolume);

    Rectangle sfxBar = { centerX, sh * 0.46f, elemW, elemH * 0.6f };
    settings->sfxVolume = UI_DrawSlider(sfxBar, settings->sfxVolume, "SFX Volume", fontSize);
    SetSoundVolume(assets->clickSfx, settings->sfxVolume);

    Rectangle fsBtn = { centerX, sh * 0.58f, elemW, elemH * 1.3f };
    const char *fsText = settings->isFullscreen ? "Fullscreen: ON" : "Fullscreen: OFF";
    if (UI_DrawButton(fsBtn, fsText, fontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, assets->clickSfx)) {
        settings->isFullscreen = !settings->isFullscreen;
        ToggleFullscreen();
    }

    Rectangle backBtn = { centerX, sh * 0.72f, elemW, elemH * 1.3f };
    if (UI_DrawButton(backBtn, "BACK", fontSize, PALETTE_MOSS_GREEN, PALETTE_LEMON, assets->clickSfx) || IsKeyPressed(KEY_ESCAPE)) {
        if (IsKeyPressed(KEY_ESCAPE)) PlaySound(assets->clickSfx);
        Settings_Save("data/config.txt", settings); // Visszalépéskor elmenti a változásokat
        return settings->returnScene;
    }

    return SCENE_SETTINGS;
}