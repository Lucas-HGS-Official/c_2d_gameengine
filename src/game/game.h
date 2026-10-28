#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>


static const int FPS = 60;
static const int MILLISECS_PER_FRAME = 1000/FPS;

typedef struct Game_t {
    bool is_running;
    Vector2 screen_size;
    char *title;
} Game_t;


Game_t *init_game(void);
void run_game(Game_t *game);
void destroy_game(Game_t *game);

void process_input(Game_t *game);
void update_game(Game_t *game, float dt);
void render_game(Game_t *game);
void setup_game(Game_t *game);
