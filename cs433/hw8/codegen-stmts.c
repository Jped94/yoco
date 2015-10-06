/* codegen-stmts.c  for CS 433 project
 *
 * code generation for statements
 *
 * By James Thornton & Josh Pedowitz, based on code by Daniel Scharstein
 *
 * Time to Complete: 9 hours
 *
 * Version for hw 8
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

/* generate code for a return statement */
void genReturn(node *stmt, codelabel *next)
{

    if(stmt->internal.child[0]) {
        opdesc *op = genExpr(stmt->internal.child[0]);
        op = forceToSpecificReg(op, eax, stmt->unk.line);
        freeOp(op);
    }

    if (next != &funend) {
        outputCmd("jmp", 0);
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
    genStmtList(funstmts, &funend);
    placeLabel(&funend);
}

/***********************************************************************
 *  Top-level routine
 */

/* Generate code for the entire program. */
void codegen(node *syntree)
{
    node *funlist = syntree->internal.child[1];

    initRegTab();
    outputHeader();

    applytolist(funlist, genFun);

    outputTrailer();
}
