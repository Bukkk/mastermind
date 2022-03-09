#pragma once

#include "../mastermind.h"

#include <stdint.h>

typedef struct {
    pattern_t* possible_patterns;
    uint32_t size;
    uint32_t capacity;
} heuristcs_data_t;

heuristcs_data_t heuristics_data__construct(const gamestate_t*);

void heuristics_data__destruct(heuristcs_data_t* data);
