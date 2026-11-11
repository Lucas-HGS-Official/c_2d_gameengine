#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct Sprite_Comp_t {
    int32_t width;
    int32_t heigt;
} Sprite_Comp_t;

void init_sprite_comp_pool_data(ComponentPool_t *sprite_comp_pool);
