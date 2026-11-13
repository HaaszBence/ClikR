#ifndef ENTITY_H
#define ENTITY_H

#include <raylib.h>
#include <stdbool.h>

typedef struct {
    const char *name;
    unsigned int maxHp;
    unsigned int creditReward;
} GameEntityTemplate;

typedef struct {
    const GameEntityTemplate *template;
    unsigned int currentHp;
    bool completed;
    Vector2 spawnPosition;
} GameEntity;

extern const GameEntityTemplate GAME_ENTITY_BASIC_TEMPLATE;

GameEntity GameEntity_Create(const GameEntityTemplate *template);
bool GameEntity_ApplyClick(GameEntity *entity, unsigned int clickPower);
bool GameEntity_IsClicked(const GameEntity *entity);
void GameEntity_Draw(const GameEntity *entity);

#endif
