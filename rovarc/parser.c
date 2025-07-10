#include "parser.h"
#include "lexer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Helper: create AST node
ASTNode* make_ast_node(ASTNodeType type, const char* value, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    node->value = value ? strdup(value) : NULL;
    node->left = left;
    node->right = right;
    return node;
}

// Free AST
void free_ast(ASTNode* node) {
    if (!node) return;
    if (node->value) free(node->value);
    free_ast(node->left);
    free_ast(node->right);
    free(node);
}

// Free a token
void free_token(Token* t) {
    if (t->value) free(t->value);
    t->value = NULL; // Avoid dangling pointer
}

// Initialize lexer
void lexer_init(Lexer* lex, const char* src) {
    lex->src = src;
    lex->pos = 0;
    lex->line = 1;
    lex->col = 1;
}

// Parser init
void parser_init(Parser* parser, const char* src) {
    lexer_init(&parser->lexer, src);
    parser->current = lexer_next_token(&parser->lexer);
}

// Helper: advance to next token
void parser_advance(Parser* parser) {
    free_token(&parser->current);
    parser->current = lexer_next_token(&parser->lexer);
}

// Minimal parse_program: parse a number or identifier (Demo!)
ASTNode* parse_program(Parser* parser) {
    // Demo: parse a single number or identifier
    if (parser->current.type == TOKEN_NUMBER) {
        ASTNode* n = make_ast_node(AST_NUMBER, parser->current.value, NULL, NULL);
        parser_advance(parser);
        return n;
    } else if (parser->current.type == TOKEN_IDENTIFIER) {
        ASTNode* n = make_ast_node(AST_IDENTIFIER, parser->current.value, NULL, NULL);
        parser_advance(parser);
        return n;
    }
    // TODO: Mehr Grammatikregeln ergänzen
    return NULL;
}

// Optional: Debug-Ausgabe für AST
void print_ast(ASTNode* node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    printf("Node type %d, value '%s'\n", node->type, node->value ? node->value : "");
    print_ast(node->left, indent+1);
    print_ast(node->right, indent+1);
}