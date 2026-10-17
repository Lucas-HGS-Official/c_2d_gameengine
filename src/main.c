#include <raylib.h>

#include "game/game.h"


int main() {
    Game_t *game = init_game();
    run_game(game);
    destroy_game(game);

    return 0;
}
