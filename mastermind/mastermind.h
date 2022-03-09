// pomysl: 
// ze zbioru wszystkich mozliwych stanow odpowiedzi filtruj po kolei te ktore nie dadza tej samej odpowiedzi co uzytkownik

#pragma once

#include <stdbool.h>
#include <stdint.h>

// kolorowy wzor
#define PATTERN_LENGTH 4
#define PATTERN_COLORS 6
#define TURN_COUNT 8

typedef struct {
    uint8_t color_at_position[PATTERN_LENGTH];
} pattern_t;

// informacja zwrotna ilosci trafien z miejscem i bez miejsca
typedef struct {
    uint8_t red; // trafiony kolor i miejsce
    uint8_t white; // trafiony kolor ale w blednym miejscu
} response_t;

typedef struct {
    pattern_t pattern;
    response_t response;
} turn_t;

typedef struct {
    turn_t turns[TURN_COUNT];
    uint8_t current_turn;
} gamestate_t;

void decoder_algorithm(
    gamestate_t* gamestate,
    response_t (*get_response)(gamestate_t*),
    void (*on_decoder_wins)(gamestate_t*),
    void (*on_decoder_loses)(gamestate_t*),
    void (*on_player_cheats)(gamestate_t*));

static inline bool response_t__is_valid(const response_t* const response)
{
    return response->red <= PATTERN_LENGTH && 
        response->white <= PATTERN_LENGTH && 
        (response->white + response->red) <= PATTERN_LENGTH;
}

static inline bool pattern_t__is_valid(const pattern_t* const response)
{
    for (uint32_t i = 0; i < PATTERN_LENGTH; ++i) {
        if (response->color_at_position[i] >= PATTERN_COLORS) {
            return false;
        }
    }

    return true;
}
