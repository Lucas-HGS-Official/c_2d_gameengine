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


void init_transform_comp_pool_data(Pool *transform_comp_pool);
void transform_comp_pool_resize(Pool *transform_comp_pool, int16_t size_to_add);
void transform_comp_set_to_pool(Pool *transform_comp_pool, int16_t entt_id, void *transform_comp);
void *transform_comp_get_from_pool(Pool *transform_comp_pool, int16_t entt_id);
void transform_comp_remove_from_pool(Pool *transform_comp_pool, int16_t entt_id);
