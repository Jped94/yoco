/* codegen-stmts.c  for CS 433 project
 *
 * code generation for statements
 *
 * version for hw 7
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"
#include "codegen.h"


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

/* Generate code for a statement (vardecl, assign, funcall,
 * return, if/elf/else, or whilst).
 */
void genStmt(node *stmtnode)
{
    switch (stmtnode->internal.type) {

    case Nvardecl:
        genVardecl(stmtnode);
        break;
        
    case Nassign:
        genAssign(stmtnode);
        break;

    default:    /* handle other cases later */
        break;
    }
}

/* Generate code for function */
void genFun(node *funnode)
{
    node *funname = funnode->internal.child[1];
    node *funstmts = funnode->internal.child[3];

    
    placeFunLabel(funname->ident.STentry->lexptr);
    currentfundesc = funname->ident.decl;

    applytolist(funstmts, genStmt);
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
