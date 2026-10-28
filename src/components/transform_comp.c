#include "transform_comp.h"

#include <stddef.h>
#include <stdint.h>

#include <raylib.h>


void transform_comp_pool_resize(Pool *tranform_comp_pool, uint16_t size_to_add) {
    uint16_t new_size = tranform_comp_pool->max_length + size_to_add;
    size_t new_memory_size = sizeof(Transform_Comp_t) * new_size;
    tranform_comp_pool->data = MemRealloc(tranform_comp_pool->data, new_memory_size);
    tranform_comp_pool->max_length = new_size;

    return;
}
void tranform_comp_set_to_pool(Pool *tranform_comp_pool, uint16_t entt_id, Transform_Comp_t transform_comp) {
    Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) tranform_comp_pool->data;
    transform_comp_data[entt_id] = transform_comp;

    return;
}

// void *pool_get(Pool *pool, COMPONENT pool_type, uint16_t index) {
//
//     return &pool[pool_type].data + index+pool->data_size; // TODO: Check if it works, possily need system struct offset
// }
