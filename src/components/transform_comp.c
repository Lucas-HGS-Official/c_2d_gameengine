#include "transform_comp.h"

#include <stddef.h>
#include <stdint.h>

#include <raylib.h>


void init_trasform_comp_pool_data(Pool *transform_comp_pool) {
    transform_comp_pool_resize(transform_comp_pool, 100);

    return;
}
void transform_comp_pool_resize(Pool *tranform_comp_pool, uint16_t size_to_add) {
    uint16_t new_size = tranform_comp_pool->max_length + size_to_add;
    size_t new_memory_size = sizeof(Transform_Comp_t) * new_size;

    tranform_comp_pool->data = MemRealloc(tranform_comp_pool->data, new_memory_size);

    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) tranform_comp_pool->data;
    for (int i=tranform_comp_pool->current_length; i<tranform_comp_pool->max_length; i++) {
        transform_comp_data[i] =  (Transform_Comp_t) {0};
    }

    tranform_comp_pool->max_length = new_size;

    return;
}
void tranform_comp_set_to_pool(Pool *tranform_comp_pool, uint16_t entt_id, Transform_Comp_t transform_comp) {
    if (entt_id > tranform_comp_pool->max_length) {
        transform_comp_pool_resize(tranform_comp_pool, 100);
    }
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) tranform_comp_pool->data;
    transform_comp_data[entt_id] = transform_comp;

    return;
}
Transform_Comp_t *transform_comp_get_from_pool(Pool *tranform_comp_pool, uint16_t entt_id) {
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) tranform_comp_pool->data;

    return &transform_comp_data[entt_id];
}
void transform_comp_remove_from_pool(Pool *tranform_comp_pool, uint16_t entt_id) {
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) tranform_comp_pool->data;
    transform_comp_data[entt_id] = (Transform_Comp_t) {0};

    return;
}
