#pragma once

#include <raylib.h>

typedef enum TEXTURES {
    NUM_TEXTURES,
} TEXTURES;

typedef struct assets_manager_t {
    Texture2D textures_arr[NUM_TEXTURES];
    int textures_arr_len;

} assets_manager_t;


void clear_assets();
void add_texture(char *file_path, TEXTURES texture_id);
Texture2D *get_texture(TEXTURES texture_id);
