#include "game.h"

#include <raylib.h>
#include <raymath.h>


void init_game(Game *game) {
    game = MemAlloc(sizeof(Game));
    game->screen_size = (Vector2) { .x=800, .y=600 };
    game->title = "raylib [core] example - basic window";

    InitWindow((int)game->screen_size.x, (int)game->screen_size.y, game->title);
    SetTargetFPS(60);

    return;
}
void run_game(Game *game) {
    while (!WindowShouldClose()) {
        render_game(game);
    }

    return;
}
void destroy_game(Game *game) {
    CloseWindow();
    MemFree(game);

    return;
}

void process_input(Game *game) {

    return;
}
void update_game(Game *game) {

    return;
}
void render_game(Game *game) {
    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    return;
}
