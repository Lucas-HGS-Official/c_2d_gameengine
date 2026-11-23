#include "render_system.h"

#include <stdint.h>
#include <stdlib.h>

#include <raylib.h>
#include "darray/darray.h"
#include "log_dot_c/log.h"

#include "ECS.h"
#include "../game/game.h"
#include "base_system.h"
#include "assets_manager.h"
#include "logging_comp.h"
#include "transform_comp.h"
#include "sprite_comp.h"


typedef struct Renderable_Entity {
    Logging_Comp_t *logging;
    Transform_Comp_t *transform;
    Sprite_Comp_t *sprite;
} Renderable_Entity;


static int _comp_z_index(const void * elem1, const void * elem2);

System_t init_render_system() {
    int comp_arr[3]={LOGGING_COMP, TRANSFORM_COMP, SPRITE_COMP};
    System_t new_render_system = system_create_system(comp_arr, 3);
    log_info("render system initialized");

    return new_render_system;
}
void render_system_update(System_t *render_system,  Registry_t *registry, AssetsManager_t *assets_manager) {
    Logging_Comp_t *logging_entt = NULL;
    Transform_Comp_t *transform_entt = NULL;
    Sprite_Comp_t *sprite_entt = NULL;

    Renderable_Entity *render_entt_darr = NULL;

    for (int16_t i=0; i<render_system->entities.length; i++) {
        int16_t entt_id = render_system->entities.id_list[i];

        logging_entt = SYSTEM_GET_COMP(registry, LOGGING_COMP, entt_id);
        transform_entt = SYSTEM_GET_COMP(registry, TRANSFORM_COMP, entt_id);
        sprite_entt = SYSTEM_GET_COMP(registry, SPRITE_COMP, entt_id);

        Renderable_Entity new_render_entt = {
            .logging=logging_entt,
            .transform=transform_entt,
            .sprite=sprite_entt,
        };

        darray_push(render_entt_darr, new_render_entt);
    }

    qsort(render_entt_darr, darray_size(render_entt_darr), sizeof(Renderable_Entity), _comp_z_index);

    for (int16_t i=0; i<darray_size(render_entt_darr); i++) {
        logging_entt = render_entt_darr[i].logging;
        sprite_entt = render_entt_darr[i].sprite;
        transform_entt = render_entt_darr[i].transform;

        Texture2D entt_texture = assets_manager->textures_arr[sprite_entt->texture_id];
        Rectangle entt_dest_rec = {
            .x=transform_entt->position.x,
            .y=transform_entt->position.y,
            .width=sprite_entt->rec.width * transform_entt->scale,
            .height=sprite_entt->rec.height * transform_entt->scale,
        };
        Rectangle entt_src_rec = sprite_entt->rec;

        DrawTexturePro(entt_texture, entt_src_rec, entt_dest_rec, sprite_entt->origin, transform_entt->rotation, sprite_entt->color);

        if (*logging_entt) {

        }
    }

    darray_free(render_entt_darr);

    return;
}


static int _comp_z_index(const void * elem1, const void * elem2)  {
   if (((Renderable_Entity*)elem1)->sprite == NULL || ((Renderable_Entity*)elem2)->sprite == NULL) {
       return 0;
   }

   uint32_t f = ((Renderable_Entity*)elem1)->sprite->z_index;
   uint32_t s = ((Renderable_Entity*)elem2)->sprite->z_index;

   if (f > s) return  1;
   if (f < s) return -1;
   return 0;
}
