#include "ECS.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "darray/darray.h"
#include "log_dot_c/log.h"

#include "../components/transform_comp.h"
#include "../components/rigidbody_comp.h"
#include "../systems/movement_system.h"



// Entities_t init_entities(void);
void destroy_entities(Entities_t entity);

void entities_add_entity(Entities_t *entity, int16_t id);
void entities_remove_entity(Entities_t *entity, int16_t id);


System_t *init_system(void);
void destroy_system(System_t *system);

void system_set_required_components(System_t * system, COMPONENT *component_list, int component_list_size);
void system_add_entity(System_t *system, int16_t entity_id);
void system_remove_entity(System_t *system, int16_t entity_id);


Comp_Pool_t *init_pool(void);
void destroy_pool_data(Comp_Pool_t *pool);
void destroy_pool(Comp_Pool_t *pool);


// Allocates memory for the entities
Entities_t init_entities(void) {
    Entities_t new_ent = {0};
    new_ent.is_enttities_initialized = true;
    log_info("entities initialized");

    return new_ent;
}
// Frees memory for the entities
void destroy_entities(Entities_t entity) {
    if (!entity.is_enttities_initialized) {
        log_info("entities not initialized");

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
    log_info("entity %i added", id);

    return;
}
void entities_remove_entity(Entities_t *entity, int16_t id) {
    for (int16_t i=0; i<entity->length; i++) {
        if (entity->id_list[i] == id) {
            entity->id_list[i] = -1;
            if (i == entity->length-1) {
                entity->length--;
            }
            log_info("entity %i removed", id);
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
    new_system->entities = init_entities();
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
// Sets the system component signature to that it can chose aplicable entities
void system_set_required_components(System_t *system, COMPONENT *component_list, int component_list_size) {

    log_info("system set to require the components:");
    for (int i=0; i<component_list_size; i++) {
        BITSET(system->requirement.signature, component_list[i]);
        log_info("%i", component_list[i]);
    }

    return;
}
void system_add_entity(System_t *system, int16_t entity_id) {

    log_info("adding entity %i to system", entity_id);
    entities_add_entity(&system->entities, entity_id);

    return;
}
void system_remove_entity(System_t *system, int16_t entity_id) {

    log_info("removing entity %i to system", entity_id);
    entities_remove_entity(&system->entities, entity_id);

    return;
}


Comp_Pool_t *init_pool(void) {
    Comp_Pool_t *new_pool = MemAlloc(sizeof(Comp_Pool_t));
    *new_pool = (Comp_Pool_t) {0};
    log_info("component pool initialized");

    return new_pool;
}
void destroy_pool_data(Comp_Pool_t *pool) {
    if (pool->length != 0) {
        log_info("no data in component pool");

        MemFree(pool->data);
    } else {
        log_info("freed component pool data");
    }

    return;
}
void destroy_pool(Comp_Pool_t *pool) {
    if (!pool->is_pool_initialized) {
        log_info("component pool not initialized");

        return;
    }
    destroy_pool_data(pool);
    MemFree(pool);
    log_info("freed component pool");

    return;
}


Registry_t *init_registry(void) {
    Registry_t *new_registry = MemAlloc(sizeof(Registry_t));
    *new_registry = (Registry_t) {0};

    new_registry->entities_to_be_added = init_entities();
    new_registry->entities_to_be_destroyed = init_entities();

    for (COMPONENT i=0; i<NUM_COMPONENTS; i++) {
        switch (i) {
            case TRANSFORM_COMP:
                init_transform_comp_pool_data(&new_registry->component_pools[i]);
                break;

            case RIGIDBODY_COMP:
                init_rigidbody_comp_pool_data(&new_registry->component_pools[i]);
                break;

            case NUM_COMPONENTS:
                break;
        }
    }

    for (SYSTEM i=0; i<NUM_SYSTEMS; i++) {
        switch (i) {
            case MOVEMENT_SYS:
                new_registry->systems_list[i] = init_movement_system();
                break;

            case NUM_SYSTEMS:
                break;
        }
    }

    new_registry->is_registry_initialized = true;
    log_info("registry initialized");

    return new_registry;
}
void destroy_registry(Registry_t *registry) {
    if (!registry->is_registry_initialized) {
        log_info("registry not initialized");

        return;
    }

    destroy_entities(registry->entities_to_be_added);
    destroy_entities(registry->entities_to_be_destroyed);
    log_info("freed all entities in the registry struct");

    for (SYSTEM i=0; i<NUM_SYSTEMS; i++) {

        log_info("freeing %i system in the registry", i);
        destroy_entities(registry->systems_list[i].entities);
    }
    for (COMPONENT i=0; i<NUM_COMPONENTS; i++) {

        log_info("freeing %i component in the registry", i);
        destroy_pool_data(&registry->component_pools[i]);
    }
    if (registry->entities_components_len != 0) {
        darray_free(registry->entities_components);
        log_info("freed component signatures in the registry");
    }
    MemFree(registry);
    log_info("freed registry");

    return;
}

int16_t registry_create_entity(Registry_t *registry) {
    log_info("creating a new entity in the registry");
    int16_t entity_id = registry->biggest_entity_id;
    registry->biggest_entity_id++;

    while (entity_id >= registry->entities_components_len) {
        Signature_t new_signature = {0};
        darray_push(registry->entities_components, new_signature);
        registry->entities_components_len++;
        log_info("new slot for component signature added in the registry");
    }
    entities_add_entity(&registry->entities_to_be_added, entity_id);
    log_info("entity %i created in the registry", entity_id);

    return entity_id;
}
void registry_set_component_to_entity(Registry_t *registry, int16_t entt_id, COMPONENT comp_type, void *comp) {
    log_info("setting %i component to entity %i", comp_type, entt_id);

    if (entt_id >= registry->entities_components_len) {
        log_info("no space for new signature");

        return;
    }

    BITSET(registry->entities_components[entt_id].signature, comp_type);
    registry->component_pools[comp_type].set_comp(&registry->component_pools[comp_type], entt_id, comp);

    return;
}
void *registry_get_component_of_entity(Registry_t *registry, int16_t entt_id, COMPONENT comp_type) {
    if (entt_id == -1) {
        return NULL;
    }

    Signature_t entt_signature = registry->entities_components[entt_id];
    if (BITTEST(entt_signature.signature, comp_type)) {
        Comp_Pool_t *comp_pool = &registry->component_pools[comp_type];
        return comp_pool->get_comp(comp_pool, entt_id);
    }

    return NULL;
}
void registry_remove_component_from_entity(Registry_t *registry, int16_t entt_id, COMPONENT comp_type) {
    log_info("removing %i component from entity %i", comp_type, entt_id);

    BITCLEAR(registry->entities_components[entt_id].signature, comp_type);
    registry->component_pools[comp_type].remove_comp(&registry->component_pools[comp_type], entt_id);

    return;
}
bool registry_entity_has_component(Registry_t *registry, int16_t entt_id, COMPONENT comp_type) {
    log_info("testing component %i for entity %i", comp_type, entt_id);

    return BITTEST(registry->entities_components[entt_id].signature, comp_type);
}
void registry_add_system(Registry_t *registry, SYSTEM system_to_add) {
    log_info("adding %i system to registry");

    switch (system_to_add) {
        case MOVEMENT_SYS:
            registry->systems_list[system_to_add] = init_movement_system();
            break;
        case NUM_SYSTEMS:
            break;
        default:
            break;
    }

    return;
}
void registry_remove_system(Registry_t *registry, SYSTEM system_to_remove) {
    log_info("removing %i system from registry");

    registry->systems_list[system_to_remove] = (System_t) {0};

    return;
}
bool registry_has_system(Registry_t *registry, SYSTEM system_to_check) {
    log_info("testing system %i", system_to_check);

    return registry->systems_list[system_to_check].is_system_initialized;
}
void registry_add_entity_to_systems(Registry_t *registry, int16_t entt_id) {
    log_info("adding entity %i to systems", entt_id);
    for (SYSTEM i=0; i<NUM_SYSTEMS; i++) {
        if (!registry_has_system(registry, i)) {
            continue;
        }
        Signature_t system_required_signature = registry->systems_list[i].requirement;
        Signature_t entity_signature = registry->entities_components[entt_id];

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
            system_add_entity(&registry->systems_list[i], entt_id);
            log_info("entity %i added to system %i", entt_id, i);
        }
    }

    return;
}
void registry_remove_entity_from_systems(Registry_t *registry, int16_t entt_id) {
    log_info("removing entity %i from systems", entt_id);
    for (SYSTEM i=0; i<NUM_SYSTEMS; i++) {
        if (!registry_has_system(registry, i)) {
            continue;
        }
        Entities_t *entts = &registry->systems_list[i].entities;
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
void registry_update(Registry_t *registry) {
    int16_t n_entts_to_add = registry->entities_to_be_added.length;
    for (int16_t i=0; i<n_entts_to_add; i++) {
        int16_t *entt_id = &registry->entities_to_be_added.id_list[i];
        if (*entt_id == -1) {
            continue;
        } else {
            registry_add_entity_to_systems(registry, *entt_id);
            entities_remove_entity(&registry->entities_to_be_added, *entt_id);
        }
    }

    return;
}
