#include "defs.h"
#include "decl.h"
#include "data.h"

struct ASTnode *mkastnode(int op, struct ASTnode *left, struct ASTnode *right, int intValue) {
    struct ASTnode *node;

    //Malloc new ASTnode
    node = (struct ASTnode *) malloc(sizeof(struct ASTnode));
    if(node == NULL) {
        fprintf(stderr, "Unable to malloc in mkastnode\n");
        exit(1);
    }

    node->op = op;
    node->left = left;
    node->right = right;
    node->intValue = intValue;

    return node;
}

struct ASTnode *mkastleaf(int op, int intValue) {
    return mkastnode(op, NULL, NULL, intValue);
}

struct ASTnode *mkastunary(int op, struct ASTnode *left, int intValue) {
    return mkastnode(op, left, NULL, intValue);
}