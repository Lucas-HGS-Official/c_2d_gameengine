#include "movement_system.h"

#include <stdint.h>

#include "log_dot_c/log.h"

#include "ECS.h"
#include "logging_comp.h"
#include "rigidbody_comp.h"
#include "transform_comp.h"


System_t init_movement_system() {
    COMPONENT comp_arr[3]={LOGGING_COMP, TRANSFORM_COMP, RIGIDBODY_COMP};
    System_t new_movement_system = system_create_system(comp_arr, 3);
    log_info("movement system initialized");

    return new_movement_system;
}
void movement_system_update(System_t *movement_system, Registry_t *registry, float dt) {
    ComponentPool_t *logging_pool = &registry->component_pools[LOGGING_COMP];
    ComponentPool_t *transform_pool = &registry->component_pools[TRANSFORM_COMP];
    ComponentPool_t *rigidbody_pool = &registry->component_pools[RIGIDBODY_COMP];
    Logging_Comp_t *logging_entt = NULL;
    Transform_Comp_t *transform_entt = NULL;
    RigidBody_Comp_t *rigidbody_entt = NULL;
    void *temp_comp = NULL;

    for (int16_t i=0; i<movement_system->entities.length; i++) {
        int16_t entt_id = movement_system->entities.id_list[i];

        temp_comp = logging_pool->get_comp(logging_pool, entt_id);
        logging_entt = (Logging_Comp_t *)temp_comp;

        temp_comp = transform_pool->get_comp(transform_pool, entt_id);
        transform_entt = (Transform_Comp_t *)temp_comp;

        temp_comp = rigidbody_pool->get_comp(rigidbody_pool, entt_id);
        rigidbody_entt = (RigidBody_Comp_t *)temp_comp;

        transform_entt->position.x += rigidbody_entt->velocity.x * dt;
        transform_entt->position.y += rigidbody_entt->velocity.y * dt;
    }

    return;
}
