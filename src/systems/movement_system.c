#include "movement_system.h"

#include <stdint.h>

#include "log_dot_c/log.h"

#include "ECS.h"
#include "rigidbody_comp.h"
#include "transform_comp.h"


System_t init_movement_system() {
    COMPONENT comp_arr[2]={TRANSFORM_COMP, RIGIDBODY_COMP};
    System_t new_movement_system = system_create_system(comp_arr, 2);
    log_info("movement system initialized");

    return new_movement_system;
}
void movement_system_update(System_t *movement_system, Registry_t *registry, float dt) {
    ComponentPool_t *transform_pool = &registry->component_pools[TRANSFORM_COMP];
    ComponentPool_t *rigidbody_pool = &registry->component_pools[RIGIDBODY_COMP];
    Transform_Comp_t *entt_transform = NULL;
    RigidBody_Comp_t *entt_rigidbody = NULL;
    void *temp_comp = NULL;

    for (int16_t i=0; i<movement_system->entities.length; i++) {
        int16_t entt_id = movement_system->entities.id_list[i];

        temp_comp = transform_pool->get_comp(transform_pool, entt_id);
        entt_transform = (Transform_Comp_t *)temp_comp;

        temp_comp = rigidbody_pool->get_comp(rigidbody_pool, entt_id);
        entt_rigidbody = (RigidBody_Comp_t *)temp_comp;

        entt_transform->position.x += entt_rigidbody->velocity.x * dt;
        entt_transform->position.y += entt_rigidbody->velocity.y * dt;
    }

    return;
}
