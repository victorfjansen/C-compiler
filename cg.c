#include "defs.h"
#include "decl.h"
#include "data.h"

// code generator in x86-64

// list of available registers and  their names
// eax, ebx, ecx, edx

static int freeReg[4];
static char *regList[4]= { "%r8", "%r9", "%r10", "%r11" };

// set all registers as available
void freeAllRegisters(void) {
    freeReg[0] = freeReg[1] = freeReg[2] = freeReg[3] = 1;
}

// Allocate a free register. Return a number of
// the register. Die if no available registers
static int allocRegister(void) {
    for(int i=0; i<4; i++) {
        if(freeReg[i]) {
            freeReg[i] = 0;
            return i;
        }
    }
    fprintf(stderr, "Out of registers!\n");
    exit(1);
}

static void freeRegister(int reg) {
    if(freeReg[reg] != 0) {
        fprintf(stderr, "Error trying to free register %d\n", reg);
        exit(1);
    }
    freeReg[reg] = 1;
}

// Print out the assembly preamble
void cgpreamble() {
    freeAllRegisters();
    fputs(
            "\t.text\n"
            "   .LC0:\n"
            "\t.string\t\"%d\\n\"\n"
            "printint:\n"
            "\tpushq\t%rbp\n"
            "\tmovq\t%rsp, %rbp\n"
            "\tsubq\t$16, %rsp\n"
            "\tmovl\t%edi, -4(%rbp)\n"
            "\tmovl\t-4(%rbp), %eax\n"
            "\tmovl\t%eax, %esi\n"
            "\tleaq	.LC0(%rip), %rdi\n"
            "\tmovl	$0, %eax\n"
            "\tcall	printf@PLT\n"
            "\tnop\n"
            "\tleave\n"
            "\tret\n"
            "\n"
            "\t.globl\tmain\n"
            "\t.type\tmain, @function\n"
            "main:\n"
            "\tpushq\t%rbp\n"
            "\tmovq	%rsp, %rbp\n",
            Outfile);
}

// Print out the assembly postamble
void cgpostamble()
{
    fputs(
            "\tmovl	$0, %eax\n"
            "\tpopq	%rbp\n"
            "\tret\n",
            Outfile);
}

// Load an integer literal value into a register.
// Return the number of the register
int cgload(int value) {

    // Get a new register
    int r = allocRegister();

    // Print out the code to initialise it
    fprintf(Outfile, "\tmovq\t$%d, %s\n", value, regList[r]);
    return(r);
}

// Add two registers together and return
// the number of the register with the result
int cgadd(int r1, int r2) {
    fprintf(Outfile, "\taddq\t%s, %s\n", regList[r1], regList[r2]);
    freeRegister(r1);
    return(r2);
}

// Subtract the second register from the first and
// return the number of the register with the result
int cgsub(int r1, int r2) {
    fprintf(Outfile, "\tsubq\t%s, %s\n", regList[r2], regList[r1]);
    freeRegister(r2);
    return(r1);
}

// Multiply two registers together and return
// the number of the register with the result
int cgmul(int r1, int r2) {
    fprintf(Outfile, "\timulq\t%s, %s\n", regList[r1], regList[r2]);
    freeRegister(r1);
    return(r2);
}

// Divide the first register by the second and
// return the number of the register with the result
int cgdiv(int r1, int r2) {
    fprintf(Outfile, "\tmovq\t%s,%%rax\n", regList[r1]);
    fprintf(Outfile, "\tcqo\n");
    fprintf(Outfile, "\tidivq\t%s\n", regList[r2]);
    fprintf(Outfile, "\tmovq\t%%rax,%s\n", regList[r1]);
    freeRegister(r2);
    return(r1);
}

// Call printint() with the given register
void cgprintint(int r) {
    fprintf(Outfile, "\tmovq\t%s, %%rdi\n", regList[r]);
    fprintf(Outfile, "\tcall\tprintint\n");
    freeRegister(r);
}

