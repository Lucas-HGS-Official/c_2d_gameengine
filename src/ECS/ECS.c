#include "ECS.h"

#include <raylib.h>


Entity_t init_entity(int id) {
    Entity_t new_ent = {
        .id = id,
    };

    return new_ent;
}
