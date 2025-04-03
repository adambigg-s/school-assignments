#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [test file]\n", argv[0]);
        exit(1);
    }

    FILE *input;
    errno_t err = fopen_s(&input, argv[1], "r");
    if (err != 0 || input == NULL) {
        fprintf(stderr, "failed to open input file");
        exit(1);
    }

    int expected;
    fscanf_s(input, "%d", &expected);

    struct GameState start = {0};
    start.num_steps = 0;
    for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
            int value;
            fscanf_s(input, "%d", &value);
            start.tiles[i][j] = value;
            if (value == 0) {
                start.empty_row = i;
                start.empty_col = j;
            }
        }
    }
    fclose(input);

    int output = number_of_moves(start);
    if (output != expected) {
        fprintf(stderr, "Expected %d moves, got %d\n", expected, output);
        exit(3);
    }

    printf("\n\nnumber of moves we got: %d", output);
    printf("\nexpected number: %d\n", expected);

    return 0;
}
