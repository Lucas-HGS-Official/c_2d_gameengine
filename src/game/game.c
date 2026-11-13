#include "game.h"

#include <stdbool.h>
#include <stdint.h>

#include <raylib.h>
#include <raymath.h>
#include "log_dot_c/log.h"

#include "../ECS/ECS.h"
#include "assets_manager.h"

#include "movement_system.h"
#include "render_system.h"
#include "rigidbody_comp.h"
#include "sprite_comp.h"
#include "transform_comp.h"


struct Game_Entts_t {
    int16_t tank;
    int16_t truck;

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

    game->registry = init_registry();
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
    if (game->registry != NULL) {
        destroy_registry(game->registry);
    }
    if (game->game_entts->is_game_entts_initialized) {
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
    System_t *systems = game->registry->systems_list;
    movement_system_update(&systems[MOVEMENT_SYS], game->registry, dt);

    registry_update(game->registry);

    return;
}
void render_game(Game_t *game) {
    System_t *systems = game->registry->systems_list;
    BeginDrawing();

        ClearBackground(RAYWHITE);

        render_system_update(&systems[RENDER_SYSTEM], game->registry, game->assets_manager);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    return;
}


void setup_game(Game_t *game) {
    game_load_lvl(game, 0);

    return;
}

void game_load_lvl(Game_t *game, LEVELS lvl_to_load) {
    AssetsManager_t *assets_manager = game->assets_manager;
    Registry_t *registry = game->registry;
    Game_Entts_t *entts = game->game_entts;


    assets_manager_add_texture(assets_manager, "assets/images/tank-panther-right.png", TANK_PANTHER_RIGHT_TEXTURE);


    Transform_Comp_t tank_transform = {
        .position = (Vector2) { .x=10, .y=30 },
        .rotation = 0.f,
        .scale = 1.f,
    };
    RigidBody_Comp_t tank_rigidbody = {
        .velocity = (Vector2) { .x=10, .y=50 },
    };
    Sprite_Comp_t tank_sprite = {
        .texture_id = TANK_PANTHER_RIGHT_TEXTURE,
        .heigt = 32,
        .width = 32,
    };
    entts->tank = registry_create_entity(registry);
    registry_set_component_to_entity(registry, entts->tank, TRANSFORM_COMP, &tank_transform);
    registry_set_component_to_entity(registry, entts->tank, RIGIDBODY_COMP, &tank_rigidbody);
    registry_set_component_to_entity(registry, entts->tank, SPRITE_COMP, &tank_sprite);

    entts->truck = registry_create_entity(registry);
    registry_set_component_to_entity(registry, entts->truck, TRANSFORM_COMP, &(Transform_Comp_t) {0});
    registry_set_component_to_entity(registry, entts->truck, SPRITE_COMP, &(Sprite_Comp_t) { 0, 100, 100 });

    return;
}
