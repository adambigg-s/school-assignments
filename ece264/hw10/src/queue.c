#include <stdint.h>
#include <stdlib.h>

#include "linked_list.h"
#include "queue.h"
#include "tile_game.h"

struct Queue queue_new() {
    struct Queue output = {.data = linkedlist_new()};
    return output;
}

void enqueue(struct Queue *queue, struct GameState state) {
    uint64_t serialized = serialize(state);
    insert_at_tail(&queue->data, serialized);
}

struct GameState dequeue(struct Queue *queue) {
    uint64_t serialized = remove_from_head(&queue->data);
    return deserialize(serialized);
}

bool queue_is_empty(struct Queue *queue) { return queue->data.head == NULL; }

void free_queue(struct Queue *queue) { free_list(&queue->data); }

typedef struct Visited {
    int count;
    int capacity;
    uint64_t *visited;
} Visited;

Visited visited_new() {
    int capacity = 500000;
    uint64_t *visited = malloc(capacity * sizeof(uint64_t));
    Visited output = {.count = 0, .capacity = capacity, visited = visited};
    return output;
}

bool visited_seen(Visited *visited, uint64_t state) {
    for (int i = 0; i < visited->count; i += 1) {
        if (visited->visited[i] == state) {
            return true;
        }
    }
    return false;
}

void visited_add(Visited *visited, uint64_t state) {
    if (visited->count >= visited->capacity) {
        printf("breaking at visited_add: stack blown");
        exit(100);
        return;
    }

    visited->visited[visited->count] = state;
    visited->count += 1;
}

void free_visited(Visited *visited) { free(visited->visited); }

int number_of_moves(struct GameState start) {
    print_gamestate(start);

    struct GameState solved_gamestate = {
        .tiles = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 0}},
        .empty_row = 3,
        .empty_col = 3,
        .num_steps = 0};
    uint64_t solved = serialize(solved_gamestate);

    if (serialize(start) == solved) {
        return start.num_steps;
    }
    Visited visited = visited_new();
    visited_add(&visited, serialize(start));

    struct Queue queue = queue_new();
    enqueue(&queue, start);
    while (!queue_is_empty(&queue)) {
        struct GameState current = dequeue(&queue);

        struct GameState dequeued_check_state = current;
        dequeued_check_state.num_steps = 0;
        dequeued_check_state.empty_col = 3;
        dequeued_check_state.empty_row = 3;
        if (solved == serialize(dequeued_check_state)) {
            free_queue(&queue);
            free_visited(&visited);
            printf("visited cache size: %d", visited.count);
            return current.num_steps;
        }

        struct GameState next;
        if (current.empty_row < 3) {
            next = current;
            move_up(&next);
            uint64_t next_serial = serialize(next);
            if (!visited_seen(&visited, next_serial)) {
                enqueue(&queue, next);
                visited_add(&visited, next_serial);
            }
        }
        if (current.empty_row > 0) {
            next = current;
            move_down(&next);
            uint64_t next_serial = serialize(next);
            if (!visited_seen(&visited, next_serial)) {
                enqueue(&queue, next);
                visited_add(&visited, next_serial);
            }
        }
        if (current.empty_col < 3) {
            next = current;
            move_left(&next);
            uint64_t next_serial = serialize(next);
            if (!visited_seen(&visited, next_serial)) {
                enqueue(&queue, next);
                visited_add(&visited, next_serial);
            }
        }
        if (current.empty_col > 0) {
            next = current;
            move_right(&next);
            uint64_t next_serial = serialize(next);
            if (!visited_seen(&visited, next_serial)) {
                enqueue(&queue, next);
                visited_add(&visited, next_serial);
            }
        }
    }

    printf("reached a point that should never be reached...\n");
    free_queue(&queue);
    free_visited(&visited);

    return -1;
}
