#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"


#define SLOTS_TO_ADD 100


#define RESIZE_COMP_POOL(component_type, component_pool, size_to_add) \
    uint16_t old_length = component_pool->length; \
    uint16_t new_size = old_length + size_to_add; \
    size_t new_memory_size = sizeof(component_type) * new_size; \
    component_pool->data = MemRealloc(component_pool->data, new_memory_size); \
    component_pool->length = new_size; \
    component_type *component_pool_data = (component_type*) component_pool->data; \
    for (int i=old_length; i<component_pool->length; i++) { \
        component_pool_data[i] =  (component_type) {0}; \
    } \
    component_pool->length = new_size; \
    log_info("component pool new size: %i", new_size); \


#define SET_COMP_TO_POOL(component_type, component_pool, entt_id, component, resize_function_name) \
    if (entt_id >= component_pool->length) { \
        resize_function_name(component_pool, SLOTS_TO_ADD); \
    } \
    component_type *component_pool_data = (component_type*) component_pool->data; \
    component_pool_data[entt_id] = component; \
    log_info("set component for entity %i", entt_id); \


// Transform_Comp_t *transform_comp_get_from_pool(Pool *transform_comp_pool, uint16_t entt_id) {
//     Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) transform_comp_pool->data;
//     log_info("get transform comp from entity %i", entt_id);
//
//     return &transform_comp_data[entt_id];
// }
// void transform_comp_remove_from_pool(Pool *transform_comp_pool, uint16_t entt_id) {
//     Transform_Comp_t *transform_comp_data = (Transform_Comp_t*) transform_comp_pool->data;
//     transform_comp_data[entt_id] = (Transform_Comp_t) {0};
//     log_info("remove transform comp from entity %i", entt_id);
//
//     return;
// }
