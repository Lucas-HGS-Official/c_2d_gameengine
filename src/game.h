#pragma once

#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>


typedef struct Game_t {
    bool is_running;
    Vector2 screen_size;
    char *title;
} Game_t;


void init_game(Game_t *game);
void run_game(Game_t *game);
void destroy_game(Game_t *game);

void process_input(Game_t *game);
void update_game(Game_t *game);
void render_game(Game_t *game);
