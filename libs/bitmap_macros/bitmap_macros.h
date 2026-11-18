#pragma once

#include <limits.h>		/* for CHAR_BIT */

#define BITMASK(bit_number) (1 << ((bit_number) % CHAR_BIT))
#define BITSLOT(bit_slot) ((bit_slot) / CHAR_BIT)
#define BITSET(bitmap, bit_to_set) ((bitmap)[BITSLOT(bit_to_set)] |= BITMASK(bit_to_set))
#define BITCLEAR(bitmap, bit_to_clear) ((bitmap)[BITSLOT(bit_to_clear)] &= ~BITMASK(bit_to_clear))
#define BITTEST(bitmap, bit_to_test) ((bitmap)[BITSLOT(bit_to_test)] & BITMASK(bit_to_test))
#define BITNSLOTS(bitmap_size) ((bitmap_size + CHAR_BIT - 1) / CHAR_BIT)
