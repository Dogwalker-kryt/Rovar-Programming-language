#ifndef ROVAR_SEMANTIC_ANALYSIS_H
#define ROVAR_SEMANTIC_ANALYSIS_H

#include "parser.h"

// Fehlerarten (minimal)
typedef enum {
    SEMANTIC_OK = 0,
    SEMANTIC_UNDECLARED_VARIABLE,
    SEMANTIC_TYPE_ERROR,
    SEMANTIC_DUPLICATE_DECLARATION,
    SEMANTIC_UNKNOWN
} SemanticErrorType;

// Fehlerstruktur
typedef struct {
    SemanticErrorType type;
    char* message;
    int line;
    int col;
} SemanticError;

// Analysefunktion
SemanticError* semantic_analyze(ASTNode* root);
void free_semantic_error(SemanticError* err);

#endif // ROVAR_SEMANTIC_ANALYSIS_H
