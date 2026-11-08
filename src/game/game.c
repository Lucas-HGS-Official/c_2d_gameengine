#include "game.h"

#include <stdbool.h>
#include <stdint.h>

#include <raylib.h>
#include <raymath.h>
#include "log_dot_c/log.h"

#include "../ECS/ECS.h"
#include "rigidbody_comp.h"
#include "transform_comp.h"


struct Game_Entts_t {
    uint16_t tank;
    uint16_t truck;

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
    registry_update(game->registry);

    return;
}
void render_game(Game_t *game) {
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    return;
}


void setup_game(Game_t *game) {
    Registry_t *registry = game->registry;
    Game_Entts_t *entts = game->game_entts;


    entts->tank = registry_create_entity(registry);
    registry_set_component_to_entity(registry, entts->tank, TRANSFORM_COMP, (void *) &(Transform_Comp_t) {0});
    registry_set_component_to_entity(registry, entts->tank, RIGIDBODY_COMP, (void *) &(RigidBody_Comp_t) {0});

    entts->truck = registry_create_entity(registry);
    registry_set_component_to_entity(registry, entts->truck, TRANSFORM_COMP, &(Transform_Comp_t) {0});

    return;
}
