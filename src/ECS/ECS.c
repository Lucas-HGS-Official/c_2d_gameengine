#include "ECS.h"

#include <raylib.h>


Entity_t init_entity(int id) {
    Entity_t new_ent = {
        .id = id,
    };

    return new_ent;
}
void destroy_entity(Entity_t *entity) {
    MemFree(entity);

    return;
}


// Allocates memory for the system
System_t *init_system(void) {
    System_t *new_system = MemAlloc(sizeof(System_t));

    for (int i=0; i<BITSLOT(MAX_COMPONENTS); i++) {
        new_system->component_signature[i] = 0;
    }

    return new_system;
}
void add_entity_to_system(Entity_t *entity);
void remove_entity_from_system(Entity_t *entity);

// Frees memory for the system
void destroy_system(System_t *system) {
    MemFree(system);
}

// Sets the system component signature to that it can chose aplicable entities
void set_required_components(System_t * system, COMPONENT *component_list, int component_list_size) {
    for (int i=0; i<component_list_size; i++) {
        BITSET(system->component_signature, component_list[i]);
    }

    return;
}
