#include "animation_system.h"

#include <stdint.h>

#include "animation_comp.h"
#include "log_dot_c/log.h"

#include "ECS.h"
#include "logging_comp.h"
#include "sprite_comp.h"


System_t init_animation_system() {
    COMPONENT comp_arr[3]={LOGGING_COMP, SPRITE_COMP, ANIMATION_COMP};
    System_t new_animation_system = system_create_system(comp_arr, 3);
    log_info("animation system initialized");

    return new_animation_system;
}
void animation_system_update(System_t *animation_system, Registry_t *registry, float dt) {
    ComponentPool_t *logging_pool = &registry->component_pools[LOGGING_COMP];
    ComponentPool_t *sprite_pool = &registry->component_pools[SPRITE_COMP];
    ComponentPool_t *animation_pool = &registry->component_pools[ANIMATION_COMP];
    Logging_Comp_t *logging_entt = NULL;
    Sprite_Comp_t *sprite_entt = NULL;
    Animation_Comp_t *animation_entt = NULL;
    void *temp_comp = NULL;

    for (int16_t i=0; i<animation_system->entities.length; i++) {
        int16_t entt_id = animation_system->entities.id_list[i];

        temp_comp = logging_pool->get_comp(logging_pool, entt_id);
        logging_entt = (Logging_Comp_t *)temp_comp;

        temp_comp = sprite_pool->get_comp(sprite_pool, entt_id);
        sprite_entt = (Sprite_Comp_t *)temp_comp;

        temp_comp = animation_pool->get_comp(animation_pool, entt_id);
        animation_entt = (Animation_Comp_t *)temp_comp;

        if (animation_entt->current_frame >= animation_entt->num_frames) {
            animation_entt->current_frame = 0;
        }
        if (animation_entt->timer < 0.f) {
            animation_entt->timer = animation_entt->frame_time;
            animation_entt->current_frame++;
        }
        animation_entt->timer -= dt;

        sprite_entt->rec.x = sprite_entt->rec.width * animation_entt->current_frame;

        if (*logging_entt) {

        }
    }
}
