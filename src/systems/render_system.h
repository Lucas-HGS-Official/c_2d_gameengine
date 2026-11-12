#pragma once

#include "ECS.h"
#include "assets_manager.h"


System_t init_render_system();
void render_system_update(System_t *render_system,  Registry_t *registry, AssetsManager_t *assets_manager);
