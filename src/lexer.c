#include <string.h>
#include <stdlib.h>
#include <macros.h>
#include <stdio.h>
#include <ctype.h>
#include <lexer.h>

lexer_T* init_lexer(char* src)
{
    lexer_T* lexer = calloc(1, sizeof(struct LEXER_STRUCT));
    lexer->src = src;
    lexer->src_len = strlen(src);
    lexer->index = 0;
    lexer->curr_char = src[lexer->index];

    return lexer;
}

void lexer_advance(lexer_T* lexer)
{
    if (lexer->index < lexer->src_len && lexer->curr_char != '\0')
    {
        lexer->index++;
        lexer->curr_char = lexer->src[lexer->index];
    }
}

char lexer_peek(lexer_T* lexer, int offset)
{
    return lexer->src[MIN(lexer->index + offset, lexer->src_len)];
}

token_T* lexer_advance_with(lexer_T* lexer, token_T* token)
{
    lexer_advance(lexer);
    return token;
}

token_T* lexer_advance_current(lexer_T* lexer, int type)
{
    char* value = calloc(2, sizeof(char));
    value[0] = lexer->curr_char;
    value[1] = '\0';

    token_T* token = init_token(value, type);
    lexer_advance(lexer);

    return token;
}

void lexer_skip_whitespace(lexer_T* lexer)
{
    while (lexer->curr_char == 13 || lexer->curr_char == 10 || lexer->curr_char == ' ' || lexer->curr_char == '\t')
        lexer_advance(lexer);
}

token_T* lexer_parse_id(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));

    while (isalpha(lexer->curr_char))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){ lexer->curr_char, 0 });
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_ID);
}

token_T* lexer_parse_number(lexer_T* lexer)
{
    char* value = calloc(1, sizeof(char));

    while (isdigit(lexer->curr_char))
    {
        value = realloc(value, (strlen(value) + 2) * sizeof(char));
        strcat(value, (char[]){ lexer->curr_char, 0 });
        lexer_advance(lexer);
    }

    return init_token(value, TOKEN_INT);
}

token_T* lexer_next_token(lexer_T* lexer)
{
    while (lexer->curr_char != '\0')
    {
        lexer_skip_whitespace(lexer);

        if (isalpha(lexer->curr_char))
            return lexer_advance_with(lexer, lexer_parse_id(lexer));

        if (isdigit(lexer->curr_char))
            return lexer_advance_with(lexer, lexer_parse_number(lexer));

        switch (lexer->curr_char)
        {
            case '=': {
                if (lexer_peek(lexer, 1) == '>') return lexer_advance_with(lexer, init_token("=>", TOKEN_ARROW_RIGHT));
                return lexer_advance_with(lexer, init_token("=", TOKEN_EQUALS));
            } break;
            case '(': return lexer_advance_current(lexer, TOKEN_LPAREN);
            case ')': return lexer_advance_current(lexer, TOKEN_RPAREN);
            case '{': return lexer_advance_current(lexer, TOKEN_LBRACE);
            case '}': return lexer_advance_current(lexer, TOKEN_LBRACE);
            case ':': return lexer_advance_current(lexer, TOKEN_COLON);
            case ',': return lexer_advance_current(lexer, TOKEN_COMMA);
            case '<': return lexer_advance_current(lexer, TOKEN_LT);
            case '>': return lexer_advance_current(lexer, TOKEN_GT);
            case ';': return lexer_advance_current(lexer, TOKEN_SEMICOLON);
            case '\0': break;
            default:
                printf("[Lexer]: Unexpected expression `%c`\n", lexer->curr_char);
                exit(1);
        }
    }

    return init_token(0, TOKEN_EOF);
}
