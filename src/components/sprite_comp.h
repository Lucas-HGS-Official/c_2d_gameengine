#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"
#include "assets_manager.h"


typedef struct Sprite_Comp_t {
    TEXTURES texture_id;
    Rectangle rec;
} Sprite_Comp_t;

void init_sprite_comp_pool_data(ComponentPool_t *sprite_comp_pool);
