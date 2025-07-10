// Lexer.h for Rovar
#ifndef ROVAR_LEXER_H
#define ROVAR_LEXER_H
#include <stddef.h>

// Token types
typedef enum {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_OPERATOR,
    TOKEN_KEYWORD,
    TOKEN_LPAREN, // (
    TOKEN_RPAREN, // )
    TOKEN_LBRACE, // {
    TOKEN_RBRACE, // }
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_UNKNOWN
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char* value;
    int line;
    int col;
} Token;

// Lexer structure
typedef struct {
    const char* src;
    size_t pos;
    int line;
    int col;
} Lexer;

// Lexer API
void lexer_init(Lexer* lex, const char* src);
Token lexer_next_token(Lexer* lex);
void free_token(Token* t);

#endif // ROVAR_LEXER_H