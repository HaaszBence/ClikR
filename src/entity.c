#include "entity.h"
#include "ui.h"

static const float ENTITY_SIZE_RATIO = 0.06f;
static const float ENTITY_HORIZONTAL_MARGIN_RATIO = 0.07f;
static const float ENTITY_TOP_MARGIN_RATIO = 0.18f;
static const float ENTITY_BOTTOM_MARGIN_RATIO = 0.08f;

const GameEntityTemplate GAME_ENTITY_BASIC_TEMPLATE = {
    .name = "Basic",
    .maxHp = 10,
    .creditReward = 1
};

GameEntity GameEntity_Create(const GameEntityTemplate *template) {
    return (GameEntity){
        .template = template,
        .currentHp = 0,
        .completed = false,
        .spawnPosition = {
            (float)GetRandomValue(0, 10000) / 10000.0f,
            (float)GetRandomValue(0, 10000) / 10000.0f
        }
    };
}

bool GameEntity_ApplyClick(GameEntity *entity, unsigned int clickPower) {
    if (entity->completed || clickPower == 0) return false;

    unsigned int remainingHp = entity->template->maxHp - entity->currentHp;
    if (clickPower >= remainingHp) {
        entity->currentHp = entity->template->maxHp;
        entity->completed = true;
        return true;
    }

    entity->currentHp += clickPower;
    return false;
}

static Rectangle GameEntity_GetBounds(const GameEntity *entity) {
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();
    float entitySize = (screenWidth < screenHeight ? screenWidth : screenHeight) * ENTITY_SIZE_RATIO;
    float horizontalMargin = screenWidth * ENTITY_HORIZONTAL_MARGIN_RATIO;
    float minX = horizontalMargin;
    float maxX = screenWidth - horizontalMargin - entitySize;
    float minY = screenHeight * ENTITY_TOP_MARGIN_RATIO;
    float maxY = screenHeight - screenHeight * ENTITY_BOTTOM_MARGIN_RATIO - entitySize;

    if (maxX < minX) maxX = minX;
    if (maxY < minY) maxY = minY;

    return (Rectangle){
        minX + (maxX - minX) * entity->spawnPosition.x,
        minY + (maxY - minY) * entity->spawnPosition.y,
        entitySize,
        entitySize
    };
}

bool GameEntity_IsClicked(const GameEntity *entity) {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
           CheckCollisionPointRec(GetMousePosition(), GameEntity_GetBounds(entity));
}

void GameEntity_Draw(const GameEntity *entity) {
    Rectangle bounds = GameEntity_GetBounds(entity);
    DrawRectangleRec(bounds, PALETTE_MOSS_GREEN);
    DrawRectangleLinesEx(bounds, 3.0f, PALETTE_LEMON);

    float barHeight = bounds.height * 0.12f;
    float barWidth = bounds.width * 1.5f;
    float barGap = bounds.height * 0.12f;
    Rectangle hpBar = {
        bounds.x + (bounds.width - barWidth) / 2.0f,
        bounds.y - barGap - barHeight,
        barWidth,
        barHeight
    };
    DrawRectangleRec(hpBar, PALETTE_DARK_OLIVE);

    float hpRatio = entity->template->maxHp > 0
        ? (float)entity->currentHp / (float)entity->template->maxHp
        : 0.0f;
    if (hpRatio > 1.0f) hpRatio = 1.0f;

    Rectangle hpFill = { hpBar.x, hpBar.y, hpBar.width * hpRatio, hpBar.height };
    DrawRectangleRec(hpFill, PALETTE_GOLD);
    DrawRectangleLinesEx(hpBar, 2.0f, PALETTE_CHALK);
}
