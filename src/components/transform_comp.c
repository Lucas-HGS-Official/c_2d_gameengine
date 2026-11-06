#include "transform_comp.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"

#include "base_comp.h"


void init_transform_comp_pool_data(Pool *transform_comp_pool) {
    transform_comp_pool_resize(transform_comp_pool, SLOTS_TO_ADD);
    transform_comp_pool->is_pool_initialized = true;
    log_info("tranform pool initilized");

    return;
}
void transform_comp_pool_resize(Pool *transform_comp_pool, uint16_t size_to_add) {
    log_info("re-sizing transform component pool");
    RESIZE_COMP_POOL(Transform_Comp_t, transform_comp_pool, size_to_add);

    return;
}
void transform_comp_set_to_pool(Pool *transform_comp_pool, uint16_t entt_id, Transform_Comp_t transform_comp) {
    SET_COMP_TO_POOL(Transform_Comp_t, transform_comp_pool, entt_id, transform_comp, transform_comp_pool_resize);

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
