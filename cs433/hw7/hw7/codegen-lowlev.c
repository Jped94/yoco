/* codegen-lowlev.c  for CS 433 project
 *
 * code generation: low-level routines
 *
 * FILL IN for hw 7
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"


/* Debugging output for low-level code-generation functions: */
#define CODEDEBUG 1

/* Data structure (linked list) to keep track of the displacements of
 * free memory temporaries.  The global variable "availMemTemps"
 * points to the beginning of this list.
 */
typedef struct memTempStr {
    int disp;
    struct memTempStr *next;
} memTemp;

/***********************************************************************
 *  Global variables
 */

/* Register names - used to output code */
char *regname[REGCOUNT] = {
    "eax",
    "ecx",
    "edx",
    "ebx",
    "edi",
    "esi",
    "ebp",
    "esp"
};

/* A table to keep track of the status of "general" registers (eax..edi).
 * If register r is free, then regTab[r].op == NULL
 * If register r is used, then regTab[r].op points to the associated opdesc
 * Used registers can be spilled to memory or moved to other registers
 * unless regTab[r].locked == TRUE.
 * We allocate an entry for all registers, including the reserved ones (esi,
 * esp, ebp) so we don't need special cases in the code below, but of
 * course the reserved registers are never considered free.
 */
struct {
    opdesc *op;
    int locked;
} regTab[REGCOUNT];

int codeLine = 0;       /* last line number processed */

int printComma = FALSE; /* remember to print commas between arguments */

memTemp *availMemTemps = NULL;      /* list of memory temporaries */

/* Protoypes of functions defined below */
void spill(opdesc *op, regnum r);
void makeAvailable(regnum r, int line);
void freeRegs(opdesc *op);
void freeMemtemp(opdesc *op);

/***********************************************************************
 *  Operations on registers
 */

/* mark all non-reserved registers free and unlocked */
void initRegTab()
{
    // FILL IN FIRST
}

/* Lock register so it won't get moved or spilled */
void lockReg(regnum r) 
{
    // FILL IN SECOND
}

/* Unlock register */
void unlockReg(regnum r) 
{
    // FILL IN SECOND
}

/* Get the number of a free register.  If none are left, spill an unlocked
 * used register into a memory temporary.
 */
regnum getFreeRegnum() 
{
    // FILL IN FIRST
    // return first free non-reserved register (starting with eax)

    /* not enough regs - need to spill one into memtemp */
    // FILL IN THIRD
    // find the first used non-locked register r and spill its opdesc op
    // by calling spill(op, r);

    // for now, let fall through to assert(FALSE) if run out of registers

    assert(FALSE); /* should always find a register to spill... */
    return 0;
}

/***********************************************************************
 *  Operations on opdescs
 */

/* Allocate a new opdesc of type constop and value val */
opdesc *newConstOp(int val) 
{
    // FILL IN FIRST
}

/* Allocate a new opdesc of type regop and register r and update regtab[r] */
opdesc *newRegOp(regnum r) 
{
    // FILL IN FIRST
}

/* Allocate a new opdesc of type dispop, register r, displacement disp,
 * isTemp==FALSE, and update regtab[r] 
 */
opdesc *newDispOp(int disp, regnum r) 
{
    // FILL IN FIRST
}

/* Turn regop 'op' (register) into a dispop (memory location) */
void makeDispOp(opdesc *op, int disp, int isTemp) 
{
    assert(op->type == regop);
    // FILL IN FIRST
}

/* Turn dispop 'op1' (memory location) into an indexop (array location),
 * using register 'op2' as index and 's' as scale factor.  Free op2's
 * memory, but don't call freeOp(), which would also mark op'2 register
 * as free.  Instead, update regTab of op2's register to point to op1.
 */
void makeIndexOp(opdesc *op1, opdesc *op2, int s) 
{
    assert(op1->type == dispop);
    assert(op2->type == regop);
    // FILL IN FIRST
}

/* Lock 'op' by locking its register(s) */
void lock(opdesc *op)
{ 
    // FILL IN SECOND
}

