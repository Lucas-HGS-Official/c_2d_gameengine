#include "transform_comp.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"


#define SLOTS_TO_ADD 100


void init_transform_comp_pool_data(Pool *transform_comp_pool) {
    transform_comp_pool_resize(transform_comp_pool, SLOTS_TO_ADD);
    transform_comp_pool->is_pool_initialized = true;
    log_info("tranform pool initilized");

    return;
}
void transform_comp_pool_resize(Pool *transform_comp_pool, uint16_t size_to_add) {
    uint16_t old_length = transform_comp_pool->length;
    uint16_t new_size = old_length + size_to_add;
    size_t new_memory_size = sizeof(Transform_Comp_t) * new_size;

    transform_comp_pool->data = MemRealloc(transform_comp_pool->data, new_memory_size);
    transform_comp_pool->length = new_size;

    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) transform_comp_pool->data;
    for (int i=old_length; i<transform_comp_pool->length; i++) {
        transform_comp_data[i] =  (Transform_Comp_t) {0};
    }

    transform_comp_pool->length = new_size;
    log_info("tranform pool new size %i", new_size);

    return;
}
void transform_comp_set_to_pool(Pool *transform_comp_pool, uint16_t entt_id, Transform_Comp_t transform_comp) {
    if (entt_id >= transform_comp_pool->length) {
        transform_comp_pool_resize(transform_comp_pool, SLOTS_TO_ADD);
    }
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) transform_comp_pool->data;
    transform_comp_data[entt_id] = transform_comp;
    log_info("set transform comp for entity %i", entt_id);

    return;
}
Transform_Comp_t *transform_comp_get_from_pool(Pool *transform_comp_pool, uint16_t entt_id) {
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) transform_comp_pool->data;
    log_info("get transform comp from entity %i", entt_id);

    return &transform_comp_data[entt_id];
}
void transform_comp_remove_from_pool(Pool *transform_comp_pool, uint16_t entt_id) {
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) transform_comp_pool->data;
    transform_comp_data[entt_id] = (Transform_Comp_t) {0};
    log_info("remove transform comp from entity %i", entt_id);

    return;
}
