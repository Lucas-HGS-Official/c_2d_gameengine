#include "collision_system.h"

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


System_t init_collision_system(void) {
    int comp_arr[3]={LOGGING_COMP, TRANSFORM_COMP, BOXCOLLIDER_COMP};
    System_t new_collision_system = init_system(comp_arr, 3);
    log_info("collision system initialized");

    return new_collision_system;
}
void collision_system_update(System_t *collision_system, World_t *world) {
    int16_t n_entitites = collision_system->entities.length;
    for (int16_t i=0; i<n_entitites; i++) {
        int16_t entt_id = collision_system->entities.id_list[i];

        Logging_Comp_t *logging_entt = SYSTEM_GET_COMP(world, LOGGING_COMP, entt_id);
        Transform_Comp_t *transform_entt = SYSTEM_GET_COMP(world, TRANSFORM_COMP, entt_id);
        BoxCollider_Comp_t *boxcollider_entt = SYSTEM_GET_COMP(world, BOXCOLLIDER_COMP, entt_id);

        Rectangle collision_box_entt = {
            .width=boxcollider_entt->width,
            .height=boxcollider_entt->height,
            .x=boxcollider_entt->x + transform_entt->position.x,
            .y=boxcollider_entt->y + transform_entt->position.y,
        };

        bool is_colliding = false;

        int16_t collided_entt = entt_id;

        for (int16_t j=0; j<n_entitites; j++) {
            int16_t entt_collision_check_id = collision_system->entities.id_list[j];
            if (entt_id == entt_collision_check_id) {
                continue;
            }

            Transform_Comp_t *transform_collided_entt = SYSTEM_GET_COMP(world, TRANSFORM_COMP, entt_collision_check_id);
            BoxCollider_Comp_t *boxcollider_collided_entt = SYSTEM_GET_COMP(world, BOXCOLLIDER_COMP, entt_collision_check_id);

            Rectangle collided_box_entt = {
                .width=boxcollider_collided_entt->width,
                .height=boxcollider_collided_entt->height,
                .x=boxcollider_collided_entt->x + transform_collided_entt->position.x,
                .y=boxcollider_collided_entt->y + transform_collided_entt->position.y,
            };

            is_colliding = CheckCollisionRecs(collision_box_entt, collided_box_entt);
            if (is_colliding) {
                collided_entt = entt_collision_check_id;
                log_info("entity %i is colliding with entity %i", entt_id, collided_entt);
            }
        }

        if (logging_entt) {
        }
    }
}
