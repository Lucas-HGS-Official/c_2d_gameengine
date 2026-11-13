#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"
#include "assets_manager.h"


typedef enum LEVELS {
    NUM_LVLS,
} LEVELS ;

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

static const int FPS = 60;

typedef struct Game_Entts_t Game_Entts_t;

typedef struct Game_t {
    Game_Entts_t *game_entts;
    Registry_t *registry;
    AssetsManager_t *assets_manager;
    char *title;
    bool is_running;
    Vector2 screen_size;

} Game_t;


Game_t *init_game(void);
void run_game(Game_t *game);
void destroy_game(Game_t *game);

void process_input(Game_t *game);
void update_game(Game_t *game, float dt);
void render_game(Game_t *game);
void setup_game(Game_t *game);

void game_load_lvl(Game_t *game, LEVELS lvl_to_load);
