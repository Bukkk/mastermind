#include "../mastermind_repersentation.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

void pattern_t__to_string(pattern_t* pattern, char* buffer, uint32_t length)
{
    for (uint32_t digit = 0; digit < PATTERN_LENGTH; ++digit) {
        uint32_t end_position = strlen(buffer); // FIXME strnlen ma jakies problemy z niebyciem zdefiniowanym
        snprintf(buffer + end_position, length - end_position, "[%u] ", (uint32_t)pattern->color_at_position[digit] + 1);
    }
}

void response_t__to_string(response_t* response, char* buffer, uint32_t length)
{
    snprintf(buffer, length, "red: %u, white %u", (uint32_t)response->red, (uint32_t)response->white);
}
