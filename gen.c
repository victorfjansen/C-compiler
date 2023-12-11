#include "defs.h"
#include "decl.h"
#include "data.h"

// Given an AST, generate
// assembly code recursively
int genAST(struct ASTnode *n) {
    int leftReg, rightReg;

    // Get the left and right sub-tree values
    if(n->left) leftReg = genAST(n->left);
    if(n->right) rightReg = genAST(n->right);

    switch (n->op) {
        case A_ADD:  return (cgadd(leftReg, rightReg));
        case A_SUBTRACT: return (cgsub(leftReg, rightReg));
        case A_MULTIPLY: return (cgmul(leftReg, rightReg));
        case A_DIVIDE: return (cgdiv(leftReg, rightReg));
        case A_INT_LITERAL: return (cgload(n->intValue));
        default:
            fprintf(stderr, "Unknown AST operator %d\n", n->op);
            exit(1);
    }
}

void generateCode(struct ASTnode *n) {
    int reg;

    cgpreamble();
    reg = genAST(n);
    cgprintint(reg);
    cgpostamble();
}


void genpreamble() {
    cgpreamble();
}
void genpostamble() {
    cgpostamble();
}
void genfreeregs() {
    freeAllRegisters();
}
void genprintint(int reg) {
    cgprintint(reg);
}