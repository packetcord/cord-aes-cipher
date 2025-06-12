//
// aes_helpers.h
//

#include "aes_cipher.h"

void print_expanded_key(uint8_t expanded_key[Nb][AES_WORDS]);
uint8_t round_const(uint8_t ri);
void generate_round_constants(uint8_t *rc_array, uint8_t nth_constant);
void print_round_key_column_major(uint8_t key_matrix[4][AES_WORDS], uint8_t round);
void print_round_key_row_major(uint8_t key_matrix[4][AES_WORDS], uint8_t round);
