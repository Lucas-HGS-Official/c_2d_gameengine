#pragma once

#include <stdint.h>

#include <limits.h>		/* for CHAR_BIT */

#define BITMASK(b) (1 << ((b) % CHAR_BIT))
#define BITSLOT(b) ((b) / CHAR_BIT)
#define BITSET(a, b) ((a)[BITSLOT(b)] |= BITMASK(b))
#define BITCLEAR(a, b) ((a)[BITSLOT(b)] &= ~BITMASK(b))
#define BITTEST(a, b) ((a)[BITSLOT(b)] & BITMASK(b))
#define BITNSLOTS(nb) ((nb + CHAR_BIT - 1) / CHAR_BIT)


const uint32_t MAX_COMPONENTS= 32;

#define SIGNATURE char signature[BITSLOT(MAX_COMPONENTS)]


typedef struct Entity_t {
    uint32_t id;
} Entity_t;

Entity_t init_entity(int id);

typedef struct System_t {
    SIGNATURE;
    Entity_t *entities; // TODO: download dinamic arrays lib
} System_t;

void add_entity_to_system(Entity_t *entity);
void remove_entity_from_system(Entity_t *entity);
