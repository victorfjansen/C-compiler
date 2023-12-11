#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TEXTLEN 512 // lenghts of symbol input

// Tokens
enum {
    T_EOF, T_PLUS, T_MINUS, T_STAR, T_SLASH, T_INT_LITERAL, T_PRINT, T_SEMI
};

// Token structure
struct token {
    int token;
    int intValue;
};

// Enum for AST Nodes
enum {
    A_ADD, A_SUBTRACT, A_MULTIPLY, A_DIVIDE, A_INT_LITERAL
};

struct ASTnode {
    int op;
    struct ASTnode *left;
    struct ASTnode *right;
    int intValue;
};