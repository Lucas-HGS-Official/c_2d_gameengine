#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct RigidBody_Comp_t {
    Vector2 velocity;
} RigidBody_Comp_t;


void init_rigidbody_comp_pool_data(Pool *rigidbody_comp_pool);
void rigidbody_comp_pool_resize(Pool *rigidbody_comp_pool, uint16_t size_to_add);
void rigidbody_comp_set_to_pool(Pool *rigidbody_comp_pool, uint16_t entt_id, RigidBody_Comp_t rigidbody_comp);
RigidBody_Comp_t *rigidbody_comp_get_from_pool(Pool *rigidbody_comp_pool, uint16_t entt_id);
void rigidbody_comp_remove_from_pool(Pool *rigidbody_comp_pool, uint16_t entt_id);
