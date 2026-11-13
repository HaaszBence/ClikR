#include "game.h"
#include "entity.h"
#include "pause.h"
#include "ui.h"
#include <limits.h>

static bool isPaused = false;
static unsigned int credits = 0;
static const unsigned int clickPower = 1;
static GameEntity activeEntity;
static bool entitySpawned = false;

static void SpawnActiveEntity(void) {
    activeEntity = GameEntity_Create(&GAME_ENTITY_BASIC_TEMPLATE);
    entitySpawned = true;
}

Scene Game_UpdateAndDraw(GameSettings *settings, Sound clickSound) {
    float sw = (float)GetScreenWidth();
    float sh = (float)GetScreenHeight();

    if (!entitySpawned) {
        SpawnActiveEntity();
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        PlaySound(clickSound);
        isPaused = !isPaused;
    }

    DrawText("Game (ESC to pause)", (int)(sw * 0.04f), (int)(sh * 0.05f), (int)(sh * 0.03f), PALETTE_GOLD);

    int creditsFontSize = (int)(sh * 0.03f);
    const char *creditsText = TextFormat("CREDITS: %u", credits);
    int creditsTextWidth = MeasureText(creditsText, creditsFontSize);
    DrawText(creditsText, (int)sw - (int)(sw * 0.04f) - creditsTextWidth,
             (int)(sh * 0.05f), creditsFontSize, PALETTE_GOLD);

    if (!isPaused && GameEntity_IsClicked(&activeEntity)) {
        PlaySound(clickSound);
        if (GameEntity_ApplyClick(&activeEntity, clickPower)) {
            unsigned int reward = activeEntity.template->creditReward;
            credits = reward > UINT_MAX - credits ? UINT_MAX : credits + reward;
            SpawnActiveEntity();
        }
    }

    GameEntity_Draw(&activeEntity);

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