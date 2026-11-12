#include "entity.h"
#include "ui.h"

const GameEntityTemplate GAME_ENTITY_BASIC_TEMPLATE = {
    .name = "Basic",
    .maxHp = 10,
    .creditReward = 1
};

GameEntity GameEntity_Spawn(const GameEntityTemplate *template) {
    return (GameEntity){
        .template = template,
        .currentHp = template->maxHp,
        .completed = false
    };
}

void GameEntity_Draw(const GameEntity *entity, Rectangle bounds) {
    DrawRectangleRec(bounds, PALETTE_MOSS_GREEN);
    DrawRectangleLinesEx(bounds, 3.0f, PALETTE_LEMON);

    int nameFontSize = (int)(bounds.height * 0.145f);
    int nameWidth = MeasureText(entity->template->name, nameFontSize);
    DrawText(entity->template->name,
             (int)(bounds.x + (bounds.width - nameWidth) / 2.0f),
             (int)(bounds.y + bounds.height * 0.2f),
             nameFontSize, PALETTE_CHALK);

    int hpFontSize = (int)(bounds.height * 0.105f);
    const char *hpText = TextFormat("HP: %u / %u", entity->currentHp, entity->template->maxHp);
    int hpTextWidth = MeasureText(hpText, hpFontSize);
    DrawText(hpText,
             (int)(bounds.x + (bounds.width - hpTextWidth) / 2.0f),
             (int)(bounds.y + bounds.height * 0.55f),
             hpFontSize, PALETTE_CHALK);

    Rectangle hpBar = {
        bounds.x + bounds.width * 0.12f,
        bounds.y + bounds.height * 0.75f,
        bounds.width * 0.76f,
        bounds.height * 0.105f
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
