#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct Animation_Comp_t {
    uint32_t num_frames;
    uint32_t current_frame;
    bool is_looping;
    float frame_time;
    float timer;
} Animation_Comp_t;


void init_animation_comp_pool_data(ComponentPool_t *animation_comp_pool);
