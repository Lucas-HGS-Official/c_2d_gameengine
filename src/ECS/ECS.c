#include "ECS.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "darray/darray.h"
#include "log_dot_c/log.h"


void destroy_entities(Entities_t entity);

void entities_add_entity(Entities_t *entity, int16_t id);
void entities_remove_entity(Entities_t *entity, int16_t id);


System_t *init_system(void);
void destroy_system(System_t *system);

void system_set_required_components(System_t * system, int *component_list, int component_list_size);
void system_add_entity(System_t *system, int16_t entity_id);
void system_remove_entity(System_t *system, int16_t entity_id);


ComponentPool_t *init_pool(void);
void destroy_pool_data(ComponentPool_t *pool);
void destroy_pool(ComponentPool_t *pool);


// Allocates memory for the entities
Entities_t entities_create_entities(void) {
    Entities_t new_ent = {0};
    new_ent.is_enttities_initialized = true;
    log_info("entities initialized");

    return new_ent;
}
// Frees memory for the entities
void destroy_entities(Entities_t entity) {
    if (!entity.is_enttities_initialized) {

        return;
    }
    if (entity.length>0) {
        darray_free(entity.id_list);
        log_info("freed all entities");
    }

    return;
}
void entities_add_entity(Entities_t *entity, int16_t id) {
    darray_push(entity->id_list, id);
    entity->length++;
    // log_info("entity %i added", id);

    return;
}
void entities_remove_entity(Entities_t *entity, int16_t id) {
    for (int16_t i=0; i<entity->length; i++) {
        if (entity->id_list[i] == id) {
            entity->id_list[i] = -1;
            if (i == entity->length-1) {
                entity->length--;
            }
            // log_info("entity %i removed", id);
        }
    }

    return;
}


// Allocates memory for the system
System_t *init_system(void) {
    System_t *new_system = MemAlloc(sizeof(System_t));

    for (int i=0; i<BITSLOT(MAX_COMPONENTS); i++) {
        BITCLEAR(new_system->requirement.signature, i);
    }
    new_system->entities = entities_create_entities();
    log_info("system struct initialized");

    return new_system;
}
// Frees memory for the system
void destroy_system(System_t *system) {
    if (!system->is_system_initialized) {
        log_info("system not initialized");

        return;
    }
    destroy_entities(system->entities);
    MemFree(system);
    log_info("system freed");

    return;
}
System_t system_create_system(int *comp_arr, int comp_arr_len) {
    System_t new_system = {0};
    system_set_required_components(&new_system, comp_arr, comp_arr_len);
    new_system.entities = entities_create_entities();
    new_system.is_system_initialized = true;

    return new_system;
}
// Sets the system component signature to that it can chose aplicable entities
void system_set_required_components(System_t *system, int *component_list, int component_list_size) {

    log_info("system set to require the components:");
    for (int i=0; i<component_list_size; i++) {
        BITSET(system->requirement.signature, component_list[i]);
        log_info("%i", component_list[i]);
    }

    return;
}
void system_add_entity(System_t *system, int16_t entity_id) {

    // log_info("adding entity %i to system", entity_id);
    entities_add_entity(&system->entities, entity_id);

    return;
}
void system_remove_entity(System_t *system, int16_t entity_id) {

    // log_info("removing entity %i to system", entity_id);
    entities_remove_entity(&system->entities, entity_id);

    return;
}


ComponentPool_t *init_pool(void) {
    ComponentPool_t *new_pool = MemAlloc(sizeof(ComponentPool_t));
    *new_pool = (ComponentPool_t) {0};
    log_info("component pool initialized");

    return new_pool;
}
void destroy_pool_data(ComponentPool_t *pool) {
    if (pool->length != 0) {
        MemFree(pool->data);
    }

    return;
}
void destroy_pool(ComponentPool_t *pool) {
    if (!pool->is_pool_initialized) {
        log_info("component pool not initialized");

        return;
    }
    destroy_pool_data(pool);
    MemFree(pool);
    log_info("freed component pool");

    return;
}


World_t *init_world(void) {
    World_t *new_world = MemAlloc(sizeof(World_t));
    *new_world = (World_t) {0};

    new_world->entities_to_be_added = entities_create_entities();
    new_world->entities_to_be_destroyed = entities_create_entities();

    new_world->is_world_initialized = true;
    log_info("world initialized");

    return new_world;
}
void destroy_world(World_t *world) {
    if (!world->is_world_initialized) {
        log_info("world not initialized");

        return;
    }

    destroy_entities(world->entities_to_be_added);
    destroy_entities(world->entities_to_be_destroyed);
    log_info("freed all entities in the world struct");

    for (int i=0; i<MAX_SYSTEMS; i++) {

        destroy_entities(world->systems_list[i].entities);
    }
    for (int i=0; i<MAX_COMPONENTS; i++) {

        destroy_pool_data(&world->component_pools[i]);
    }
    if (world->entities_components_len != 0) {
        darray_free(world->entities_components);
        log_info("freed component signatures in the world");
    }
    MemFree(world);
    log_info("freed world");

    return;
}

