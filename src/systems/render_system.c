#include "render_system.h"

#include <raylib.h>
#include "log_dot_c/log.h"

#include "ECS.h"
#include "transform_comp.h"
#include "sprite_comp.h"


System_t init_render_system() {
    COMPONENT comp_arr[2]={TRANSFORM_COMP, SPRITE_COMP};
    System_t new_render_system = system_create_system(comp_arr, 2);
    log_info("render system initialized");

    return new_render_system;
}
void render_system_update(System_t *render_system,  Registry_t *registry) {
    Comp_Pool_t *transform_pool = &registry->component_pools[TRANSFORM_COMP];
    Comp_Pool_t *sprite_pool = &registry->component_pools[SPRITE_COMP];
    Transform_Comp_t *entt_transform = NULL;
    Sprite_Comp_t *entt_sprite = NULL;
    void *temp_comp = NULL;

    for (int16_t i=0; i<render_system->entities.length; i++) {
        int16_t entt_id = render_system->entities.id_list[i];

        temp_comp = transform_pool->get_comp(transform_pool, entt_id);
        entt_transform = (Transform_Comp_t *)temp_comp;

        temp_comp = sprite_pool->get_comp(sprite_pool, entt_id);
        entt_sprite = (Sprite_Comp_t *)temp_comp;

        Rectangle entt_rec = {
            .x=entt_transform->position.x,
            .y=entt_transform->position.y,
            .width=entt_sprite->width,
            .height=entt_sprite->heigt,
        };

        DrawRectangleRec(entt_rec, BLACK);
    }

    return;
}
