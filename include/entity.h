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
} GameEntity;

extern const GameEntityTemplate GAME_ENTITY_BASIC_TEMPLATE;

GameEntity GameEntity_Spawn(const GameEntityTemplate *template);
void GameEntity_Draw(const GameEntity *entity, Rectangle bounds);

#endif