/* Unlock 'op' by unlocking its register(s) */
void unlock(opdesc *op)
{ 
    // FILL IN SECOND
}

/* Force an operand to a register.  If it is a register already, just
 * return it. Otherwise, allocate a new register, output code to move
 * the operand to the register, free the old operand, and return the
 * new register.  In order to allow the operand's register(s) to be
 * reused, call freeRegs(op) before allocating a new register, but
 * don't call freeOp(op) until the end.
 */
opdesc *forceToReg(opdesc *op, int line)
{
    // FILL IN FIRST
    // use getFreeRegnum and newRegOp
}

/* Make a specific register available (used for "idivl") */
opdesc *clearSpecificReg(regnum r, int line)
{
    makeAvailable(r, line);
    return newRegOp(r);
}

/* Force an operand to a specific register (used for "idivl" and
 * returning values from functions) 
 */
opdesc *forceToSpecificReg(opdesc *op, regnum r, int line)
{
    // FILL IN SECOND

    // if it's in the correct register already, just return it

    // call makeAvailable to make r available, UNLESS op is a memloc
    // that uses this register (e.g., if op is "0(%eax)" and we want
    // eax, we want to simply output "movl 0(%eax), %eax"

    // output a movl instruction from the old op to register r

    // THEN call freeOp to free the old op, THEN call newRegOp
    // (so that register allocation table is correct; we can't call
    // freeOp earlier since the debugging output created by freeMemTemps
    // could mess things up)
    // Note that this makes outputting the new register tricky
    // in the movl instruction above (hint: use outputReg)

    // return the new regop
}

/***********************************************************************
 *  Freeing opdescs
 */

/* Mark the register(s) used by 'op' as free */
void freeRegs(opdesc *op)
{
    // FILL IN FIRST
}

/* Free memory temporary 'op' (in case it is one) by pushing its displacement
 * onto the front of the linked list availMemTemps
 */
void freeMemtemp(opdesc *op) 
{
    // FILL IN THIRD

    // if op is a memory temporary:
    outputDebugN("freeing memory temp at disp %d", op->disp);

    // allocate a new memTemp structure with op's displacement and push
    // it onto the front of availMemTemps
}

void freeOp(opdesc *op) 
{
    freeRegs(op);
    freeMemtemp(op);
    free(op);
}

/***********************************************************************
 *  Spilling and moving of opdescs
 */

/* Free op's register(s) by spilling it into a memtemp.  Update op to reflect
 * the change.  If op is a dispop or indexop, need to 'movl' it into the
 * register it occupies (parameter r) before spilling.
 * If availMemTemps is not NULL, reuse first available displacement, else
 * increase localsize to get a new displacement.
 */
void spill(opdesc *op, regnum r) 
{
    // FILL IN THIRD:

    int disp;
    // first, compute the correct displacement, and output one of:
    outputDebugN("reusing memtemp at disp %d", disp);
    outputDebugN("creating new memtemp at disp %d", disp);
  
    // if memory location (dispop or indexop), need to move it into reg first:
    //   output movl instruction and op, then mark op's register(s) as free,
    //   then change op into register r and output that

    // now we are ready for the actual spilling:
    // output movl instruction and op, then mark op's register as free
    // then use makeDispOp to change op into a temporary displacement off ebp
    // and output op
}

/* Make register r available by making the opdesc that uses it (if
 * any) use a different register.  Call getFreeRegnum to get a new
 * register (which in turn may cause spilling of some other register).
 * If 'op' is the opdesc that uses r, we need to MODIFY op since it is
 * still being used.  Note that op could be a regop, dispop, or
 * indexop (in which case r could be either op->reg or op->reg2), but
 * in all cases we want to output "movl r, newreg" and update op to
 * use newreg instead of r.
 */
