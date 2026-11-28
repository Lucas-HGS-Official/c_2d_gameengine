#pragma once

#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "../ECS/ECS.h"
#include "assets_manager.h"


typedef enum TEXTURES_E {
    TANK_PANTHER_RIGHT_TEXTURE,
    TILESET_TEXTURE,
    CHOPPER_SPRITESHEET_TEXTURE,
    RADAR_SPRITESHEET_TEXTURE,
    TRUCK_FORD_LEFT_TEXTURE,

    NUM_TEXTURES,
} TEXTURES_E;

typedef enum COMPONENTS_E {
    LOGGING_COMP,
    TRANSFORM_COMP,
    RIGIDBODY_COMP,
    SPRITE_COMP,
    ANIMATION_COMP,
    BOXCOLLIDER_COMP,

    NUM_COMPONENTS,
} COMPONENTS_E;

typedef enum SYSTEMS_E {
    MOVEMENT_SYS,
    RENDER_SYS,
    ANIMATION_SYS,
    COLLISION_SYS,
    RENDERCOLLIDER_SYS,

    NUM_SYSTEMS,
} SYSTEMS_E;

typedef enum LEVELS_E {
    NUM_LVLS,
} LEVELS_E ;

static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 600;

static const int FPS = 60;

typedef struct Game_Entts_t Game_Entts_t;

typedef struct Game_t {
    Game_Entts_t *game_entts;
    World_t *world;
    AssetsManager_t *assets_manager;
    char *title;
    bool is_running;
    bool is_debugging;
    Vector2 screen_size;

} Game_t;


Game_t *init_game(void);
void run_game(Game_t *game);
void destroy_game(Game_t *game);

void process_input(Game_t *game);
void update_game(Game_t *game, float dt);
void render_game(Game_t *game);
void setup_game(Game_t *game);

void game_load_lvl(Game_t *game, LEVELS_E lvl_to_load);
