#pragma once

#include "ECS.h"


System_t init_render_system();
void render_system_update(System_t *render_system,  Registry_t *registry);
