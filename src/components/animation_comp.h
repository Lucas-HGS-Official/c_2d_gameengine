#pragma once

#include <stdint.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


typedef struct Animation_Comp_t {
    uint32_t num_frames;
    uint32_t current_frame;
    uint32_t frame_speed;
    uint32_t startup_time;
    bool is_looping;
} Animation_Comp_t;


void init_animation_comp_pool_data(ComponentPool_t *animation_comp_pool);
