#pragma once

#include "ECS.h"


System_t init_rendercollider_system(void);
void rendercollider_system_update(System_t *rendercollider_system,  World_t *world, bool is_debugging);
