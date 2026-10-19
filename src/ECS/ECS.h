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

typedef struct Entity_t {
    uint32_t id;
} Entity_t;


Entity_t init_entity(int id);
