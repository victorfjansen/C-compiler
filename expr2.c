// Recursive mode of get tokens precedence
// "Climbing"

// Not used. Using Pratt Parser Instead

#include "defs.h"
#include "decl.h"
#include "data.h"

struct ASTnode *multiplicative_expr(void) {
    struct ASTnode *left, *right;
    int tokenType;

    left = primary();

    tokenType = Token.token;
    if(tokenType == T_EOF)
        return left;

    while (tokenType == T_STAR || tokenType == T_SLASH) {
        scan(&Token);
        right = primary();

        left = mkastnode(arithop(tokenType), left, right, 0);

        tokenType = Token.token;
        if(tokenType == T_EOF)
            break;
    }
    return left;
}

struct ASTnode *additive_expr(void) {
    struct ASTnode *left, *right;
    int tokenType;

    left =  multiplicative_expr();

    tokenType = Token.token;
    if(tokenType == T_EOF)
        return left;

    while(1) {
        scan(&Token);

        right = multiplicative_expr();

        left = mkastnode(arithop(tokenType), left, right, 0);

        tokenType = Token.token;
        if(tokenType == T_EOF)
            break;
    }

    return left;
}
