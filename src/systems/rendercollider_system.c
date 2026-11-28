#include "rendercollider_system.h"

#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>

#include "log_dot_c/log.h"

#include "ECS.h"
#include "../game/game.h"
#include "base_system.h"
#include "logging_comp.h"
#include "transform_comp.h"
#include "boxcollider_comp.h"


System_t init_rendercollider_system(void) {
    int comp_arr[3]={LOGGING_COMP, TRANSFORM_COMP, BOXCOLLIDER_COMP};
    System_t new_rendercollider_system = init_system(comp_arr, 3);
    log_info("render collider system initialized");

    return new_rendercollider_system;
}
void rendercollider_system_update(System_t *rendercollider_system,  World_t *world, bool is_debugging) {
    if (!is_debugging) {
        return;
    }
    int16_t n_entitites = rendercollider_system->entities.length;
    for (int16_t i=0; i<n_entitites; i++) {
        int16_t entt_id = rendercollider_system->entities.id_list[i];

        Logging_Comp_t *logging_entt = SYSTEM_GET_COMP(world, LOGGING_COMP, entt_id);
        Transform_Comp_t *transform_entt = SYSTEM_GET_COMP(world, TRANSFORM_COMP, entt_id);
        BoxCollider_Comp_t *boxcollider_entt = SYSTEM_GET_COMP(world, BOXCOLLIDER_COMP, entt_id);

        Rectangle collision_box_entt = {
            .width=boxcollider_entt->width,
            .height=boxcollider_entt->height,
            .x=boxcollider_entt->x + transform_entt->position.x,
            .y=boxcollider_entt->y + transform_entt->position.y,
        };

        DrawRectangleLinesEx(collision_box_entt, 1.f, YELLOW);
    }
}
