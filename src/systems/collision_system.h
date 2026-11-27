#pragma once

#include "ECS.h"


System_t init_collision_system(void);
void collision_system_update(System_t *collision_system, World_t *world);
