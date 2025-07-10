#ifndef ROVAR_PARSER_H
#define ROVAR_PARSER_H

#include "lexer.h"

// AST node types (minimal, extensible)
typedef enum {
    AST_PROGRAM,
    AST_STATEMENT,
    AST_EXPRESSION,
    AST_NUMBER,
    AST_IDENTIFIER,
    AST_BINARY_OP,
    AST_VAR_DECL,
    AST_UNKNOWN
} ASTNodeType;

// AST node structure (minimal, for demo)
typedef struct ASTNode {
    ASTNodeType type;
    char* value; // e.g. name, number, operator
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

// Parser structure
typedef struct {
    Lexer lexer;
    Token current;
} Parser;

// Parser API
void parser_init(Parser* parser, const char* src);
ASTNode* parse_program(Parser* parser);
void free_ast(ASTNode* node);

#endif // ROVAR_PARSER_H
