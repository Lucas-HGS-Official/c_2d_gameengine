#pragma once

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
    uint32_t id;
} Entity_t;

Entity_t init_entity(int id);
void destroy_entity(Entity_t *entity);


typedef struct System_t {
    char component_signature[SIGNATURE_SIZE];
    Entity_t *entities;
} System_t;

System_t *init_system(void);
void destroy_system(System_t *system);

void set_required_components(System_t * system, COMPONENT *component_list, int component_list_size);
void add_entity_to_system(System_t *system, Entity_t entity);
void remove_entity_from_system(System_t *system, Entity_t entity);
