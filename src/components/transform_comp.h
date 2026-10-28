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


void transform_comp_pool_resize(Pool *tranform_comp_pool, uint32_t size_to_add);
void tranform_comp_set_to_pool(Pool *tranform_comp_pool, uint32_t entt_id, Transform_Comp_t transform_comp);

// void pool_resize(Pool *pool, COMPONENT pool_type, uint32_t new_size); --
// void pool_add(Pool *pool, COMPONENT pool_type, void *new_component); --
// void pool_set(Pool *pool, COMPONENT pool_type, void *new_component, uint32_t index); --
// void *pool_get(Pool *pool, COMPONENT pool_type, uint32_t index);
