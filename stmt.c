#include "defs.h"
#include "decl.h"
#include "data.h"

// Parse one or more elements
void statements(void) {
    struct ASTnode *tree;
    int reg;

    while (1) {
        match(T_PRINT, "print");

        // parse the following code and
        // generate de assembly code
        tree = binexpr(0);
        reg = genAST(tree);
        genprintint(reg);
        genfreeregs();


        semi();
        if(Token.token == T_EOF)
            return;
    }
}

