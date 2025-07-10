// Minimal Rovar Lexer (machine code compiler basis)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// List of Rovar keywords (expand as needed)
const char* keywords[] = {
    "if", "else", "for", "while", "return", "fn", "void", "var", "let", "const", "dir", "break", "continue", "true", "false", "null", NULL
};

// Helper: check if string is a keyword
int is_keyword(const char* str) {
    for (int i = 0; keywords[i]; i++) {
        if (strcmp(str, keywords[i]) == 0) return 1;
    }
    return 0;
}

// Create a new token
Token make_token(TokenType type, const char* value, int line, int col) {
    Token t;
    t.type = type;
    t.value = strdup(value);
    t.line = line;
    t.col = col;
    return t;
}

// Free a token
void free_token(Token* t) {
    if (t->value) free(t->value);
}

// Initialize lexer
void lexer_init(Lexer* lex, const char* src) {
    lex->src = src;
    lex->pos = 0;
    lex->line = 1;
    lex->col = 1;
}

// Get next character
char lexer_peek(Lexer* lex) {
    return lex->src[lex->pos];
}

// Advance lexer
char lexer_advance(Lexer* lex) {
    char c = lex->src[lex->pos++];
    if (c == '\n') { lex->line++; lex->col = 1; } else { lex->col++; }
    return c;
}

// Skip whitespace
void lexer_skip_whitespace(Lexer* lex) {
    while (isspace(lexer_peek(lex))) lexer_advance(lex);
}

// Get next token (very basic, expand as needed)
Token lexer_next_token(Lexer* lex) {
    lexer_skip_whitespace(lex);
    int start_col = lex->col;
    char c = lexer_peek(lex);
    if (c == '\0') return make_token(TOKEN_EOF, "", lex->line, lex->col);
    // Identifiers/keywords
    if (isalpha(c) || c == '_') {
        char buf[256]; int i = 0;
        while (isalnum(lexer_peek(lex)) || lexer_peek(lex) == '_') {
            buf[i++] = lexer_advance(lex);
        }
        buf[i] = '\0';
        if (is_keyword(buf)) return make_token(TOKEN_KEYWORD, buf, lex->line, start_col);
        else return make_token(TOKEN_IDENTIFIER, buf, lex->line, start_col);
    }
    // Numbers
    if (isdigit(c)) {
        char buf[64]; int i = 0;
        while (isdigit(lexer_peek(lex))) {
            buf[i++] = lexer_advance(lex);
        }
        buf[i] = '\0';
        return make_token(TOKEN_NUMBER, buf, lex->line, start_col);
    }
    // Single-char tokens
    switch (c) {
        case '(': lexer_advance(lex); return make_token(TOKEN_LPAREN, "(", lex->line, start_col);
        case ')': lexer_advance(lex); return make_token(TOKEN_RPAREN, ")", lex->line, start_col);
        case '{': lexer_advance(lex); return make_token(TOKEN_LBRACE, "{", lex->line, start_col);
        case '}': lexer_advance(lex); return make_token(TOKEN_RBRACE, "}", lex->line, start_col);
        case ';': lexer_advance(lex); return make_token(TOKEN_SEMICOLON, ";", lex->line, start_col);
        case ',': lexer_advance(lex); return make_token(TOKEN_COMMA, ",", lex->line, start_col);
        // Add more as needed
    }
    // Operators (very basic)
    if (strchr("=+-*/<>!&|", c)) {
        char buf[3] = {lexer_advance(lex), '\0', '\0'};
        // Check for two-char operators (==, !=, etc.)
        if (strchr("=<>!", buf[0]) && lexer_peek(lex) == '=') {
            buf[1] = lexer_advance(lex);
        }
        return make_token(TOKEN_OPERATOR, buf, lex->line, start_col);
    }
    // Unknown/skip
    lexer_advance(lex);
    return make_token(TOKEN_UNKNOWN, "?", lex->line, start_col);
}
/*
// Example main for testing
#ifdef TEST_LEXER
int main() {
    const char* code = "var x = 42; if (x > 10) { return x; }";
    Lexer lex; lexer_init(&lex, code);
    Token t;
    do {
        t = lexer_next_token(&lex);
        printf("Token: type=%d, value='%s', line=%d, col=%d\n", t.type, t.value, t.line, t.col);
        free_token(&t);
    } while (t.type != TOKEN_EOF);
    return 0;
}
#endif
*/