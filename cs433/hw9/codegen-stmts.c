/* codegen-stmts.c  for CS 433 project
 *
 * code generation for statements
 *
 * By James Thornton & Josh Pedowitz, based on code by Daniel Scharstein
 *
 * Time to Complete: 6 hours
 *
 * Version for hw 9
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"

/* global variable for return statements */
codelabel funend; /* label of last statement in function */


/* generate code for an assignment statement */
void genAssign(node *stmt)
{
    node *var = stmt->internal.child[0];
    node *expr = stmt->internal.child[1];

    assert (stmt->unk.type == Nassign || stmt->unk.type == Ndecl);

    if (expr == NULL)
        return; /* declaration without assignment */
    
    opdesc *value = genExpr(expr);
    opdesc *target = genVar(var);
    if (isMemloc(value))
        value = forceToReg(value, stmt->internal.line);
    outputCmd("movl", stmt->internal.line);
    outputOp(value);
    outputOp(target);
    freeOp(value);
    freeOp(target);
}

/* handle vardecls as list of assignments */
void genVardecl(node *vardeclnode)
{
    node *decllist = vardeclnode->internal.child[1];
    applytolist(decllist, genAssign);
}

/* Generate code for expressions appearing as actual parameters.
 * Recursive method pushes actuals in reverse order.
 */
void genActuals(node *actualList, decldesc *formal)
{
    // use recursive strategy:
    // if the lists are NULL, we're done
    // otherwise, call genActuals recursively with the rests of
    // both lists (which will generate code to push the parameters
    // in reverse order)
    // then, generate code to compute the current actual
    // - it it's an array parameter, need to adjust the displacement again
    //   since the called function thinks the lowbound is 0
    // - if it's a refparam (which includes arrays), call computeAddress
    // finally, push the actual on the stack
    
    if (!actualList) return;
    node *actual = actualList->internal.child[0];
    node *nextActualList = actualList->internal.child[1];
    decldesc *formalList = formal->formal.formallink;
    int line = actual->unk.line;
    int typesize;
    typedesc* type0;

    if (actualList->internal.child[1] != NULL ) {
        genActuals(nextActualList, formalList);
    }

    opdesc *op0 = genExpr(actual);

    //if it's an array
    if (actual->unk.type == Nident && actual->ident.decl->var.vartype->isArray == TRUE) {
        
        type0 = actual->ident.decl->var.vartype;  
        typesize = type0->typespec == integer ? INTSIZE : BOOLSIZE;
        // adjust the base address if lowbound != 0
        op0->disp -= typesize * type0->lowbound;
    } 
    if(formal->formal.valparam == FALSE)
        //if it's a ref param
        op0 = computeAddress(op0, line);
    //push onto the stack
    outputCmd("pushl", line);
    outputOp(op0);
    freeOp(op0);
}

/* Generate code for a function call. */
opdesc *genCall(node *stmt)
{
    // call genActuals with actualList and the function's formallist
    // save volatile regs eax, ecx, edx (call saveReg, which calls spill)
    // if non-void function, get opdesc for eax to hold the return value
    // output a call command
    // restore stackpointer after call by adding the function's paramsize
    // return opdesc for eax or NULL if void function

    node *actuallist = stmt->internal.child[1];
    decldesc* fundesc = stmt->internal.child[0]->ident.decl;
    genActuals(actuallist, fundesc->fun.formallist);
    opdesc* op0;
    
    saveReg(eax); saveReg(ecx); saveReg(edx);
    
    if (fundesc->fun.returntype != NULL) {
        op0 = clearSpecificReg(eax, stmt->unk.line);    
    }
    outputCmd("call", stmt->unk.line);
    outputFunLabel(fundesc->fun.STentry->lexptr);
    outputCmd("addl", 0);
    outputConst(fundesc->fun.paramsize);
    outputReg(esp);
    
    if (fundesc->fun.returntype) return op0;
    else return NULL;
   
}

