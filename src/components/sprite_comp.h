#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"
#include "../game/game.h"


typedef struct Sprite_Comp_t {
    Color color;
    Rectangle rec;
    Vector2 origin;
    uint32_t z_index;
    TEXTURES_E texture_id;
} Sprite_Comp_t;

ComponentPool_t init_sprite_comp_pool_data(void);
