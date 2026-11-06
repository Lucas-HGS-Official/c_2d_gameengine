#include "rigidbody_comp.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <raylib.h>
#include "log_dot_c/log.h"

#include "base_comp.h"


void init_rigidbody_comp_pool_data(Pool *rigidbody_comp_pool);
void rigidbody_comp_pool_resize(Pool *rigidbody_comp_pool, uint16_t size_to_add) {
    log_info("re-sizing rigid-body component pool");
    RESIZE_COMP_POOL(RigidBody_Comp_t, rigidbody_comp_pool, size_to_add);
}
void rigidbody_comp_set_to_pool(Pool *rigidbody_comp_pool, uint16_t entt_id, RigidBody_Comp_t rigidbody_comp);
RigidBody_Comp_t *rigidbody_comp_get_from_pool(Pool *rigidbody_comp_pool, uint16_t entt_id);
void rigidbody_comp_remove_from_pool(Pool *rigidbody_comp_pool, uint16_t entt_id);
