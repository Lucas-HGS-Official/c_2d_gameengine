#include "assets_manager.h"

#include <raylib.h>
#include "log_dot_c/log.h"


AssetsManager_t *init_assets_manager() {
    AssetsManager_t *new_assets_manager = MemAlloc(sizeof(AssetsManager_t));
    *new_assets_manager = (AssetsManager_t) {0};

    new_assets_manager->is_assets_manager_initialized = true;

    return new_assets_manager;
}
void destroy_assets_manager(AssetsManager_t *assets_manager) {
    if (!assets_manager->is_assets_manager_initialized) {
        log_info("assets_manager not initialized");

        return;
    }
    assets_manager_clear_assets(assets_manager);
    MemFree(assets_manager);

    return;
}
void assets_manager_clear_assets(AssetsManager_t *assets_manager) {
    for (int i=0; i<NUM_TEXTURES; i++) {
        UnloadTexture(assets_manager->textures_arr[i]);
    }

    return;
}

void assets_manager_add_texture(AssetsManager_t *assets_manager, char *file_path, TEXTURES texture_id) {
    Texture2D new_texture = LoadTexture(file_path);
    assets_manager->textures_arr[texture_id] = new_texture;
    log_info("new texture loaded with the id: %i", texture_id);

    return;
}
Texture2D *assets_manager_get_texture(AssetsManager_t *assets_manager, TEXTURES texture_id) {

    return &assets_manager->textures_arr[texture_id];
}
