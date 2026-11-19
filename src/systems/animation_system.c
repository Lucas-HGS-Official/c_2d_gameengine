#include "animation_system.h"

#include <stdint.h>

#include "animation_comp.h"
#include "log_dot_c/log.h"

#include "ECS.h"
#include "sprite_comp.h"


System_t init_animation_system() {
    COMPONENT comp_arr[2]={SPRITE_COMP, ANIMATION_COMP};
    System_t new_animation_system = system_create_system(comp_arr, 2);
    log_info("animation system initialized");

    return new_animation_system;
}
void animation_system_update(System_t *animation_system, Registry_t *registry, float dt) {
    ComponentPool_t *sprite_pool = &registry->component_pools[SPRITE_COMP];
    ComponentPool_t *animation_pool = &registry->component_pools[ANIMATION_COMP];
    Sprite_Comp_t *sprite_entt = NULL;
    Animation_Comp_t *animation_entt = NULL;
    void *temp_comp = NULL;

    for (int16_t i=0; i<animation_system->entities.length; i++) {
        int16_t entt_id = animation_system->entities.id_list[i];

        temp_comp = sprite_pool->get_comp(sprite_pool, entt_id);
        sprite_entt = (Sprite_Comp_t *)temp_comp;

        temp_comp = animation_pool->get_comp(animation_pool, entt_id);
        animation_entt = (Animation_Comp_t *)temp_comp;
    }
}
