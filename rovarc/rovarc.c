/*
 * Rovar Compiler
 * Copyright (c) 2025 <Dogwalker-kryt>
 *
 * This file is part of the Rovar compiler project and is licensed under the MIT License.
 * See the LICENSE file in the project root for more information.
 */

// rovarc.c - maincompiler für Rovar
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "semantic_analysis.h"

// Suche nach fn main im AST (sehr einfach, für Demo)
int ast_has_main(ASTNode* node) {
    if (!node) return 0;
    if (node->type == AST_IDENTIFIER && node->value && strcmp(node->value, "main") == 0) return 1;
    return ast_has_main(node->left) || ast_has_main(node->right);
}

// Dummy-Codegenerator (Platzhalter)
void codegen(ASTNode* root) {
    printf("[Codegen] (Platzhalter)\n");
    // TODO: Echten Maschinencode generieren
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <source.rov>\n", argv[0]);
        return 1;
    }
    // Datei einlesen
    FILE* f = fopen(argv[1], "r");
    if (!f) { perror("fopen"); return 1; }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* src = (char*)malloc(len+1);
    fread(src, 1, len, f); src[len] = '\0';
    fclose(f);

    // Kompilierpipeline
    Parser parser;
    parser_init(&parser, src);
    ASTNode* ast = parse_program(&parser);
    if (!ast) { printf("Parse error!\n"); free(src); return 1; }

    SemanticError* err = semantic_analyze(ast);
    if (err) {
        printf("Semantic error: %s (line %d, col %d)\n", err->message, err->line, err->col);
        free_semantic_error(err);
        free_ast(ast); free(src); return 1;
    }

    // Suche nach main
    if (!ast_has_main(ast)) {
        printf("Error: No 'main' function found!\n");
        free_ast(ast); free(src); return 1;
    }

    // Codegenerierung (Platzhalter)
    codegen(ast);

    free_ast(ast);
    free(src);
    printf("Compile OK.\n");
    return 0;
}
