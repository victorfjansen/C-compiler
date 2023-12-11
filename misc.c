#include "defs.h"
#include "decl.h"
#include "data.h"

void match(int t, char *what) {
    if(Token.token == t)
        scan(&Token);
    else {
        printf("%s expected on line %d\n", what, Line);
        exit(1);
    }
}

// match with a semicolon
void semi(void) {
    match(T_SEMI, ";");
}