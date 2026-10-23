#pragma once

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

    NUM_COMPONENTS,
} COMPONENT;


typedef struct Entity_t {
    uint32_t *id_list;
    uint32_t length;
} Entity_t;

Entity_t init_entities(void);
void destroy_entities(Entity_t entity);
void add_entity(Entity_t *entity, uint32_t id);
void remove_entity(Entity_t *entity, uint32_t id);


typedef struct System_t {
    char component_signature[SIGNATURE_SIZE];
    Entity_t entities;
} System_t;

System_t *init_system(void);
void destroy_system(System_t *system);

void set_required_components(System_t * system, COMPONENT *component_list, int component_list_size);
void add_entity_to_system(System_t *system, uint32_t entity_id);
void remove_entity_from_system(System_t *system, uint32_t entity_id);


typedef struct Pool {
    void *data;
    size_t data_size;
} Pool;

void pool_resize(Pool *pool, COMPONENT pool_type, uint32_t new_size);
void pool_add(Pool *pool, COMPONENT pool_type, void *new_component);
void pool_set(Pool *pool, COMPONENT pool_type, void *new_component, uint32_t index);
void *pool_get(Pool *pool, COMPONENT pool_type, uint32_t index);


typedef struct ECSCoordinator_t {
    Pool component_pools[NUM_COMPONENTS];
} ECSCoordinator_t;
