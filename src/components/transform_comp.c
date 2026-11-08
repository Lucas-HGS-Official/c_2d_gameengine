#include "transform_comp.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"

#include "base_comp.h"


void init_transform_comp_pool_data(Pool *transform_comp_pool) {
    transform_comp_pool->resize = &transform_comp_pool_resize;
    transform_comp_pool->set_comp = &transform_comp_set_to_pool;
    transform_comp_pool->get_comp = &transform_comp_get_from_pool;
    transform_comp_pool->remove_comp = &transform_comp_remove_from_pool;

    transform_comp_pool->resize(transform_comp_pool, SLOTS_TO_ADD);

    transform_comp_pool->is_pool_initialized = true;
    log_info("tranform pool initilized");

    return;
}
void transform_comp_pool_resize(Pool *transform_comp_pool, int16_t size_to_add) {
    log_info("re-sizing transform component pool");
    RESIZE_COMP_POOL(Transform_Comp_t, transform_comp_pool, size_to_add);

    return;
}
void transform_comp_set_to_pool(Pool *transform_comp_pool, int16_t entt_id, void *transform_comp) {
    SET_COMP_TO_POOL(Transform_Comp_t, transform_comp_pool, entt_id, transform_comp, transform_comp_pool_resize);

    return;
}
void *transform_comp_get_from_pool(Pool *transform_comp_pool, int16_t entt_id) {
    void *returned_component_pointer = NULL;
    GET_COMP_FROM_POOL(Transform_Comp_t, transform_comp_pool, entt_id, returned_component_pointer);

    return returned_component_pointer;
}
void transform_comp_remove_from_pool(Pool *transform_comp_pool, int16_t entt_id) {
    REMOVE_COMP_FROM_POOL(Transform_Comp_t, transform_comp_pool, entt_id);

    return;
}
