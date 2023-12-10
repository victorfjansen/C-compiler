#include "defs.h"
#include "decl.h"
#include "data.h"

// Pratt parse -> ordem de precedência
// EOF, +, -, *, /, Integer Literal
static int OpPrec[] = { 0, 10, 10, 20, 20, 0};

// check that we have a binary operator and
// return its precedence
static int op_precedence(int tokenType) {
    int prec = OpPrec[tokenType];
    if(prec == 0) {
        fprintf(stderr, "syntax error on line %d, token %d\n", Line, tokenType);
        exit(1);
    }
    return prec;
}


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

struct ASTnode *primary(void) {
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

// Return an AST tree whose root is a binary operator.
// Parameter ptp is the previous token's precedence.
struct ASTnode *binexpr(int ptp) {
    struct ASTnode *left, *right;
    int tokenType;

    // Get the integer literal on the left.
    // Fetch the next token at the same time.
    left = primary();

    tokenType = Token.token;
    if(tokenType == T_EOF)
        return left;

    // While the precedence of this token is
    // more than that of the previous token precedence
    while(op_precedence(tokenType) > ptp) {
        scan(&Token);

        // Recursively call binexpr() with the
        // precedence of our token to build a sub-tree
        right = binexpr(OpPrec[tokenType]);

        // Join that sub-tree with ours. Convert the token
        // into an AST operation at the same time.
        left = mkastnode(arithop(tokenType), left, right, 0);

        // Update the details of the current token.
        // If no tokens left, return just the left node
        tokenType = Token.token;
        if (tokenType == T_EOF)
            return (left);
    }
    return left;
}


