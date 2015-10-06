/* codegen-lowlev.c  for CS 433 project
 *
 * code generation: low-level routines
 *
 * version for hw 8
 *
 * By James Thornton & Josh Pedowitz, based on code by Daniel Scharstein
 *
 * 
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

int labelCount = 0;    	/* current label number */

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
    int i;
    for (i = FIRSTREG; i <= LASTREG; i++) {
        regTab[i].op = NULL; // MAKE SURE THIS DOESNT CAUSE A MEMORY LEAK
        regTab[i].locked = FALSE;
    }
}

/* Lock register so it won't get moved or spilled */
void lockReg(regnum r) 
{
    regTab[r].locked = TRUE;
}

/* Unlock register */
void unlockReg(regnum r) 
{
    regTab[r].locked = FALSE;
}

/* Get the number of a free register.  If none are left, spill an unlocked
 * used register into a memory temporary.
 */
regnum getFreeRegnum() 
{
    // return first free non-reserved register (starting with eax)

    int i;
    for(i = FIRSTREG; i <= LASTREG; i++) {
        if(regTab[i].op == NULL) {
            return i;
        }
    }

    /* not enough regs - need to spill one into memtemp */
    // find the first used non-locked register r and spill its opdesc op
    // by calling spill(op, r);

    for(i = 0; i < 5; i++) {
        if(!regTab[i].locked) {
            spill(regTab[i].op, i);
            assert(regTab[i].op != NULL);
            return i;
        }
    }

    assert(FALSE); /* should always find a register to spill... */
    return 0;
}

/***********************************************************************
 *  Operations on opdescs
 */

/* Allocate a new opdesc of type constop and value val */
opdesc *newConstOp(int val) 
{
    opdesc *newop = (opdesc *) malloc(sizeof(opdesc));
    newop->type = constop;
    newop->val = val;
    return newop;
}

/* Allocate a new opdesc of type regop and register r and update regtab[r] */
opdesc *newRegOp(regnum r) 
{
    opdesc *newop = (opdesc *) malloc(sizeof(opdesc));
    newop->type = regop;
    newop->reg = r;
    assert(regTab[r].op == NULL);
    regTab[r].op = newop;
    return newop;
}

/* Allocate a new opdesc of type dispop, register r, displacement disp,
 * isTemp==FALSE, and update regtab[r] 
 */
opdesc *newDispOp(int disp, regnum r) 
{
    opdesc *newop = (opdesc *) malloc(sizeof(opdesc));
    newop->type = dispop;
    newop->reg = r;
    newop->disp = disp;
    newop->isTemp = FALSE;
    regTab[r].op = newop;
    return newop;
    
}

/* Turn regop 'op' (register) into a dispop (memory location) */
void makeDispOp(opdesc *op, int disp, int isTemp) 
{
    assert(op->type == regop);
    op->type = dispop;
    op->disp = disp;
    op->isTemp = isTemp;
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
    op1->type = indexop;
    op1->reg2 = op2->reg;
    op1->val = s;
    regTab[op2->reg].op = op1;
    free(op2);
}

/* Lock 'op' by locking its register(s) */
void lock(opdesc *op)
{ 
    if (op->type != constop) lockReg(op->reg); 
    if (op->type == indexop) lockReg(op->reg2);
}

/* Unlock 'op' by unlocking its register(s) */
void unlock(opdesc *op)
{ 
    if (op->type != constop) unlockReg(op->reg); 
    if (op->type == indexop) unlockReg(op->reg2);
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
    // use getFreeRegnum and newRegOp

    if (op->type == regop) return op;
    freeRegs(op);

    opdesc *newop = newRegOp(getFreeRegnum());

    outputCmd("movl", line);
    outputOp(op);
    outputOp(newop);
    freeMemtemp(op);
    free(op);

    return newop;
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
    // if it's in the correct register already, just return it
    if (op->type == regop && op->reg == r) return op;


    // call makeAvailable to make r available, UNLESS op is a memloc
    // that uses this register (e.g., if op is "0(%eax)" and we want
    // eax, we want to simply output "movl 0(%eax), %eax"
    if (!((op->type == dispop && op->reg == r) ||
          (op->type == indexop && (op->reg == r || op->reg2 == r)))) makeAvailable(r, line);

    // output a movl instruction from the old op to register r
    outputCmd("movl", line);
    outputOp(op);
    outputReg(r); 

    // THEN call freeOp to free the old op, THEN call newRegOp
    // (so that register allocation table is correct; we can't call
    // freeOp earlier since the debugging output created by freeMemTemps
    // could mess things up)
    // Note that this makes outputting the new register tricky
    // in the movl instruction above (hint: use outputReg)           
    freeOp(op);

    // return the new regop
    return newRegOp(r);
    
}

