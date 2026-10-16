#include <raylib.h>

#include "game/game.h"


int main() {
    Game_t *game = (Game_t*)MemAlloc(sizeof(Game_t));

    init_game(game);
    run_game(game);
    destroy_game(game);

    return 0;
}
