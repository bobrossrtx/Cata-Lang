#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <unistd.h>

typedef struct LEXER_STRUCT
{
    char* src;
    size_t src_len;
    char curr_char;
    unsigned int index;
} lexer_T;

lexer_T* init_lexer(char* src);

void lexer_advance(lexer_T* lexer);

char lexer_peek(lexer_T* lexer, int offset);

token_T* lexer_advance_with(lexer_T* lexer, token_T* token);

token_T* lexer_advance_current(lexer_T* lexer, int type);

void lexer_skip_whitespace(lexer_T* lexer);

token_T* lexer_parse_id(lexer_T* lexer);

token_T* lexer_parse_number(lexer_T* lexer);

token_T* lexer_next_token(lexer_T* lexer);

#endif // LEXER_H