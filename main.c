#include "defs.h"
#define EXTERN_
#include "data.h"
#undef EXTERN_
#include "decl.h"
#include <errno.h>


// Compiler setup and top-level execution
// Copyright (c) 2019 Warren Toomey, GPL3

// Compiler setup and top-level execution
// Copyright (c) 2019 Warren Toomey, GPL3

// Initialise global variables
static void init() {
    Line = 1;
    Putback = '\n';
}

// Print out a usage if started incorrectly
static void usage(char *prog) {
    fprintf(stderr, "Usage: %s infile\n", prog);
    exit(1);
}

// List of printable tokens
char *tokstr[] = { "+", "-", "*", "/", "intlit" };

// Main program: check arguments and print a usage
// if we don't have an argument. Open up the input
// file and call scanfile() to scan the tokens in it.
void main(int argc, char *argv[]) {
    struct ASTnode *node;

    if (argc != 2)
        usage(argv[0]);

    init();

    if ((Infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1], strerror(errno));
        exit(1);
    }

    scan(&Token);                 // Get the first token from the input
    node = binexpr(0);                // Parse the expression in the file
    printf("%d\n", interpretAST(node));      // Calculate the final result
    exit(0);
}