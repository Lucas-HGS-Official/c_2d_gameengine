#include <stdlib.h>
#include <stdbool.h>

#include <raylib.h>
#include <raymath.h>

#include "lua/lua.h"
#include "lua/lualib.h"
#include "lua/lauxlib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui/raygui.h"

#include "game.h"


int main() {
    Game *game = NULL;

    init_game(game);

    run_game(game);

    destroy_game(game);

    return 0;
}
