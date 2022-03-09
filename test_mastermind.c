#include "mastermind/mastermind_repersentation.h"
#include "mastermind/impl/mastermind.h"

#include <stdio.h>
#include <stdint.h>

bool test_response_prediction(
    pattern_t true_pattern,
    pattern_t guessed_pattern,
    response_t predicted_response)
{
    response_t response = response_from_pattern(true_pattern, guessed_pattern);
    if (response_t__equals(&response, &predicted_response)) {
        return true;
    }

    printf("test_response_prediction blad\n");
    char buffer[32] = {0};

    pattern_t__to_string(&true_pattern, buffer, 128);
    printf("prawdziwy pattern: %s\n", buffer);

    pattern_t__to_string(&guessed_pattern, buffer, 128);
    printf("zgadywany pattern: %s\n", buffer);

    response_t__to_string(&predicted_response, buffer, 128);
    printf("przewidywana odpowiedz: %s\n", buffer);

    response_t__to_string(&response, buffer, 128);
    printf("otrzymana odpowiedz %s\n\n", buffer);
    return false;
}

int main(int argc, char** argv)
{
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){0, 0, 0, 0}, (response_t){4, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){0, 0, 0, 1}, (response_t){3, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){0, 0, 1, 0}, (response_t){3, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){0, 1, 0, 0}, (response_t){3, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){1, 0, 0, 0}, (response_t){3, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){1, 1, 0, 0}, (response_t){2, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){1, 1, 0, 1}, (response_t){1, 0});
    test_response_prediction((pattern_t){0, 0, 0, 0}, (pattern_t){1, 1, 1, 1}, (response_t){0, 0});
    test_response_prediction((pattern_t){1, 0, 0, 0}, (pattern_t){1, 0, 0, 0}, (response_t){4, 0});
    test_response_prediction((pattern_t){1, 2, 3, 0}, (pattern_t){1, 2, 3, 4}, (response_t){3, 0});
    
    test_response_prediction((pattern_t){1, 0, 0, 0}, (pattern_t){0, 1, 0, 0}, (response_t){2, 2});
    test_response_prediction((pattern_t){1, 2, 3, 4}, (pattern_t){2, 1, 4, 3}, (response_t){0, 4});
    test_response_prediction((pattern_t){1, 2, 3, 4}, (pattern_t){4, 1, 2, 3}, (response_t){0, 4});
    test_response_prediction((pattern_t){1, 2, 3, 4}, (pattern_t){4, 1, 2, 3}, (response_t){0, 4});

    test_response_prediction((pattern_t){1, 2, 3, 4}, (pattern_t){1, 2, 3, 3}, (response_t){3, 0});
    test_response_prediction((pattern_t){1, 2, 3, 3}, (pattern_t){1, 3, 3, 2}, (response_t){2, 2});
    test_response_prediction((pattern_t){1, 2, 3, 3}, (pattern_t){1, 3, 3, 4}, (response_t){2, 1});
    test_response_prediction((pattern_t){3, 3, 3, 3}, (pattern_t){1, 3, 3, 3}, (response_t){3, 0});
    test_response_prediction((pattern_t){3, 3, 3, 3}, (pattern_t){1, 3, 3, 2}, (response_t){2, 0});
    test_response_prediction((pattern_t){1, 3, 3, 3}, (pattern_t){1, 3, 3, 2}, (response_t){3, 0});
    test_response_prediction((pattern_t){1, 3, 3, 4}, (pattern_t){1, 4, 3, 3}, (response_t){2, 2});
    test_response_prediction((pattern_t){5, 5, 3, 2}, (pattern_t){1, 1, 2, 2}, (response_t){1, 0});

    // wydajae mi sie ze powinienem moc zepsuc algorytm sprawdzajacy czy tylko istnieje na innym miejscu w true rozny swojej parze
    // jezeli istnieje jeszcze jeden w guess ktory chcialby uzyc tego samego w true ale nie moge wygenerowac tego przypadku
    test_response_prediction((pattern_t){1, 3, 4, 4}, (pattern_t){3, 4, 5, 3}, (response_t){0, 2}); // udalo sie!!!
}
