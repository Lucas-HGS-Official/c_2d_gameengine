#include "assets_manager.h"

#include <time.h>

#include <raylib.h>


AssetsManager_t *init_assets_manager() {
    AssetsManager_t *new_assets_manager = MemAlloc(sizeof(AssetsManager_t));
    new_assets_manager = NULL;

    return new_assets_manager;
}
void destroy_assets_manager(AssetsManager_t *assets_manager);

void clear_assets();
void add_texture(char *file_path, TEXTURES texture_id);
Texture2D *get_texture(TEXTURES texture_id);
