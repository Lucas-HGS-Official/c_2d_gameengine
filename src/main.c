#include <stdlib.h>

#include "game.h"


int main() {
    Game_t *game = NULL;

    init_game(game);
    run_game(game);
    destroy_game(game);

    return 0;
}