/* generate code for a return statement */
void genReturn(node *stmt, codelabel *next)
{

    if(stmt->internal.child[0]) {
        opdesc *op = genExpr(stmt->internal.child[0]);
        op = forceToSpecificReg(op, eax, stmt->unk.line);
        freeOp(op);
    }

    if (next != &funend) {
        outputCmd("jmp", stmt->internal.line);
        outputLabel(&funend);
    } else {
        outputCmd(NULL, stmt->internal.line); /* do nothing -- fall through */
    }

    // Note that you don't need to output a "jmp"
    // statement if next is the same as &funend
}

/* generate code for an if/elseif statement */
void genIf(node *stmt, codelabel *endif)
{
    node *expr = stmt->internal.child[0];
    node *thenstmts = stmt->internal.child[1]; /* stmtlist */
    node *elsestmt = stmt->internal.child[2];  /* Nelseif/Nelse */

    codelabel elselabel;

    if(elsestmt) {  //make sure there is an else
        initLabel(&elselabel, "else");
        genCondExpr(expr, FALSE, &elselabel);
    } else {
        genCondExpr(expr, FALSE, endif);
    }

    genStmtList(thenstmts, endif);
    
    if(elsestmt) {
        outputCmd("jmp", 0);
        outputLabel(endif);  
        placeLabel(&elselabel);
        genStmt(elsestmt, endif);
    }

}

/* generate code for a while statement */
void genWhile(node *stmt, codelabel *endwhile)
{

    codelabel loop;
    initLabel(&loop, "while");
    loop.referenced = TRUE; //do this because we place the label before we output here
    placeLabel(&loop);
    genCondExpr(stmt->internal.child[0], FALSE, endwhile);
    genStmtList(stmt->internal.child[1], &loop);
    outputCmd("jmp", 0);
    outputLabel(&loop);
}

/* Generate code for a statement (vardecl, assign, funcall,
 * return, if/elseif/else, or while).
 */
void genStmt(node *stmtnode, codelabel *next)
{
    switch (stmtnode->internal.type) {

    case Nvardecl:
        genVardecl(stmtnode);
        break;
        
    case Nassign:
        genAssign(stmtnode);
        break;
    
    case Nfuncall: /* later */
        genCall(stmtnode);
        break;

    case Nreturn:
        genReturn(stmtnode, next);
        break;

    case Nif:
    case Nelseif:
        genIf(stmtnode, next);
        break;

    case Nelse:
        genStmtList(stmtnode->internal.child[0], next);
        break;
    
    case Nwhile:
        genWhile(stmtnode, next);
        break;

    default:
        assert(FALSE); /* should never get here */
    }
}

/* Generate code for a statement list */
void genStmtList(node *stmtlist, codelabel *next)
{
    if (stmtlist != NULL) {
        codelabel nextstmt;  
        while (stmtlist->internal.child[1] != NULL){
            initLabel(&nextstmt,"stmt");            
            genStmt(stmtlist->internal.child[0], &nextstmt);
            placeLabel(&nextstmt);
            stmtlist = stmtlist->internal.child[1];
        }
        // do the last statement
        genStmt(stmtlist->internal.child[0], next);
                 
    }
}

/* Generate code for function */
void genFun(node *funnode)
{
    node *funname = funnode->internal.child[1];
    node *funstmts = funnode->internal.child[3];

    placeFunLabel(funname->ident.STentry->lexptr);
    currentfundesc = funname->ident.decl;

    initLabel(&funend, "funend");
    createFrame(TRUE, funname->ident.STentry->lexptr);
    genStmtList(funstmts, &funend);
    placeLabel(&funend);
    removeFrame(TRUE, funname->ident.STentry->lexptr);
    
}

/***********************************************************************
 *  Top-level routine
 */

/* Generate code for the entire program. */
void codegen(node *syntree)
{
    //outputCmd("movl", 0);
    //outputConst(20);
    //outputReg(edx);
    node *funlist = syntree->internal.child[1];

    initRegTab();
    outputHeader();

    applytolist(funlist, genFun);

    outputTrailer();
}
