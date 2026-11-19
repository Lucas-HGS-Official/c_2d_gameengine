#pragma once

#include "ECS.h"


System_t init_animation_system(void);
void animation_system_update(System_t *animation_system, Registry_t *registry, float dt);
