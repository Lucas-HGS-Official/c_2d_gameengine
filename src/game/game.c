#include "game.h"

#include <stdbool.h>
#include <stdint.h>

#include <raylib.h>
#include <raymath.h>
#include "darray/darray.h"
#include "log_dot_c/log.h"

#include "../ECS/ECS.h"
#include "assets_manager.h"

#include "movement_system.h"
#include "collision_system.h"
#include "render_system.h"
#include "animation_system.h"

#include "logging_comp.h"
#include "boxcollider_comp.h"
#include "animation_comp.h"
#include "rigidbody_comp.h"
#include "sprite_comp.h"
#include "transform_comp.h"


struct Game_Entts_t {
    int16_t *tile_darr;
    int16_t tank;
    int16_t truck;
    int16_t chopper;
    int16_t radar;

    bool is_game_entts_initialized;
};


Game_t *init_game() {
    Game_t *game = (Game_t*)MemAlloc(sizeof(Game_t));
    *game = (Game_t) {0};

    game->game_entts = (Game_Entts_t*)MemAlloc(sizeof(Game_Entts_t));
    *game->game_entts = (Game_Entts_t) {0};
    game->game_entts->is_game_entts_initialized = true;

    game->screen_size = (Vector2) { .x=WINDOW_WIDTH, .y=WINDOW_HEIGHT };
    game->title = "raylib [core] example - basic window";

    InitWindow((int)game->screen_size.x, (int)game->screen_size.y, game->title);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(FPS);

    if (IsWindowReady()) {
        game->is_running = true;
        log_info("Window initialized");
    } else {
        log_error("Raylib window not correctly initialized");
    }

    game->world = world_create_world();
    game->assets_manager = init_assets_manager();

    return game;
}
void run_game(Game_t *game) {
    setup_game(game);
    while (game->is_running) {
        process_input(game);
        update_game(game, GetFrameTime());
        render_game(game);
    }

    return;
}
void destroy_game(Game_t *game) {
    if (game->assets_manager != NULL) {
        destroy_assets_manager(game->assets_manager);
    }
    if (game->world != NULL) {
        destroy_world(game->world);
    }
    if (game->game_entts->is_game_entts_initialized) {
        darray_free(game->game_entts->tile_darr);
        MemFree(game->game_entts);
    }
    if (IsWindowReady()) {
        CloseWindow();
        MemFree(game);
    }

    return;
}

void process_input(Game_t *game) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        game->is_running = false;
    }

    return;
}
void update_game(Game_t *game, float dt) {
    System_t *systems = game->world->systems_darr;
    movement_system_update(&systems[MOVEMENT_SYS], game->world, dt);
    animation_system_update(&systems[ANIMATION_SYS], game->world, dt);
    collision_system_update(&systems[COLLISION_SYS], game->world);

    world_update(game->world);

    return;
}
void render_game(Game_t *game) {
    System_t *systems = game->world->systems_darr;
    BeginDrawing();

        ClearBackground(RAYWHITE);

        render_system_update(&systems[RENDER_SYS], game->world, game->assets_manager);

    EndDrawing();

    return;
}


void setup_game(Game_t *game) {
    World_t *world = game->world;

    for (COMPONENTS_E comp_type = 0; comp_type < NUM_COMPONENTS; comp_type++) {
        darray_push(world->component_pools_darr, (ComponentPool_t) {0});
        world->component_pools_darr_size++;
    }
    for (SYSTEMS_E sys_type=0; sys_type < NUM_SYSTEMS; sys_type++) {
        darray_push(world->systems_darr, (System_t) {0});
        world->systems_darr_size++;
    }

    world->component_pools_darr[LOGGING_COMP] = init_logging_comp_pool();
    world->component_pools_darr[TRANSFORM_COMP] = init_transform_comp_pool();
    world->component_pools_darr[RIGIDBODY_COMP] = init_rigidbody_comp_pool();
    world->component_pools_darr[SPRITE_COMP] = init_sprite_comp_pool();
    world->component_pools_darr[ANIMATION_COMP] = init_animation_comp_pool();
    world->component_pools_darr[BOXCOLLIDER_COMP] = init_boxcollider_comp_pool();

    world->systems_darr[MOVEMENT_SYS] = init_movement_system();
    world->systems_darr[RENDER_SYS] = init_render_system();
    world->systems_darr[ANIMATION_SYS] = init_animation_system();
    world->systems_darr[COLLISION_SYS] = init_collision_system();

    game_load_lvl(game, 0);

    return;
}

