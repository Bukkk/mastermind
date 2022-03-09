#pragma once

#include "../mastermind.h"
#include "heuristics_data.h"


static inline bool response_t__equals(const response_t* const a, const response_t* const b)
{
    return a->red == b->red && a->white == b->white;
}

response_t response_from_pattern(pattern_t real_pattern, pattern_t guessed_pattern);

pattern_t choose_next_pattern(gamestate_t* gamestate, heuristcs_data_t* heuristics_data);

void sieve_impossible_patterns(
    heuristcs_data_t* const data, 
    const pattern_t guessed_pattern, 
    const response_t response);
