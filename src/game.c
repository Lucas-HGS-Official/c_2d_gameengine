#include "game.h"

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>


static bool is_running = false;


void init_game(Game_t *game) {
    game = (Game_t*)MemAlloc(sizeof(Game_t));
    game->screen_size = (Vector2) { .x=800, .y=600 };
    game->title = "raylib [core] example - basic window";

    InitWindow((int)game->screen_size.x, (int)game->screen_size.y, game->title);
    SetTargetFPS(60);

    is_running = true;

    return;
}
void run_game(Game_t *game) {
    while (is_running) {
        process_input(game);
        update_game(game);
        render_game(game);
    }

    return;
}
void destroy_game(Game_t *game) {
    CloseWindow();
    MemFree(game);

    return;
}

void process_input(Game_t *game) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        is_running = false;
    }

    return;
}
void update_game(Game_t *game) {

    return;
}
void render_game(Game_t *game) {
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    return;
}