void game_load_lvl(Game_t *game, LEVELS_E lvl_to_load) {
    AssetsManager_t *assets_manager = game->assets_manager;
    World_t *world = game->world;
    Game_Entts_t *entts = game->game_entts;


    assets_manager_add_texture(assets_manager, "assets/images/tank-panther-right.png", TANK_PANTHER_RIGHT_TEXTURE);
    assets_manager_add_texture(assets_manager, "assets/images/truck-ford-left.png", TRUCK_FORD_LEFT_TEXTURE);
    assets_manager_add_texture(assets_manager, "assets/tilemaps/jungle.png", TILESET_TEXTURE);
    assets_manager_add_texture(assets_manager, "assets/images/chopper.png", CHOPPER_SPRITESHEET_TEXTURE);
    assets_manager_add_texture(assets_manager, "assets/images/radar.png", RADAR_SPRITESHEET_TEXTURE);


    Logging_Comp_t tank_log = true;
    Transform_Comp_t tank_transform = {
        .position = (Vector2) { .x=10, .y=3 },
        .rotation = 0.f,
        .scale = 1.f,
    };
    RigidBody_Comp_t tank_rigidbody = {
        .velocity = (Vector2) { .x=10, .y=0 },
    };
    Sprite_Comp_t tank_sprite = {
        .texture_id = TANK_PANTHER_RIGHT_TEXTURE,
        .rec.height = 32,
        .rec.width = 32,
        .z_index = 1,
        .color = WHITE,
    };
    BoxCollider_Comp_t tank_boxcollider = tank_sprite.rec;
    entts->tank = world_create_entity(world);
    world_set_component_to_entity(world, entts->tank, LOGGING_COMP, &tank_log);
    world_set_component_to_entity(world, entts->tank, RIGIDBODY_COMP, &tank_rigidbody);
    world_set_component_to_entity(world, entts->tank, TRANSFORM_COMP, &tank_transform);
    world_set_component_to_entity(world, entts->tank, SPRITE_COMP, &tank_sprite);
    world_set_component_to_entity(world, entts->tank, BOXCOLLIDER_COMP, &tank_boxcollider);


    Logging_Comp_t chopper_logging = true;
    Transform_Comp_t chopper_transform = {
        .position = (Vector2) { .x=10, .y=30 },
        .rotation = 0.f,
        .scale = 1.f,
    };
    RigidBody_Comp_t chopper_rigidbody = {
        .velocity = (Vector2) { .x=10, .y=50 },
    };
    Sprite_Comp_t chopper_sprite = {
        .texture_id = CHOPPER_SPRITESHEET_TEXTURE,
        .rec.height = 32,
        .rec.width = 32,
        .z_index = 1,
        .color = WHITE,
    };
    Animation_Comp_t chopper_animation = {
        .num_frames = 2,
        .frame_time = .1f,
        .is_looping = true,
        .timer = chopper_animation.frame_time,
    };
    BoxCollider_Comp_t chopper_boxcollider = chopper_sprite.rec;
    entts->chopper = world_create_entity(world);
    world_set_component_to_entity(world, entts->chopper, LOGGING_COMP, &chopper_logging);
    world_set_component_to_entity(world, entts->chopper, RIGIDBODY_COMP, &chopper_rigidbody);
    world_set_component_to_entity(world, entts->chopper, TRANSFORM_COMP, &chopper_transform);
    world_set_component_to_entity(world, entts->chopper, SPRITE_COMP, &chopper_sprite);
    world_set_component_to_entity(world, entts->chopper, ANIMATION_COMP, &chopper_animation);
    world_set_component_to_entity(world, entts->chopper, BOXCOLLIDER_COMP, &chopper_boxcollider);

    Logging_Comp_t radar_logging = true;
    Transform_Comp_t radar_transform = {
        .position = (Vector2) { .x=WINDOW_WIDTH-64 - 3, .y=3 },
        .rotation = 0.f,
        .scale = 1.f,
    };
    RigidBody_Comp_t radar_rigidbody = { 0 };
    Sprite_Comp_t radar_sprite = {
        .texture_id = RADAR_SPRITESHEET_TEXTURE,
        .rec.height = 64,
        .rec.width = 64,
        .z_index = 2,
        .color = WHITE,
    };
    Animation_Comp_t radar_animation = {
        .num_frames = 8,
        .frame_time = .05f,
        .is_looping = true,
        .timer = radar_animation.frame_time,
    };
    entts->radar = world_create_entity(world);
    world_set_component_to_entity(world, entts->radar, LOGGING_COMP, &radar_logging);
    world_set_component_to_entity(world, entts->radar, RIGIDBODY_COMP, &radar_rigidbody);
    world_set_component_to_entity(world, entts->radar, TRANSFORM_COMP, &radar_transform);
    world_set_component_to_entity(world, entts->radar, SPRITE_COMP, &radar_sprite);
    world_set_component_to_entity(world, entts->radar, ANIMATION_COMP, &radar_animation);


    int tile_size = 32;
    float tile_scale = 2.f;
    int num_cols = 25;
    int num_rows = 20;

    char *map_file = LoadFileText("assets/tilemaps/jungle.map");

    int x=0;
    int y=0;
    for (int i=0; y<num_rows && x<num_cols; i++) {
        if (map_file[i] == ',') {
            Logging_Comp_t tile_logging = false;

            int num = 0;

            num = map_file[i-2] - '0';
            int src_rec_y = num*tile_size;

            num = map_file[i-1] - '0';
            int src_rec_x = num*tile_size;

            float tile_true_size = tile_scale*tile_size;
            Transform_Comp_t tile_transform = {
                .position={ .x=x*tile_true_size, .y=y*tile_true_size },
                .rotation=0.f,
                .scale=tile_scale,
            };

            Rectangle src_rec = {
                .x=src_rec_x,
                .y=src_rec_y,
                .width=tile_size,
                .height=tile_size,
            };
            Sprite_Comp_t tile_sprite = {
                .texture_id=TILESET_TEXTURE,
                .rec = src_rec,
                .z_index = 0,
                .color = WHITE,
            };

            int16_t new_tile = world_create_entity(world);
            darray_push(entts->tile_darr, new_tile);
            world_set_component_to_entity(world, new_tile, LOGGING_COMP, &tile_logging);
            world_set_component_to_entity(world, new_tile, TRANSFORM_COMP, &tile_transform);
            world_set_component_to_entity(world, new_tile, SPRITE_COMP, &tile_sprite);

            x++;
            if (x>=num_cols-1) {
                x=0;
                y++;
            }
        }
        // log_debug("(x=%i, y=%i)", x, y);
    }

    UnloadFileText(map_file);


    Logging_Comp_t truck_log = true;
    Transform_Comp_t truck_transform = {
        .position = (Vector2) { .x=100, .y=3 },
        .scale=1.f,
    };
    Sprite_Comp_t truck_sprite = {
        .color=WHITE,
        .texture_id=TRUCK_FORD_LEFT_TEXTURE,
        .rec.height=32,
        .rec.width=32,
        .z_index=2,
    };
    RigidBody_Comp_t truck_rigidbody = {
        .velocity = (Vector2) { .x=-20, .y=0 },
    };
    BoxCollider_Comp_t truck_boxcollider = truck_sprite.rec;
    entts->truck = world_create_entity(world);
    world_set_component_to_entity(world, entts->truck, LOGGING_COMP, &truck_log);
    world_set_component_to_entity(world, entts->truck, TRANSFORM_COMP, &truck_transform);
    world_set_component_to_entity(world, entts->truck, SPRITE_COMP, &truck_sprite);
    world_set_component_to_entity(world, entts->truck, RIGIDBODY_COMP, &truck_rigidbody);
    world_set_component_to_entity(world, entts->truck, BOXCOLLIDER_COMP, &truck_boxcollider);

    return;
}
