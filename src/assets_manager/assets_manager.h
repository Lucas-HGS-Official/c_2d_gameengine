#pragma once

#include <stdbool.h>

#include <raylib.h>

typedef enum TEXTURES {
    TANK_PANTHER_RIGHT_TEXTURE,
    TILESET_TEXTURE,

    NUM_TEXTURES,
} TEXTURES;

typedef struct AssetsManager_t {
    Texture2D textures_arr[NUM_TEXTURES];
    int textures_arr_len;

    bool is_assets_manager_initialized;
} AssetsManager_t;


AssetsManager_t *init_assets_manager();
void destroy_assets_manager(AssetsManager_t *assets_manager);

void assets_manager_clear_assets(AssetsManager_t *assets_manager);
void assets_manager_add_texture(AssetsManager_t *assets_manager, char *file_path, TEXTURES texture_id);
Texture2D *assets_manager_get_texture(AssetsManager_t *assets_manager, TEXTURES texture_id);
