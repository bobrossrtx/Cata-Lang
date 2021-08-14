#include <stdlib.h>
#include <lexer.h>
#include <stdio.h>
#include <cata.h>
#include <io.h>

void cata_compile(char* src)
{
    lexer_T* lexer = init_lexer(src);
    token_T* tok = 0;

    while ((tok = lexer_next_token(lexer))->type != TOKEN_EOF)
        printf("%s\n", token_to_string(tok));
}

void cata_compile_file(const char* filename)
{
    char* src = read_file(filename);
    cata_compile(src);
    free(src);
}
