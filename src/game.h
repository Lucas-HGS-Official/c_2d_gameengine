#pragma once

typedef struct Game {

} Game;

void init_game(Game *game);
void run_game(Game *game);
void destroy_game(Game *game);

void process_input(Game *game);
void update_game(Game *game);
void render_game(Game *game);
