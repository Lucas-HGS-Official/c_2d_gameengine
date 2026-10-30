#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <limits.h>		/* for CHAR_BIT */

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)


#define MAX_ENTITY_PER_SYSTEM 200

#define MAX_COMPONENTS 32
#define SIGNATURE_SIZE BITSLOT(MAX_COMPONENTS)


typedef enum COMPONENT {
    TRANSFORM_COMP,

    NUM_COMPONENTS,
} COMPONENT;

typedef enum SYSTEM {
    MOVEMENT_SYS,

    NUM_SYSTEMS,
} SYSTEM;


typedef struct Signature_t {
    char signature[SIGNATURE_SIZE];
} Signature_t;

typedef struct Entity_t {
    uint16_t *id_list;
    uint16_t length;
    bool is_enttities_initialized;
} Entity_t;

Entity_t init_entities(void);
void destroy_entities(Entity_t entity);

void entities_add_entity(Entity_t *entity, uint16_t id);
void entities_remove_entity(Entity_t *entity, uint16_t id);


typedef struct System_t {
    Signature_t component;
    Entity_t entities;
    bool is_system_initialized;
} System_t;

System_t *init_system(void);
void destroy_system(System_t *system);

void system_set_required_components(System_t * system, COMPONENT *component_list, int component_list_size);
void system_add_entity_to(System_t *system, uint16_t entity_id);
void system_remove_entity(System_t *system, uint16_t entity_id);


typedef struct Pool {
    void *data;
    uint16_t max_length;
    uint16_t current_length;
    size_t data_size;
    bool is_pool_initialized;
} Pool;

Pool *init_pool(void);
void destroy_pool_data(Pool *pool);
void destroy_pool(Pool *pool);


typedef struct Registry_t {
    uint16_t biggest_entity_id;
    Entity_t entities_to_be_added;
    Entity_t entities_to_be_destroyed;
    Signature_t *entities_components;
    uint16_t entities_components_len;

    Pool component_pools[NUM_COMPONENTS];
    System_t systems_list[NUM_SYSTEMS];

    bool is_registry_initialized;
} Registry_t;

Registry_t *init_registry(void);
void destroy_registry(Registry_t *registry);

void registry_create_entity(Registry_t *registry);
void registry_set_component_to_entity(Registry_t *registry, uint16_t entt_id, COMPONENT comp_type, void *comp);
void registry_add_entity_to_system(Registry_t *registry);
void registry_update(Registry_t *registry);
