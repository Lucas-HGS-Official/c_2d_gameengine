#include "movement_system.h"

#include "log_dot_c/log.h"

#include "ECS.h"


System_t init_movement_system() {
    System_t new_movement_system = {0};
    BITSET(new_movement_system.requirement.signature, TRANSFORM_COMP);
    BITSET(new_movement_system.requirement.signature, RIGIDBODY_COMP);
    new_movement_system.entities = init_entities();

    new_movement_system.is_system_initialized = true;
    log_info("movement system initialized");

    return new_movement_system;
}
void movement_system_update(System_t *movement_system) {

    return;
}
