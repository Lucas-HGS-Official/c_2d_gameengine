#pragma once

#include <raylib.h>
#include <raymath.h>

typedef struct Game {
    Vector2 screen_size;
    char *title;
} Game;

void init_game(Game *game);
void run_game(Game *game);
void destroy_game(Game *game);

void process_input(Game *game);
void update_game(Game *game);
void render_game(Game *game);
