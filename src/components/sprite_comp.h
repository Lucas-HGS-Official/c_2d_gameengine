#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"
#include "assets_manager.h"


typedef struct Sprite_Comp_t {
    Color color;
    Rectangle rec;
    Vector2 origin;
    uint32_t z_index;
    TEXTURES texture_id;
} Sprite_Comp_t;

void init_sprite_comp_pool_data(ComponentPool_t *sprite_comp_pool);
