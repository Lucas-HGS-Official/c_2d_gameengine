#include "game.h"

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>
#include "log_dot_c/log.h"

#include "../ECS/ECS.h"


Registry_t *registry = NULL;

Game_t *init_game() {
    Game_t *game = (Game_t*)MemAlloc(sizeof(Game_t));
    game->screen_size = (Vector2) { .x=800, .y=600 };
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

    registry = init_registry();

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
    if (registry != NULL) {
        destroy_registry(registry);
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

    return;
}
