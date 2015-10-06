/* codegen-expr.c  for CS 433 project
 *
 * code generation for expressions
 *
 * FILL IN for hw 7
 * By James Thornton & Josh Pedowitz, based on code by Daniel Scharstein
 *
 * Time to Complete: 18 hours
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
    int disp;
    opdesc *op0, *op1;
    typedesc *type0;
    int typesize;

    switch (varnode->unk.type) {
        
    case Nident:

        // use newDispOp to make opdesc for globals, locals, and parameters
        // for refparams, use forceToReg and make Dis pOp

        if(varnode->ident.decl->unk.type == formaldecl) {
            disp = varnode->ident.decl->formal.vardisp;
            op0 = newDispOp(disp+PARAM_OFFS, ebp);

            if (varnode->ident.decl->formal.valparam == FALSE) {
                op0 = forceToReg(op0, varnode->unk.line);
                makeDispOp(op0, 0, FALSE);    
            }

        } else if (varnode->ident.decl->var.type == vardecl) {
            disp = varnode->ident.decl->var.vardisp;
            // Check for global or local
            if (varnode->ident.decl->var.level == 0) op0 = newDispOp(disp, GLOBALREG);
            else op0 = newDispOp(LOCAL_OFFS - disp- varnode->ident.decl->var.vartype->typesize, ebp);
            
        }
        return op0;

    case Narray:
        subvar = varnode->internal.child[0];
        subexpr = varnode->internal.child[1];

        // call genExpr and genVar on subexpr and subvar (in that order)
        // to get index and base address of array

        op0 = genExpr(subexpr);
        op1 = genVar(subvar);
        
        typesize  = type0->typespec == integer ? INTSIZE : BOOLSIZE;


        // adjust the base address if lowbound != 0

        type0 = subvar->ident.decl->var.vartype;  


        op1->disp -= typesize * type0->lowbound;

        // if index is constant, simply add correct amount to base
        // address's displacement

        if (isConst(op0)){
            int subnum = op0->val;
            freeOp(op0);              
            op1->disp += op0->val * typesize;
            if (type0->lowbound != 0 || type0->highbound != 0) {
                if (subnum > type0->highbound || subnum < type0->lowbound) {
                    fprintf(stderr, "Line %d. Index out of bounds.", varnode->unk.line);
                }
            }
        } else {
            op0 = forceToReg(op0, varnode->unk.line);
            makeIndexOp(op1, op0, typesize);
        }

        return op1;
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
    opdesc *op0, *op1, *op2;
  
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

        // call genExpr on child node
        // if constant opdesc, simply negate its value
        // else make sure opdesc is register, then output code to perform
        // negation (use outputCmd and outputOp)
        // return resulting opdesc
    
        op0 = genExpr(expr->internal.child[0]);
        if (isConst(op0)) op0->val = -op0->val;
        else {
                op0 = forceToReg(op0, expr->unk.line);
                outputCmd("negl", expr->unk.line);
                outputOp(op0);       

        }
        return op0;
        

    case Nplus:
    case Nminus:
    case Ntimes:

        // call genExp on both child nodes to get op0 and op1
        op0 = genExpr(expr->internal.child[0]);
        op1 = genExpr(expr->internal.child[1]);
        
        // if both constant update op0's value, free op1, and return op0
        if(isConst(op0) && isConst(op1)) {
            switch (expr->unk.type){
                case Nplus: op0->val += op1->val; break;
                case Nminus: op0->val -= op1->val; break;
                case Ntimes: op0->val *= op1->val; break;
                default: assert(FALSE); return NULL;
            }
            freeOp(op1);
            return op0;
        } else {
        // for plus, minus, times:
        //   make op0 a register, output the appropriate code, free op1,
        //   return op0
            op0 = forceToReg(op0, expr->unk.line);
            switch (expr->unk.type){
                case Nplus: outputCmd("addl", expr->unk.line); break;
                case Nminus: outputCmd("subl", expr->unk.line); break;
                case Ntimes: outputCmd("imull", expr->unk.line); break;
                default: assert(FALSE); return NULL;
            }
            outputOp(op1);
            outputOp(op0);
            freeOp(op1);
            return op0;
        }

    
    case Ndiv:
    case Nmod:

        // call genExp on both child nodes to get op0 and op1
        // if both constant update op0's value, free op1, and return op0

        op0 = genExpr(expr->internal.child[0]);
        op1 = genExpr(expr->internal.child[1]);

        if(isConst(op0) && isConst(op1)) {
            op0->val = expr->unk.type == Ndiv ? op0->val / op1->val : op0->val % op1->val;
            freeOp(op1);
            return op0;
        } else {
        // for div and mod:
        //   special case: need op0 in eax, zero-extend into edx
        //   use clearSpecificReg to get opdesc for edx
        //   use forceToSpecificReg to get eax (lock edx while doing this)
        //   make sure op1 is not a constant (seems required for divl;
        //     in that case move to reg, while locking both eax, edx)
        //   output "cltd" and div instruction
        //   depending on div or mod, return one of eax, edx, free the other

            op2 = clearSpecificReg(edx, expr->unk.line);
            lock(op2); 
            op0 = forceToSpecificReg(op0, eax, expr->unk.line);    
            if(isConst(op1)) {
                lock(op0);           
                op1 = forceToReg(op1, expr->unk.line);
                unlock(op0);
            }
            
            unlock(op2);
            outputCmd("cltd", expr->unk.line);
            outputCmd("idivl", expr->unk.line);
            outputOp(op1);
            freeOp(op1);
            if ( expr->unk.type == Ndiv) {
                freeOp(op2);
                return op0;
            } else {
                freeOp(op0);
                return op2;
            }

        }


    default:
        assert(FALSE);
        return NULL;    /* this is to avoid warning msg */
    }
}
