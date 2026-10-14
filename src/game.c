#include "game.h"

#include <stdbool.h>
#include <stdio.h>

#include <raylib.h>
#include <raymath.h>


static Texture2D tank = {0};


void init_game(Game_t *game) {
    game->screen_size = (Vector2) { .x=800, .y=600 };
    game->title = "raylib [core] example - basic window";

    InitWindow((int)game->screen_size.x, (int)game->screen_size.y, game->title);
    SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(60);

    if (IsWindowReady()) {
        game->is_running = true;
    } else {
        printf("Raylib window not correctly initialized");
    }

    return;
}
void run_game(Game_t *game) {
    setup_game(game);
    while (game->is_running) {
        process_input(game);
        update_game(game);
        render_game(game);
    }

    return;
}
void destroy_game(Game_t *game) {
    if (IsWindowReady()) {
        UnloadTexture(tank);
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
void update_game(Game_t *game) {

    return;
}
void render_game(Game_t *game) {
    BeginDrawing();

        ClearBackground(RAYWHITE);

        Rectangle player = {
            .x=10,
            .y=10,
            .width=20,
            .height=20,
        };
        DrawRectangleRec(player, RED);

        Rectangle tank_srcrec = {
            .height=tank.height,
            .width=tank.width,
        };
        Rectangle tank_destrec = {
            .x=10, .y=10, .height=32, .width=32,
        };
        DrawTexturePro(tank, tank_srcrec, tank_destrec, (Vector2 ){0, 0}, 0, WHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    return;
}


void setup_game(Game_t *game) {
    tank = LoadTexture("./assets/images/tank-tiger-right.png");

    return;
}
