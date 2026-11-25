#pragma once

#include "ECS.h"
#include "assets_manager.h"


System_t init_render_system(void);
void render_system_update(System_t *render_system,  World_t *world, AssetsManager_t *assets_manager);
