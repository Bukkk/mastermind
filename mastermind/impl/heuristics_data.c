#include "heuristics_data.h"

#include <stdlib.h>

static uint32_t ipow(uint32_t base, uint32_t exponent)
{
    if (exponent == 0) {
        return 1;
    }

    // if (exponent == 1) {
    //     return base;
    // }
    // return (exponent % 2) ? base * ipow(base, exponent - 1) : ipow(base * base, exponent / 2);

    uint32_t rest = 1;
    while (exponent != 1) {
        if (exponent % 2) {
            rest *= base;
            exponent -= 1;
        }
        else {
            base *= base;
            exponent /= 2;
        }
    }

    return base * rest;
}

#include <stdio.h> // TODO: tylko do wypisania niezaimplementowania potem wywal
heuristcs_data_t heuristics_data__construct(const gamestate_t* const gamestate)
{
    if (gamestate->current_turn != 0) {
        // TODO: na razie nie implementuje stworzenia z niepusutego w czesci zagranego stanu gry
        perror("heuristics_data__construct\n");
        exit(1);
    }

    uint32_t capacity = ipow(PATTERN_COLORS, PATTERN_LENGTH);
    uint32_t size = capacity;
    pattern_t* patterns = (pattern_t*) malloc(sizeof(pattern_t) * capacity);

    patterns[0] = (pattern_t){0};
    for (uint32_t permutation_index = 1; permutation_index < capacity; ++permutation_index) {
        patterns[permutation_index] = patterns[permutation_index - 1];

        uint32_t digit = 0;
        while (true) {
            uint32_t color_if_increased = patterns[permutation_index].color_at_position[digit] + 1;
            if (color_if_increased < PATTERN_COLORS) {
                patterns[permutation_index].color_at_position[digit] = color_if_increased;
                break;
            }
            else {
                patterns[permutation_index].color_at_position[digit] = 0;
                ++digit;
            }
        }
    }

    return (heuristcs_data_t){patterns, size, capacity};
}

void heuristics_data__destruct(heuristcs_data_t* const data)
{
    free(data->possible_patterns);
}
