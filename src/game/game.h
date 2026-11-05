#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"


static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

static const int FPS = 60;

typedef struct Game_Entts_t Game_Entts_t;

typedef struct Game_t {
    Registry_t *registry;
    bool is_running;
    Vector2 screen_size;
    char *title;

    Game_Entts_t *game_entts;
} Game_t;


Game_t *init_game(void);
void run_game(Game_t *game);
void destroy_game(Game_t *game);

void process_input(Game_t *game);
void update_game(Game_t *game, float dt);
void render_game(Game_t *game);
void setup_game(Game_t *game);
