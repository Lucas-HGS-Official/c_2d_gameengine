#pragma once

#include "ECS.h"


System_t init_movement_system(void);
void movement_system_update(System_t *movement_system, World_t *world, float dt);
