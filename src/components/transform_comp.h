#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct Transform_Comp {
    Vector2 position;
    float scale;
    float rotation;
} Transform_Comp;


void tranform_comp_add_to_pool(uint32_t entt_id, Pool *tranform_comp_pool);
