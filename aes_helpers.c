//
// aes_helpers.c
//

#include "aes_helpers.h"

void print_expanded_key(uint8_t expanded_key[Nb][AES_WORDS])
{
    printf("uint8_t aes_expanded_key[Nb][AES_WORDS] = {");
    for (uint8_t i = 0; i < Nb; i++)
    {
        printf("{ ");
        for (uint8_t j = 0; j < AES_WORDS; j++)
        {
            printf("0x%02X", expanded_key[i][j]);
            if (j == (AES_WORDS - 1)) printf(" ");
            else printf(", ");
        }
        if (i == (Nb - 1)) printf("}");
        else printf("},\n");
    }
    printf("};");
}

uint8_t round_const(uint8_t ri)
{
    if (ri == 0) // Value [0] should never be used, RCs start from [1]
        return 0;
    else if (ri <= 1)
        return 1;
    else
        if (round_const(ri - 1) < 0x80)
            return 2 * round_const(ri - 1);
        else
            return (2 * round_const(ri - 1)) ^ 0x11B;
}

void generate_round_constants(uint8_t *rc_array, uint8_t nth_constant)
{
    for (uint8_t n = 1; n < nth_constant; n++)
        rc_array[n] = round_const(n);
    
    return;
}

void print_round_key_column_major(uint8_t key_matrix[4][AES_WORDS], uint8_t round)
{
    if (round > Nr)
        return;

    printf("Round %u key (default, column major): \n", round);
    for (uint8_t j = 4 * round; j < (4 * round) + 4; j++)
        for (uint8_t i = 0; i < 4; i++)
            printf("0x%02X\n", key_matrix[i][j]);
}

void print_round_key_row_major(uint8_t key_matrix[4][AES_WORDS], uint8_t round)
{
    if (round > Nr)
        return;

    printf("Round %u key (row major): \n", round);
    for (uint8_t i = 0; i < 4; i++)
        for (uint8_t j = 4 * round; j < (4 * round) + 4; j++)
            printf("0x%02X\n", key_matrix[i][j]);
}
