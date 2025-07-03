// This is the first prototype of the compiler!
// Not all features are possible and usable, because the compiler translates Rovar code to C and then you have to compile it with gcc
// I am working on the native compiler

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

// Simple token types
typedef enum {
    TOKEN_PRINT,
    TOKEN_VAR,
    TOKEN_ASSIGN,
    TOKEN_INT,
    TOKEN_STR,
    TOKEN_IDENTIFIER,
    TOKEN_UNKNOWN
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char value[256];
} Token;

// Simple tokenizer function (only printf and variables)
Token tokenize_line(const char* line) {
    Token t;
    if (strncmp(line, "printf", 6) == 0) {
        t.type = TOKEN_PRINT;
        strcpy(t.value, line + 7); // Content after printf(
    } else if (strncmp(line, "var ", 4) == 0) {
        t.type = TOKEN_VAR;
        strcpy(t.value, line + 4);
    } else if (strchr(line, '=') != NULL) {
        t.type = TOKEN_ASSIGN;
        strcpy(t.value, line);
    } else {
        t.type = TOKEN_UNKNOWN;
        strcpy(t.value, line);
    }
    return t;
}

// Main function: Read, tokenize, output C code
int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input.rov> <output.c>\n", argv[0]);
        return 1;
    }
    FILE* fin = fopen(argv[1], "r");
    FILE* fout = fopen(argv[2], "w");
    if (!fin || !fout) {
        printf("Error opening files!\n");
        return 1;
    }
    fprintf(fout, "#include <stdio.h>\nint main() {\n");
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fin)) {
        // Remove newline
        line[strcspn(line, "\r\n")] = 0;
        Token t = tokenize_line(line);
        switch (t.type) {
            case TOKEN_PRINT:
                fprintf(fout, "    printf(\"%s\\n\");\n", t.value);
                break;
            case TOKEN_VAR:
                fprintf(fout, "    int %s;\n", t.value); // Only int as example
                break;
            case TOKEN_ASSIGN:
                fprintf(fout, "    %s;\n", t.value);
                break;
            default:
                // Ignore unknown line
                break;
        }
    }
    fprintf(fout, "    return 0;\n}\n");
    fclose(fin);
    fclose(fout);
    printf("Done! C code in %s\n", argv[2]);
    return 0;
}