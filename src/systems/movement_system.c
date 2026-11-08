#include "movement_system.h"

#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "log_dot_c/log.h"

#include "ECS.h"
#include "rigidbody_comp.h"
#include "transform_comp.h"


System_t init_movement_system() {
    System_t new_movement_system = {0};
    BITSET(new_movement_system.requirement.signature, TRANSFORM_COMP);
    BITSET(new_movement_system.requirement.signature, RIGIDBODY_COMP);
    new_movement_system.entities = init_entities();

    new_movement_system.is_system_initialized = true;
    log_info("movement system initialized");

    return new_movement_system;
}
void movement_system_update(System_t *movement_system, Registry_t *registry) {
    Pool *transform_pool = &registry->component_pools[TRANSFORM_COMP];
    Pool *rigidbody_pool = &registry->component_pools[RIGIDBODY_COMP];
    Transform_Comp_t entt_transform = {0};
    RigidBody_Comp_t entt_rigidbody = {0};
    void *temp_comp = NULL;

    for (int16_t i=0; i<movement_system->entities.length; i++) {
        int16_t entt_id = movement_system->entities.id_list[i];
        temp_comp = transform_pool->get_comp(transform_pool, entt_id);
        if (temp_comp != NULL) {
            entt_transform = *(Transform_Comp_t *)temp_comp;
        }
        temp_comp = rigidbody_pool->get_comp(rigidbody_pool, entt_id);
        if (temp_comp != NULL) {
            entt_rigidbody = *(RigidBody_Comp_t *)temp_comp;
        }
    }

    return;
}
