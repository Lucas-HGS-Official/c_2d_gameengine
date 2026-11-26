#include "movement_system.h"

#include <stdint.h>

#include "log_dot_c/log.h"

#include "ECS.h"
#include "../game/game.h"
#include "base_system.h"
#include "logging_comp.h"
#include "rigidbody_comp.h"
#include "transform_comp.h"


System_t init_movement_system() {
    int comp_arr[3]={LOGGING_COMP, TRANSFORM_COMP, RIGIDBODY_COMP};
    System_t new_movement_system = init_system(comp_arr, 3);
    log_info("movement system initialized");

    return new_movement_system;
}
void movement_system_update(System_t *movement_system, World_t *world, float dt) {
    for (int16_t i=0; i<movement_system->entities.length; i++) {
        int16_t entt_id = movement_system->entities.id_list[i];

        Logging_Comp_t *logging_entt = SYSTEM_GET_COMP(world, LOGGING_COMP, entt_id);
        Transform_Comp_t *transform_entt = SYSTEM_GET_COMP(world, TRANSFORM_COMP, entt_id);
        RigidBody_Comp_t *rigidbody_entt = SYSTEM_GET_COMP(world, RIGIDBODY_COMP, entt_id);

        transform_entt->position.x += rigidbody_entt->velocity.x * dt;
        transform_entt->position.y += rigidbody_entt->velocity.y * dt;

        if (*logging_entt) {

        }
    }

    return;
}
