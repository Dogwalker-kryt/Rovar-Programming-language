/*
 * Rovar Compiler
 * Copyright (c) 2025 <Dogwalker-kryt>
 *
 * This file is part of the Rovar compiler project and is licensed under the MIT License.
 * See the LICENSE file in the project root for more information.
 */

#include "semantic_analysis.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Hilfsfunktion: Fehler erzeugen
static SemanticError* make_semantic_error(SemanticErrorType type, const char* msg, int line, int col) {
    SemanticError* err = (SemanticError*)malloc(sizeof(SemanticError));
    err->type = type;
    err->message = msg ? strdup(msg) : NULL;
    err->line = line;
    err->col = col;
    return err;
}

void free_semantic_error(SemanticError* err) {
    if (!err) return;
    if (err->message) free(err->message);
    free(err);
}

// Minimal: Dummy-Analyse (Demo)
SemanticError* semantic_analyze(ASTNode* root) {
    if (!root) return NULL;
    // Beispiel: Fehler, wenn Identifier "foo" undeclared ist
    if (root->type == AST_IDENTIFIER && strcmp(root->value, "foo") == 0) {
        return make_semantic_error(SEMANTIC_UNDECLARED_VARIABLE, "Variable 'foo' undeclared", 0, 0);
    }
    // TODO: Symboltabelle, Typprüfung, weitere Checks
    // Rekursiv auf Kinder anwenden
    SemanticError* err = semantic_analyze(root->left);
    if (err) return err;
    return semantic_analyze(root->right);
}
