#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct Transform_Comp_t {
    Vector2 position;
    float scale;
    float rotation;
} Transform_Comp_t;


void init_transform_comp_pool_data(ComponentPool_t *transform_comp_pool);
