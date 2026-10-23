#include "ECS.h"

#include <raylib.h>
#include <stdint.h>
#include "darray/darray.h"


// Allocates memory for the entities
Entity_t init_entities(void) {
    Entity_t new_ent = {0};

    return new_ent;
}
// Frees memory for the entities
void destroy_entities(Entity_t entity) {
    if (entity.length>0) {
        darray_free(entity.id_list);
    }

    return;
}
void add_entity(Entity_t *entity, uint32_t id) {
    darray_push(entity->id_list, id);
    entity->length++;

    return;
}
void remove_entity(Entity_t *entity, uint32_t id) {
    for (uint32_t i=0; i<entity->length; i++) {
        if (entity->id_list[i] == id) {
            entity->id_list[i] = entity->id_list[entity->length-1];
            entity->id_list[entity->length-1] = 0;
            entity->length--;
        }
    }

    return;
}


// Allocates memory for the system
System_t *init_system(void) {
    System_t *new_system = MemAlloc(sizeof(System_t));

    for (int i=0; i<BITSLOT(MAX_COMPONENTS); i++) {
        BITCLEAR(new_system->component_signature, i);
    }
    new_system->entities = init_entities();

    return new_system;
}
// Frees memory for the system
void destroy_system(System_t *system) {
    destroy_entities(system->entities);
    MemFree(system);
}
// Sets the system component signature to that it can chose aplicable entities
void set_required_components(System_t * system, COMPONENT *component_list, int component_list_size) {
    for (int i=0; i<component_list_size; i++) {
        BITSET(system->component_signature, component_list[i]);
    }

    return;
}
void add_entity_to_system(System_t *system, uint32_t entity_id) {
    add_entity(&system->entities, entity_id);

    return;
}
void remove_entity_from_system(System_t *system, uint32_t entity_id) {
    remove_entity(&system->entities, entity_id);

    return;
}


void pool_resize(Pool *pool, COMPONENT pool_type, uint32_t new_size) {
    pool[pool_type].data = MemRealloc(pool[pool_type].data, pool[pool_type].data_size*new_size);

    return;
}
void pool_add(Pool *pool, COMPONENT pool_type, void *new_component);
void pool_set(Pool *pool, COMPONENT pool_type, void *new_component, uint32_t index);
void *pool_get(Pool *pool, COMPONENT pool_type, uint32_t index) {

    return &pool[pool_type].data[index]; // not working, data[index] does not get the right address, need size info
}
