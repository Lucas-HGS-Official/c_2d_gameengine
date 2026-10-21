#pragma once

#include <stdint.h>

#include <limits.h>		/* for CHAR_BIT */

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)


#define MAX_COMPONENTS 32
#define SIGNATURE_SIZE BITSLOT(MAX_COMPONENTS)


typedef struct Entity_t {
    uint32_t id;
} Entity_t;

Entity_t init_entity(int id);
void destroy_entity(Entity_t *entity);


typedef struct System_t {
    char signature[SIGNATURE_SIZE];
    Entity_t *entities; // TODO: download dinamic arrays lib
} System_t;

System_t *init_system(void);
void add_entity_to_system(Entity_t *entity);
void remove_entity_from_system(Entity_t *entity);
void destroy_system(System_t *system);
