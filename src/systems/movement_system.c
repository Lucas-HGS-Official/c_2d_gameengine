#include "movement_system.h"

#include "ECS.h"


System_t init_movement_system() {
    System_t new_movement_system = {0};
    BITSET(new_movement_system.component_requirement.signature, TRANSFORM_COMP);
    new_movement_system.is_system_initialized = true;

    return new_movement_system;
}
void movement_system_update(System_t *movement_system) {

    return;
}
