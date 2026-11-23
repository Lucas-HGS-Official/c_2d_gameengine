#include "animation_system.h"

#include <stdint.h>

#include "animation_comp.h"
#include "log_dot_c/log.h"

#include "ECS.h"
#include "../game/game.h"
#include "base_system.h"
#include "logging_comp.h"
#include "sprite_comp.h"
#include "animation_comp.h"


System_t init_animation_system() {
    int comp_arr[3]={LOGGING_COMP, SPRITE_COMP, ANIMATION_COMP};
    System_t new_animation_system = system_create_system(comp_arr, 3);
    log_info("animation system initialized");

    return new_animation_system;
}
void animation_system_update(System_t *animation_system, Registry_t *registry, float dt) {
    for (int16_t i=0; i<animation_system->entities.length; i++) {
        int16_t entt_id = animation_system->entities.id_list[i];

        Logging_Comp_t *logging_entt = SYSTEM_GET_COMP(registry, LOGGING_COMP, entt_id);
        Sprite_Comp_t *sprite_entt = SYSTEM_GET_COMP(registry, SPRITE_COMP, entt_id);
        Animation_Comp_t *animation_entt = SYSTEM_GET_COMP(registry, ANIMATION_COMP, entt_id);

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
