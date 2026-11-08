#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"


#define SLOTS_TO_ADD 100


#define RESIZE_COMP_POOL(component_type, component_pool, size_to_add) \
    int16_t old_length = component_pool->length; \
    int16_t new_size = old_length + size_to_add; \
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
    component_type *component_pool_data = (component_type *) component_pool->data; \
    component_pool_data[entt_id] = *(component_type *)component; \
    log_info("set component for entity %i", entt_id); \


#define GET_COMP_FROM_POOL(component_type, component_pool, entt_id, returned_component_pointer) \
    component_type *component_pool_data = (component_type*) component_pool->data; \
    log_info("get component from entity %i", entt_id); \
    returned_component_pointer = (void *) &component_pool_data[entt_id]; \


#define REMOVE_COMP_FROM_POOL(component_type, component_pool, entt_id) \
    component_type *component_pool_data = (component_type*) component_pool->data; \
    component_pool_data[entt_id] = (component_type) {0}; \
    log_info("remove component from entity %i", entt_id); \
