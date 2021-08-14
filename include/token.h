#ifndef TOKEN_H
#define TOKEN_H

typedef struct TOKEN_STRUCT
{
    char* value;
    enum
    {
        TOKEN_ID,           // Identifier
        TOKEN_EQUALS,       // =
        TOKEN_LPAREN,       // (
        TOKEN_RPAREN,       // )
        TOKEN_LBRACE,       // {
        TOKEN_RBRACE,       // }
        TOKEN_COLON,        // :
        TOKEN_COMMA,        // ,
        TOKEN_LT,           // <
        TOKEN_GT,           // >
        TOKEN_ARROW_RIGHT,  // ->
        TOKEN_INT,          // Integer
        TOKEN_SEMICOLON,    // ;
        TOKEN_EOF,          // End of file
    } type;
} token_T;

token_T* init_token(char* value, int type);

char* token_to_string(token_T* token);

#endif // TOKEN_H