/* codegen-expr.c  for CS 433 project
 *
 * code generation for expressions
 *
 * FILL IN for hw 7
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"


/***********************************************************************
 *  Procedures for expressions
 */

/* Code generation for a variable (Nident or Narray).  The returned
 * opdesc is always a memory location (i.e. an assignable).
 */
opdesc *genVar(node *varnode)
{
    node *subvar, *subexpr;

    switch (varnode->unk.type) {
        
    case Nident:

        // FILL IN:
        // use newDispOp to make opdesc for globals, locals, and parameters
        // for refparams, use forceToReg and makeDispOp

    case Narray:
        subvar = varnode->internal.child[0];
        subexpr = varnode->internal.child[1];

        // FILL IN:
        // call genExpr and genVar on subexpr and subvar (in that order)
        // to get index and base address of array

        // adjust the base address if lowbound != 0

        // if index is constant, simply add correct amount to base
        // address's displacement

        // also check if constant index is within bounds if bounds are known
        // (i.e., for locals and globals).  If not, output a warning
        // to stderr but keep generating code anyway
        
        // else, make sure the result of subexpr is in a register and
        // use makeIndexOp

    default:
        assert(FALSE);
        return NULL;
    }
}

/* Code generation for an expression: variable (Nident, Narray),
 * Nconst, Nfuncall, unary ops (Nnot, Nneg), and binary ops (Nor,
 * Nand, Nlt, Ngt, Neq, Nle, Nge, Nne, Nplus, Nminus, Ntimes, Ndiv,
 * Nmod).  Return an opdesc holding the result.
 */
opdesc *genExpr(node *expr)
{
    opdesc *op0, *op1;
  
    switch (expr->unk.type) {
    case Nident:
    case Narray:
        return genVar(expr);

    case Nconst:
        return newConstOp(expr->constant.val);
    
    case Nfuncall:
    case Nnot:
    case Nor:
    case Nand:
    case Nlt:
    case Ngt:
    case Neq:
    case Nle:
    case Nge:
    case Nne:
        return newConstOp(0);  /* later -- for now, just return constant 0 */
    
    case Nneg:

        // FILL IN:
        // call genExp on child node
        // if constant opdesc, simply negate its value
        // else make sure opdesc is register, then output code to perform
        // negation (use outputCmd and outputOp)
        // return resulting opdesc

    case Nplus:
    case Nminus:
    case Ntimes:
    case Ndiv:
    case Nmod:

        // FILL IN:
        // call genExp on both child nodes to get op0 and op1
        // if both constant update op0's value, free op1, and return op0
        // else:
        // for plus, minus, times:
        //   make op0 a register, output the appropriate code, free op1,
        //   return op0
        // for div and mod:
        //   special case: need op0 in eax, zero-extend into edx
        //   use clearSpecificReg to get opdesc for edx
        //   use forceToSpecificReg to get eax (lock edx while doing this)
        //   make sure op1 is not a constant (seems required for divl;
        //     in that case move to reg, while locking both eax, edx)
        //   output "cltd" and div instruction
        //   depending on div or mod, return one of eax, edx, free the other

    default:
        assert(FALSE);
        return NULL;    /* this is to avoid warning msg */
    }
}
