#include "ECS.h"

#include <raylib.h>
#include "darray/darray.h"


// Allocates memory for the entity
Entity_t init_entity(int id) {
    Entity_t new_ent = {
        .id = id,
    };

    return new_ent;
}
// Frees memory for the entity
void destroy_entity(Entity_t *entity) {
    MemFree(entity);

    return;
}


// Allocates memory for the system
System_t *init_system(void) {
    System_t *new_system = MemAlloc(sizeof(System_t));

    for (int i=0; i<BITSLOT(MAX_COMPONENTS); i++) {
        BITCLEAR(new_system->component_signature, i);
    }
    for (int i=0; i<MAX_ENTITY_PER_SYSTEM; i++) {
        new_system->entities[i] = (Entity_t) {0};
    }

    return new_system;
}
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
void add_entity_to_system(System_t *system, Entity_t entity) {
    darray_push(system->entities, entity);

    return;
}
void remove_entity_from_system(System_t *system, Entity_t entity) {
    int entities_size = darray_size(system->entities);
    for (int i=0; i<entities_size; i++) {
        if (system->entities[i].id == entity.id) {
            system->entities[i] = (Entity_t) {0};

            break;
        }
    }

    return;
}
