#include "rigidbody_comp.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"

#include "base_comp.h"


void init_rigidbody_comp_pool_data(Comp_Pool_t *rigidbody_comp_pool) {
    rigidbody_comp_pool->resize = &rigidbody_comp_pool_resize;
    rigidbody_comp_pool->set_comp = &rigidbody_comp_set_to_pool;
    rigidbody_comp_pool->get_comp = &rigidbody_comp_get_from_pool;
    rigidbody_comp_pool->remove_comp = &rigidbody_comp_remove_from_pool;

    rigidbody_comp_pool->resize(rigidbody_comp_pool, SLOTS_TO_ADD);

    rigidbody_comp_pool->is_pool_initialized = true;
    log_info("tranform pool initilized");

    return;
}
void rigidbody_comp_pool_resize(Comp_Pool_t *rigidbody_comp_pool, int16_t size_to_add) {
    log_info("re-sizing rigid-body component pool");
    RESIZE_COMP_POOL(RigidBody_Comp_t, rigidbody_comp_pool, size_to_add);

    return;
}
void rigidbody_comp_set_to_pool(Comp_Pool_t *rigidbody_comp_pool, int16_t entt_id, void *rigidbody_comp) {
    SET_COMP_TO_POOL(RigidBody_Comp_t, rigidbody_comp_pool, entt_id, rigidbody_comp, rigidbody_comp_pool_resize);

    return;
}
void *rigidbody_comp_get_from_pool(Comp_Pool_t *rigidbody_comp_pool, int16_t entt_id) {
    void *returned_component_pointer = NULL;
    GET_COMP_FROM_POOL(RigidBody_Comp_t, rigidbody_comp_pool, entt_id, returned_component_pointer);

    return returned_component_pointer;
}
void rigidbody_comp_remove_from_pool(Comp_Pool_t *rigidbody_comp_pool, int16_t entt_id) {
    REMOVE_COMP_FROM_POOL(RigidBody_Comp_t, rigidbody_comp_pool, entt_id);

    return;
}
