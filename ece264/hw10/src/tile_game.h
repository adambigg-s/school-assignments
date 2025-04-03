#ifndef TILE_GAME_H_
#define TILE_GAME_H_

#include <stdint.h>
#include <stdio.h>

struct GameState {
    uint8_t tiles[4][4];
    uint8_t empty_row, empty_col;
    uint16_t num_steps;
};

uint64_t serialize(struct GameState state);
struct GameState deserialize(uint64_t state);
void move_up(struct GameState *state);
void move_down(struct GameState *state);
void move_left(struct GameState *state);
void move_right(struct GameState *state);
void print_gamestate(struct GameState current);

#endif // TILE_GAME_H_