void makeAvailable(regnum r, int line) 
{
    // FILL IN SECOND

    // if r is free, return, else:

    outputDebugS("making reg %s available", regname[r]);
    assert(!regTab[r].locked);

    // lock the opdesc's register(s) while getting a new regnum

    // output a movl instruction and the current opdesc
  
    // mark the opdesc's register(s) (r and perhaps another) as free

    // change the opdesc to the new register and output that

    // update regTab to reflect that the new register now belongs to the opdesc
}

/***********************************************************************
 *  Outputting assembly code
 */

/* Output a comment */
void outputComment(char *s)
{
    fprintf(OUTPUT, "\n//%s", s);
}

/* Output a debugging message with an integer */
void outputDebugN(char *m, int n)
{
    if (CODEDEBUG) {
        fprintf(OUTPUT, "\n//");
        fprintf(OUTPUT, m, n);
    }
}

/* Output a debugging message with a string */
void outputDebugS(char *m, char *s)
{
    if (CODEDEBUG) {
        fprintf(OUTPUT, "\n//");
        fprintf(OUTPUT, m, s);
    }
}

/* Global array containing source file (declared in main.c) */
extern char *sourceline[];

/* Output a comment when the line number changes.
 * Also show the corresponding line from source program.
 * Use line number 0 to avoid this comment. */
void checkLineNum(int line)
{
    if (line != 0 && line != codeLine) {
        fprintf(OUTPUT, "\n      //-------------------------- %2d: %s",
                line, sourceline[line]);
        codeLine = line;
    }
}

/* Output an assembly command */
void outputCmd(char *opcode, int line)
{
    checkLineNum(line);
    if (opcode == NULL) /* use NULL to force line number check only */
        return;
    fprintf(OUTPUT, "\n\t%s\t", opcode);
    printComma = FALSE;
}

/* Output an operand */
void outputOp(opdesc *op)
{
    if (printComma)
        fprintf(OUTPUT, ", ");
    switch (op->type) {
    case constop:
        fprintf(OUTPUT, "$%d", op->val); 
        break;
    case regop:
        fprintf(OUTPUT, "%%%s", regname[op->reg]); 
        break;
    case dispop:
        fprintf(OUTPUT, "%d(%%%s)", op->disp, regname[op->reg]); 
        break;
    case indexop:
        fprintf(OUTPUT, "%d(%%%s, %%%s, %d)", op->disp,
                regname[op->reg], regname[op->reg2], op->val);
        break;
    default: assert(FALSE);
    }
    printComma = TRUE;
}

/* Output a constant operand */
void outputConst(int val)
{
    if (printComma)
        fprintf(OUTPUT, ", ");
    fprintf(OUTPUT, "$%d", val); 
    printComma = TRUE;
}

/* Output a register operand */
void outputReg(regnum r)
{
    if (printComma)
        fprintf(OUTPUT, ", ");
    fprintf(OUTPUT, "%%%s", regname[r]);
    printComma = TRUE;
}


/* Output a function label as target (prepend "yo_" to avoid conflicts) */
void placeFunLabel(char *funname)
{
    outputComment("================================");
    fprintf(OUTPUT, "\nyo_%s:", funname);
}

/* Output header code (temporary version) */
void outputHeader()
{
    fprintf(OUTPUT, ".globl yocomain");  /* for now */
    fprintf(OUTPUT, "\nyocomain:");
    fprintf(OUTPUT, "\n\tpushl\t%%ebp");
    fprintf(OUTPUT, "\n\tmovl\t%%esp, %%ebp");
    fprintf(OUTPUT, "\n\tpushl\t%%ebx");
    fprintf(OUTPUT, "\n\tpushl\t%%edi");
    fprintf(OUTPUT, "\n\tpushl\t%%esi");
}

/* Output trailer code (temporary version) */
void outputTrailer()
{
    fprintf(OUTPUT, "\n");
    fprintf(OUTPUT, "\n\tpopl\t%%esi");
    fprintf(OUTPUT, "\n\tpopl\t%%edi");
    fprintf(OUTPUT, "\n\tpopl\t%%ebx");
    fprintf(OUTPUT, "\n\tleave");
    fprintf(OUTPUT, "\n\tret\n");
}