int16_t world_create_entity(World_t *world) {
    int16_t entity_id = world->biggest_entity_id;
    world->biggest_entity_id++;

    while (entity_id >= world->entities_components_len) {
        Signature_t new_signature = {0};
        darray_push(world->entities_components, new_signature);
        world->entities_components_len++;
    }
    entities_add_entity(&world->entities_to_be_added, entity_id);

    return entity_id;
}
void world_set_component_to_entity(World_t *world, int16_t entt_id, int comp_type, void *comp) {

    if (entt_id >= world->entities_components_len) {
        log_info("no space for new signature");

        return;
    }

    BITSET(world->entities_components[entt_id].signature, comp_type);
    world->component_pools[comp_type].set_comp(&world->component_pools[comp_type], entt_id, comp);

    return;
}
void *world_get_component_of_entity(World_t *world, int16_t entt_id, int comp_type) {
    if (entt_id == -1) {
        return NULL;
    }

    Signature_t entt_signature = world->entities_components[entt_id];
    if (BITTEST(entt_signature.signature, comp_type)) {
        ComponentPool_t *comp_pool = &world->component_pools[comp_type];
        return comp_pool->get_comp(comp_pool, entt_id);
    }

    return NULL;
}
void world_remove_component_from_entity(World_t *world, int16_t entt_id, int comp_type) {
    log_info("removing %i component from entity %i", comp_type, entt_id);

    BITCLEAR(world->entities_components[entt_id].signature, comp_type);
    world->component_pools[comp_type].remove_comp(&world->component_pools[comp_type], entt_id);

    return;
}
bool world_entity_has_component(World_t *world, int16_t entt_id, int comp_type) {
    log_info("testing component %i for entity %i", comp_type, entt_id);

    return BITTEST(world->entities_components[entt_id].signature, comp_type);
}

void world_remove_system(World_t *world, int system_to_remove) {
    log_info("removing %i system from world");

    world->systems_list[system_to_remove] = (System_t) {0};

    return;
}
bool world_has_system(World_t *world, int system_to_check) {
    // log_info("testing system %i", system_to_check);

    return world->systems_list[system_to_check].is_system_initialized;
}
void world_add_entity_to_systems(World_t *world, int16_t entt_id) {
    // log_info("adding entity %i to systems", entt_id);
    for (int i=0; i<MAX_SYSTEMS; i++) {
        if (!world_has_system(world, i)) {
            continue;
        }
        Signature_t system_required_signature = world->systems_list[i].requirement;
        Signature_t entity_signature = world->entities_components[entt_id];

        bool is_entt_added_to_sys = false;

        for (int16_t j=0; j<MAX_COMPONENTS; j++) {
            bool is_component_required_in_sys = BITTEST(system_required_signature.signature, j);
            bool is_component_turned_on_in_entt = BITTEST(entity_signature.signature, j);

            if (!is_component_required_in_sys) {
                continue;
            } else if (is_component_required_in_sys && is_component_turned_on_in_entt) {
                is_entt_added_to_sys = true;
            } else {
                is_entt_added_to_sys = false;
                break;
            }
        }
        if (is_entt_added_to_sys) {
            system_add_entity(&world->systems_list[i], entt_id);
            // log_info("entity %i added to system %i", entt_id, i);
        }
    }

    return;
}
void world_remove_entity_from_systems(World_t *world, int16_t entt_id) {
    log_info("removing entity %i from systems", entt_id);
    for (int i=0; i<MAX_SYSTEMS; i++) {
        if (!world_has_system(world, i)) {
            continue;
        }
        Entities_t *entts = &world->systems_list[i].entities;
        int16_t *entts_ids = entts->id_list;
        int16_t entts_len = entts->length;
        for (int j=0; j<entts_len; j++) {
            if (entts_ids[j] == entt_id) {
                entities_remove_entity(entts, entts_ids[j]);
                break;
            }
        }
    }

    return;
}
void world_update(World_t *world) {
    int16_t n_entts_to_add = world->entities_to_be_added.length;
    for (int16_t i=0; i<n_entts_to_add; i++) {
        int16_t *entt_id = &world->entities_to_be_added.id_list[i];
        if (*entt_id == -1) {
            continue;
        } else {
            world_add_entity_to_systems(world, *entt_id);
            entities_remove_entity(&world->entities_to_be_added, *entt_id);
        }
    }

    return;
}
