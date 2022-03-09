#include "../mastermind.h"
#include "mastermind.h"

#include <stdint.h>
#include <stdio.h>


response_t response_from_pattern(pattern_t real_pattern, pattern_t guessed_pattern)
{
    uint8_t red = 0;
    uint8_t white = 0;

    for (uint8_t i = 0; i < PATTERN_LENGTH; ++i) {
        if (guessed_pattern.color_at_position[i] == real_pattern.color_at_position[i]) {
            ++red;
        }
        else {
            // 1) moge wziac jezeli istnieje taki w real ze nie pasuje do odpowiednika w guessed
            // 2) i jak go wezme to juz zaden inny nie moze wziac tego samego z real

            uint8_t same_in_real = 0;
            for (uint8_t j = 0; j < PATTERN_LENGTH; ++j) {
                if (i != j && 
                    guessed_pattern.color_at_position[i] == real_pattern.color_at_position[j] &&
                    guessed_pattern.color_at_position[j] != real_pattern.color_at_position[j]
                ) {
                    // 1)
                    ++same_in_real;
                }
            }

            // 2) rownowazne: istniejace takie same wczesniej niesparowane w guessed wziely sobie dokladnie jeden 
            // dlatego moge odjac ich ilosc od ilosci istniejacych z 1)
            uint8_t same_preceding_in_guessed = 0;
            for (uint8_t j = 0 ; j < i; ++j) {
                if (guessed_pattern.color_at_position[j] == guessed_pattern.color_at_position[i] &&
                    guessed_pattern.color_at_position[j] != real_pattern.color_at_position[j]
                ) {
                    ++same_preceding_in_guessed;
                }
            }

            if (same_in_real > same_preceding_in_guessed) {
                ++white;
            }
        }
    }

    return (response_t){red, white};
}

void sieve_impossible_patterns(
    heuristcs_data_t* const data, 
    const pattern_t guessed_pattern, 
    const response_t response)
{
    for (uint32_t i = 0; i < data->size;) {

        response_t response_if_guessed_is_pattern = response_from_pattern(data->possible_patterns[i], guessed_pattern);
        if (response_t__equals(&response_if_guessed_is_pattern, &response)) {
            ++i;
        }
        else {            
            --data->size;
            data->possible_patterns[i] = data->possible_patterns[data->size];

            // opcjonalne wyzerowanie patternu ktory przestaje byc widoczny na zawsze
            data->possible_patterns[data->size] = (pattern_t){0};
        }
    }
}

pattern_t choose_next_pattern(gamestate_t* gamestate, heuristcs_data_t* data)
{
    if (gamestate->current_turn == 0) {
        pattern_t pattern = (pattern_t){0};

        for (uint32_t i = PATTERN_LENGTH / 2; i < PATTERN_LENGTH; ++i) {
            pattern.color_at_position[i] = 1;
        }
        return pattern;
    }

    // na poczatek po prostu pierwszy mozliwy potem bede sie bawic jesli za slabo
    if (data->size > 0) {
        return data->possible_patterns[0];
    }

    return (pattern_t){0};
}

void decoder_algorithm(
    gamestate_t* gamestate,
    response_t (*on_get_response)(gamestate_t*),
    void (*on_decoder_wins)(gamestate_t*),
    void (*on_decoder_loses)(gamestate_t*),
    void (*on_player_cheats)(gamestate_t*))
{
    heuristcs_data_t data = heuristics_data__construct(gamestate);

    while(gamestate->current_turn < TURN_COUNT) {
        printf("istnieje nadal %u mozliwych odpowiedzi!\n", data.size); // niepowinno tu byc ale ciekawa informacja

        const pattern_t guessed_pattern = choose_next_pattern(gamestate, &data);
        gamestate->turns[gamestate->current_turn].pattern = guessed_pattern;
        const response_t user_response = on_get_response(gamestate);
        gamestate->turns[gamestate->current_turn].response = user_response;

        if (user_response.red == PATTERN_LENGTH) {
            on_decoder_wins(gamestate);

            heuristics_data__destruct(&data); // szczerze mowiac tutaj mozna uzyc goto
            return;
        }

        sieve_impossible_patterns(&data, guessed_pattern, user_response);
        if (data.size == 0) {
            on_player_cheats(gamestate);

            heuristics_data__destruct(&data);
            return;
        }
        ++gamestate->current_turn;
    }

    on_decoder_loses(gamestate);

    heuristics_data__destruct(&data);
    return;
}
