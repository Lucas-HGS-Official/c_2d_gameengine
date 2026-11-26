#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"


#define SLOTS_TO_ADD 100

#define COMPONENT_IMPLEMENTATION(component_type, create_pool_func_name, str_component_name) \
static void comp_pool_resize(ComponentPool_t *component_pool, int16_t size_to_add); \
static void comp_set_to_pool(ComponentPool_t *component_pool, int16_t entt_id, void *comp); \
static void *comp_get_from_pool(ComponentPool_t *component_pool, int16_t entt_id); \
static void comp_remove_from_pool(ComponentPool_t *component_pool, int16_t entt_id); \
 \
ComponentPool_t create_pool_func_name(void) { \
    ComponentPool_t component_pool = {0}; \
    component_pool.resize = &comp_pool_resize; \
    component_pool.set_comp = &comp_set_to_pool; \
    component_pool.get_comp = &comp_get_from_pool; \
    component_pool.remove_comp = &comp_remove_from_pool; \
 \
    component_pool.resize(&component_pool, SLOTS_TO_ADD); \
 \
    component_pool.is_pool_initialized = true; \
    log_info("%s pool initilized", str_component_name); \
 \
    return component_pool; \
} \
\
void comp_pool_resize(ComponentPool_t *component_pool, int16_t size_to_add) { \
    log_info("re-sizing %s component pool", str_component_name); \
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
 \
    return; \
} \
void comp_set_to_pool(ComponentPool_t *component_pool, int16_t entt_id, void *component) { \
    if (entt_id >= component_pool->length) { \
        component_pool->resize(component_pool, entt_id+SLOTS_TO_ADD); \
    } \
    component_type *component_pool_data = (component_type *) component_pool->data; \
    component_pool_data[entt_id] = *(component_type *)component; \
 \
    return; \
} \
void *comp_get_from_pool(ComponentPool_t *component_pool, int16_t entt_id) { \
    void *returned_component_pointer = NULL; \
    component_type *component_pool_data = (component_type*) component_pool->data; \
    returned_component_pointer = (void *) &component_pool_data[entt_id]; \
 \
    return returned_component_pointer; \
} \
void comp_remove_from_pool(ComponentPool_t *component_pool, int16_t entt_id) { \
    component_type *component_pool_data = (component_type*) component_pool->data; \
    component_pool_data[entt_id] = (component_type) {0}; \
 \
    return; \
} \
