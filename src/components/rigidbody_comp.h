#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct RigidBody_Comp_t {
    Vector2 velocity;
} RigidBody_Comp_t;


ComponentPool_t init_rigidbody_comp_pool_data(void);
