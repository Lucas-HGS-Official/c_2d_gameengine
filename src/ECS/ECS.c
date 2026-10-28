#include "ECS.h"

#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "darray/darray.h"

#include "../components/transform_comp.h"


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
void entities_add_entity(Entity_t *entity, uint16_t id) {
    darray_push(entity->id_list, id);
    entity->length++;

    return;
}
void entities_remove_entity(Entity_t *entity, uint16_t id) {
    for (uint16_t i=0; i<entity->length; i++) {
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
        BITCLEAR(new_system->component.signature, i);
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
void system_set_required_components(System_t * system, COMPONENT *component_list, int component_list_size) {
    for (int i=0; i<component_list_size; i++) {
        BITSET(system->component.signature, component_list[i]);
    }

    return;
}
void system_add_entity_to(System_t *system, uint16_t entity_id) {
    entities_add_entity(&system->entities, entity_id);

    return;
}
void system_remove_entity(System_t *system, uint16_t entity_id) {
    entities_remove_entity(&system->entities, entity_id);

    return;
}


Pool *init_pool(void) {
    Pool *new_pool = MemAlloc(sizeof(Pool));
    *new_pool = (Pool) {0};

    return new_pool;
}
void destroy_pool_data(Pool *pool) {
    MemFree(pool->data);

    return;
}
void destroy_pool(Pool *pool) {
    destroy_pool_data(pool);
    MemFree(pool);

    return;
}


Registry_t *init_registry(void) {
    Registry_t *new_registry = MemAlloc(sizeof(Registry_t));
    *new_registry = (Registry_t) {0};

    return new_registry;
}
void destroy_registry(Registry_t *registry) {
    destroy_entities(registry->entities_to_be_added);
    destroy_entities(registry->entities_to_be_destroyed);
    for (SYSTEM i=0; i<NUM_SYSTEMS; i++) {
        destroy_system(&registry->systems_list[i]);
    }
    for (COMPONENT i=0; i<NUM_COMPONENTS; i++) {
        destroy_pool_data(&registry->component_pools[i]);
    }
    darray_free(registry->entities_components);
    MemFree(registry);

    return;
}

void registry_create_entity(Registry_t *registry) {
    uint16_t entity_id = registry->biggest_entity_id++;

    if (entity_id >= registry->entities_components_len) {
        Signature_t *signatures_list = registry->entities_components;
        Signature_t new_signature = {0};
        darray_push(signatures_list, new_signature);
        registry->entities_components_len++;
    }

    entities_add_entity(&registry->entities_to_be_added, entity_id);

    return;
}
void registry_add_component_to_entity(Registry_t *registry, uint16_t entt_id, COMPONENT comp_type) {
    BITSET(registry->entities_components[entt_id].signature, comp_type);
    // tranform_comp_add_to_pool(entt_id, &registry->component_pools[comp_type]);

    return;
}
void registry_add_entity_to_system(Registry_t *registry);
void registry_update(Registry_t *registry) {

    return;
}
