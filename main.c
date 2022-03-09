#include "mastermind/mastermind.h"
#include "mastermind/mastermind_repersentation.h"

#include <stdint.h>
#include <stdio.h>

response_t obtain_user_response(gamestate_t* gamestate)
{
    pattern_t pattern = gamestate->turns[gamestate->current_turn].pattern;

    char pattern_str[32] = {0};
    pattern_t__to_string(&pattern, pattern_str, 32);

    printf("%s?\n", pattern_str);

    response_t response;
    do {
        printf("    red: ");
        uint32_t red;
        scanf("%u", &red);
        printf("  white: ");
        uint32_t white;
        scanf("%u", &white);

        response = (response_t){red, white};
        if (response_t__is_valid(&response)) {
            break;
        }
        else {
            printf("  podano nieprawidlowa odpowiedz! popraw sie!!!\n");
        }
    } while (true);

    printf("\n\n");
    return response;
}

void decoder_wins(gamestate_t* gamestate)
{
    printf("I win!!!\n");
}

void decoder_loses(gamestate_t* gamestate)
{
    printf("YOU win, I lose smh :\"-( 2/10\n");
}

void player_cheats(gamestate_t* gamestate)
{
    printf("you are cheating!\n");
}

int main(int argc, char** argv)
{
    gamestate_t gamestate = {0};

    decoder_algorithm(
        &gamestate,
        obtain_user_response, 
        decoder_wins, 
        decoder_loses, 
        player_cheats);

    return 0;
}
