#pragma once

#include <raylib.h>

typedef enum TEXTURES {
    NUM_TEXTURES,
} TEXTURES;

typedef struct AssetsManager_t {
    Texture2D textures_arr[NUM_TEXTURES];
    int textures_arr_len;

} AssetsManager_t;


AssetsManager_t *init_assets_manager();
void destroy_assets_manager(AssetsManager_t *assets_manager);

void clear_assets();
void add_texture(char *file_path, TEXTURES texture_id);
Texture2D *get_texture(TEXTURES texture_id);
