#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct RigidBody_Comp_t {
    Vector2 velocity;
} RigidBody_Comp_t;


void init_rigidbody_comp_pool_data(Comp_Pool_t *rigidbody_comp_pool);