/***********************************************************************
 *  Freeing opdescs
 */

/* Mark the register(s) used by 'op' as free */
void freeRegs(opdesc *op)
{
    if(op->type != constop) regTab[op->reg].op = NULL;
    if(op->type == indexop) regTab[op->reg2].op = NULL;
}

/* Free memory temporary 'op' (in case it is one) by pushing its displacement
 * onto the front of the linked list availMemTemps
 */
void freeMemtemp(opdesc *op) 
{

    // if op is a memory temporary:
    if (op->type == dispop && op->isTemp == TRUE) {
        
    // allocate a new memTemp structure with op's displacement and push
    // it onto the front of availMemTemps
        outputDebugN("freeing memory temp at disp %d", op->disp);
        memTemp *newmemtemp = (memTemp *) malloc(sizeof(memTemp));
        newmemtemp->next = availMemTemps;
        newmemtemp->disp = op->disp;
        availMemTemps = newmemtemp;
        
    }
   
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

    int disp;
    // first, compute the correct displacement, and output one of:
    if(availMemTemps == NULL){
        currentfundesc->fun.localsize += INTSIZE;
        disp = LOCAL_OFFS - currentfundesc->fun.localsize;
        outputDebugN("creating new memtemp at disp %d", disp);
    } else {
        memTemp *memFree = availMemTemps;
        disp = availMemTemps->disp;
        if (availMemTemps->next == NULL) availMemTemps = NULL;
        else availMemTemps = availMemTemps->next;
        free(memFree);
        outputDebugN("reusing memtemp at disp %d", disp);
    }

    // if memory location (dispop or indexop), need to move it into reg first:
    //   output movl instruction and op, then mark op's register(s) as free,
    //   then change op into register r and output that

    if (isMemloc(op)) {
        outputCmd("movl", 0);
        outputOp(op);
        freeRegs(op);
        op->type = regop;
        op->reg = r;
        op->isTemp = 0;        
        outputOp(op);
    }

    // now we are ready for the actual spilling:
    // output movl instruction and op, then mark op's register as free
    // then use makeDispOp to change op into a temporary displacement off ebp
    // and output op

    assert(op->type == regop);
    outputCmd("movl", 0);
    outputOp(op);
    op->reg = ebp;
    freeRegs(op);
    makeDispOp(op, disp, TRUE);
    outputOp(op);

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
    opdesc *op = regTab[r].op;
    // if r is free, return, else:
    if (op == NULL) return;

    outputDebugS("making reg %s available", regname[r]);
    assert(!regTab[r].locked);

     // lock the opdesc's register(s) while getting a new regnum
    lock(op);
    regnum newr = getFreeRegnum();
    unlock(op);

    // output a movl instruction and the current opdesc
    outputCmd("movl", line);
    outputReg(r);
    
    // mark the opdesc's register(s) (r and perhaps another) as free
    freeRegs(op);

    // change the opdesc to the new register and output that
    if (op->reg == r) op->reg = newr;
    if (op->reg2 == r) op->reg2 = newr;
    outputReg(newr);

    // update regTab to reflect that the new register now belongs to the opdesc
    regTab[r].op = NULL;
    regTab[newr].op = op;
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

/***********************************************************************
 *  Labels and branches
 */

/* initialize a new label */
void initLabel(codelabel *label, char *name)
{
  label->name = name;
  label->num = ++labelCount;
  label->referenced = FALSE;
}

/* output a label as operand */
void outputLabel(codelabel *label)
{
  fprintf(OUTPUT, "%s%d", label->name, label->num);
  label->referenced = TRUE;
}

/* output a label as target */
void placeLabel(codelabel *label)
{
  if (label->referenced)
    fprintf(OUTPUT, "\n%s%d:", label->name, label->num);
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
