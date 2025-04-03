#ifndef QUEUE_H_
#define QUEUE_H_

#include "linked_list.h"
#include "tile_game.h"

struct Queue {
    struct LinkedList data;
};

struct Queue queue_new();
void enqueue(struct Queue *q, struct GameState state);
struct GameState dequeue(struct Queue *q);
bool queue_empty(struct Queue *q);
int number_of_moves(struct GameState start);

#endif
