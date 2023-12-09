#include "defs.h"
#include "decl.h"
#include "data.h"

int arithop(int tok) {
    switch (tok) {
        case T_PLUS:
            return A_ADD;
        case T_MINUS:
            return A_SUBTRACT;
        case T_SLASH:
            return A_DIVIDE;
        case T_STAR:
            return A_MULTIPLY;
        case T_INT_LITERAL:
            return A_INT_LITERAL;
        default:
            fprintf(stderr, "Unknown token in arithop() on Line %d\n", Line);
            exit(1);
    }
}

static struct ASTnode *primary(void) {
    struct ASTnode *node;

    switch (Token.token) {
        case T_INT_LITERAL:
            node = mkastleaf(A_INT_LITERAL, Token.intValue);
            scan(&Token);
            return node;
        default:
            fprintf(stderr, "Syntax error on line %d\n", Line);
            exit(1);
    }
}

struct ASTnode *binexpr(void) {
    struct ASTnode *n, *left, *right;
    int nodetype;

    left = primary();

    if(Token.token == T_EOF)
        return left;

    nodetype = arithop(Token.token);

    scan(&Token);

    right = binexpr();

    n = mkastnode(nodetype, left, right, 0);
    return  n;
}