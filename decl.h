// scan.c
int scan(struct token *t);

// tree.c
struct ASTnode *mkastnode(int op, struct ASTnode *left,
                          struct ASTnode *right, int intValue);
struct ASTnode *mkastleaf(int op, int intValue);
struct ASTnode *mkastunary(int op, struct ASTnode *left, int intValue);

// gen.c
int genAST(struct ASTnode *n);
void genpreamble();
void genpostamble();
void genfreeregs();
void genprintint(int reg);

// cg.c
void freeAllRegisters(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);

// expr.c
struct ASTnode *binexpr(int ptp);

// stmt.c
void statements(void);

// misc.c
void match(int t, char *what);
void semi(void);

int interpretAST(struct ASTnode *n);
void generateCode(struct ASTnode *n);

int arithop(int tok);
struct ASTnode *primary(void);

