/* resolve.c
 *
 * CS 433 - declaration resolution 
 *
 * 
 * version for hw 4 - global and local variables only
 *
 * James Thornton & Josh Pedowitz, Based on code by Daniel Scharstein
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"
#include "syntree.h"

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif

/***********************************************************************
 *  Global variables
 */

#define MAXDEPTH 100    /* Maximum allowed depth of scope nesting  */

extern int errorcount;  /* keep track of number of errors */

int curlevel;           /* Current scope nesting level */

decldesc *scopestack[MAXDEPTH];  /* Stack of headers for lists of
                                    declarations made in open scopes */

typedesc *IntType, *BoolType;   /* pointers to typedescs for basic types */

/***********************************************************************
 *  Utilities
 */

/* applytolist - Apply the function 'action' to each of the nodes in
 *      some subtree that forms a list.
 */
void applytolist(node *listhead, void (*action)()) 
{
    for( ; listhead != NULL; listhead = listhead->internal.child[1])
        action(listhead->internal.child[0]);
}

/* applytolist2 - Same as applytolist, except that it also passes a
 *      parameter 'param' to 'action'.
 */
void applytolist2(node *listhead, void (*action)(), void *param) 
{
    for( ; listhead != NULL; listhead = listhead->internal.child[1])
        action(listhead->internal.child[0], param);
}

/***********************************************************************
 * Initialization of global variables for basic type descriptors
 */

void initialize_basic_typedescs()
{
    IntType = (typedesc *)malloc(sizeof(typedesc));
    IntType->typespec = integer;
    IntType->isArray = FALSE;
    
    BoolType = (typedesc *)malloc(sizeof(typedesc));
    BoolType->typespec = bool;
    BoolType->isArray = FALSE;
}

/***********************************************************************
 * Declaration processing
 ***********************************************************************/
 
/* insertdecl -- Insert a new declaration descriptor into the stack of
 *      declarations associated with its identifier and the list of
 *      all declarations made at the current level.  Create a pointer
 *      from the Nident node to the new declaration descriptor.
 *      Before inserting the new declaration, make sure that the
 *      identifier was not previously defined in this scope.  If it
 *      was, free its space and return NULL.  Otherwise, return a
 *      pointer to the new declaration descriptor.
 *
 *      This function is called for three types of declarations:
 *      variables, function names, and formal parameters.
*/
		/* 1. check for multiple declaration at same level
       (print error message to stderr and return NULL if so) */

    /* 2. set common fields (type, line, level) */

    /* 3. set back pointer to ST record */

    /* 4. insert into stack of declarations */

    /* 5. insert into chain of levellinks */

    /* 6. create pointer from identnode to new declaration descriptor */

decldesc *insertdecl(decldesc *newdecl, decltype newdecltype, node *identnode)
{
    assert(identnode->ident.type == Nident);

	//1
	STrec *rec = identnode->ident.STentry;
	decldesc *curdecl = rec->declstack;
	
	while(curdecl != NULL){
		if ((curdecl->unk.STentry == rec) && (curdecl->unk.level == curlevel)) {
			fprintf(stderr, "Variable %s already declared in scope %d.\n", identnode->ident.STentry->lexptr, curlevel);
			free(newdecl);
			return NULL;
		}
		curdecl = curdecl->unk.decllink;
	}
	
	

	//2
	newdecl->unk.type = newdecltype;
	newdecl->unk.line = identnode->ident.line;
	newdecl->unk.level = curlevel;

	//3
	newdecl->unk.STentry = rec;
	
	//4
	newdecl->unk.decllink = rec->declstack;
	rec->declstack = newdecl;
	
	//5
	newdecl->unk.levellink = scopestack[curlevel];
	scopestack[curlevel] = newdecl;

	//6
	identnode->ident.decl = newdecl;

    return newdecl;
}


/***********************************************************************
 *  Basic Function for resolving an identifier
 */

/* resolve_ident -- Attempt to resolve the declaration descriptor pointer
 *      in an Nident node by setting it to the declstack pointer
 *      stored in the node's symbol table entry.  If successful,
 *      return the descriptor.  Otherwise, print an error message and
 *      return NULL.
 *
 *      This function is called when USES of an identifier are encountered,
 *      i.e., in statements and expressions.
 */
decldesc *resolve_ident(node *identnode)
{
    assert(identnode->ident.type == Nident);

	if (identnode->ident.STentry->declstack) {	
		identnode->ident.decl = identnode->ident.STentry->declstack;
		return identnode->ident.decl;
	} else {
		fprintf(stderr, "Identifier %s not yet declared: line %d \n",identnode->ident.STentry->lexptr, identnode->unk.line);	
		return NULL;
	}

}


/***********************************************************************
 *  Types
 */

/* resolve_type -- Check that 'typenode' represents a valid type, i.e.,
 *      either is 'Ntype' or 'Narraytype'.  In the former case, return
 *      either IntType or BoolType; in the latter case, malloc a new
 *      type descriptor, set the fields appropriately, and return it.
 */
typedesc *resolve_type(node *typenode)
{
	if (typenode->type.type == Ntype){
		if (typenode->type.typespec == integer) {
			return IntType;
		} else {
			return BoolType;
		} 
	} else if (typenode->type.type == Narraytype) {
		typedesc *ArrayType = (typedesc *)malloc(sizeof(typedesc));
		ArrayType->typespec = typenode->type.typespec;
		ArrayType->isArray = TRUE;
		ArrayType->lowbound = typenode->internal.child[0]->constant.val;
		ArrayType->highbound = typenode->internal.child[1]->constant.val;
		return ArrayType;
		
	} else {

		return NULL;

	}

}

/***********************************************************************
 *  Variable declarations
 */

/* prototype for function defined below */
void resolve_expression(node *exprnode);

/* resolve_singledecl -- Allocate a new 'vardesc' declaration
 *      descriptor, set its 'vartype' field, and push it onto the
 *      stack of declaration descriptors by calling 'insertdecl()'.
 *      If initialized variable, also resolve the expression.
 */
void resolve_singledecl(node *declnode, typedesc *vartypedesc)
{

    /* also resolve the expression (child[1]) if there is one */
    
	decldesc *newvar = (decldesc *)malloc(sizeof(decldesc));

	newvar->var.vartype = vartypedesc;

	

	decldesc *initialized = insertdecl(newvar, vardecl, declnode->internal.child[0]);

	/* If it's not acting the way it's supposed to...
	* try checking here.
	*/

	if(initialized != NULL) {
		if(declnode->internal.child[1]) {
			resolve_expression(declnode->internal.child[1]);
		}
	}

}

/* resolve_vardecl -- Process variable declarations, i.e., a bunch of
 *      identifiers declared to be of a certain type.
 */
void resolve_vardecl(node *vardeclnode)
{
    node *typenode = vardeclnode->internal.child[0];
    node *decllist = vardeclnode->internal.child[1];

    typedesc *vartypedesc = resolve_type(typenode);
  
    applytolist2(decllist, resolve_singledecl, vartypedesc);
}


/***********************************************************************
 *  Opening and closing scopes
 */

/* open new scope: increase curlevel, and initialize the scopestack at
 * this level to NULL */
void open_scope()
{
	curlevel +=1;
	scopestack[curlevel] = NULL;

}

/* close_scope: pop all declarations made in current scope by following the
 * current levellink-list, then decrease curlevel */
void close_scope()
{
	decldesc* curdesc = scopestack[curlevel];
	decldesc* nextdesc; 
	decldesc* nextscope;
	
	
	while (curdesc != NULL) {
		nextdesc = curdesc->unk.levellink; //sets nextdesc to next descriptor in scope
		nextscope = curdesc->unk.decllink; //sets nextscope descriptor in the next scope down
		curdesc->unk.STentry->declstack = nextscope; //points the STrec to nextscope
		curdesc->unk.levellink = NULL; //sets curdesc's levellink pointer to NULL
		curdesc = nextdesc; 
		
	}
	scopestack[curlevel] = NULL; //removes first element of scopestack
	curlevel -= 1;

}

/* prototype for forward declaration */
void resolve_stmt(node *stmtnode);

/* resolve_block: create new scope for statement lists in function bodies,
 * if/elseif/else and while statements */
void resolve_block(node *stmtlist)
{
    open_scope();
    applytolist(stmtlist, resolve_stmt);
    close_scope();
}

/*********************************************************************/
 
/* declaration resolution for an expression: variable (Nident,
 * Narray), Nconst, Nfuncall, unary ops (Nnot, Nneg), and binary ops
 * (Nor, Nand, Nlt, Ngt, Neq, Nle, Nge, Nne, Nplus, Nminus, Ntimes,
 * Ndiv, Nmod).
 */
void resolve_expression(node *exprnode)
{
    nodetype etype = exprnode->unk.type;
    node *node0 = exprnode->internal.child[0];
    node *node1 = exprnode->internal.child[1];
  
    switch (etype) {
    case Nident:
        resolve_ident(exprnode);
        break;

    case Narray:
        resolve_ident(node0);
        resolve_expression(node1);
        break;

    case Nconst:
        break;

    case Nfuncall:
        /* resolve_ident(node0);  -- don't resolve the function name yet */
        applytolist(node1, resolve_expression);
        break;
	
	case Nnot:
		resolve_expression(node0);
		break;

	case Nneg:
		resolve_expression(node0);
		break;

	case Nor:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nand:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nlt:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Ngt:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Neq:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nle:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nge:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nne:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nplus:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nminus:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Ntimes:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Ndiv:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nmod:
		resolve_expression(node0);
		resolve_expression(node1);
		break;


    
         
        /* call resolve_expressions on all subexpressions.
         */
    
    default:
        assert(FALSE); /* should never get here */
    }
  
}

/********************************************************************/

/* declaration resolution for a statement: vardecl, assign, funcall,
 * return, if/elseif/else, or while
 */
void resolve_stmt(node *stmtnode)
{
    node *node0 = stmtnode->internal.child[0];
    node *node1 = stmtnode->internal.child[1];
    node *node2 = stmtnode->internal.child[2];

    switch (stmtnode->internal.type) {
	
    case Nvardecl:
        resolve_vardecl(stmtnode);
        break;
    
        /* call resolve_stmt or resolve_expression
         * on all (non-NULL) "substatements" and  subexpressions; for
         * stmtlists in if/elseif/else and while, call resolve_block.
         */

	case Nassign:
		resolve_expression(node0);
		resolve_expression(node1);
		break;

	case Nfuncall:
		resolve_expression(node0);
		if(node1){applytolist(node1, resolve_expression);}
		break;

	case Nreturn:
		if(node0){resolve_expression(node0);}
		break;

	case Nif:
		resolve_expression(node0);
		resolve_block(node1);	
		if(node2){ resolve_stmt(node2);}
		break;	

	case Nelseif:
		resolve_expression(node0);
		resolve_block(node1);	
		if(node2){ resolve_stmt(node2);}
		break;	

	case Nelse:
		resolve_block(node0);
		break;

	case Nwhile:
		resolve_expression(node0);
		resolve_block(node1);
		break;        

    default:
        assert(FALSE); /* should never get here */
    }
}

  
/* process function body - preliminary version (ignores formal
 * parameters)
 */
void resolve_funbody(node *funnode)
{
    assert(funnode->unk.type == Nfundecl);
    resolve_block(funnode->internal.child[3]);
}

/***********************************************************************
 *  Top-level routine
 */

/* resolve  --  Do declaration resolution for the entire program.
 * For now, only resolve global and local variables (not functions or parameters)
 */
void resolve(node *syntree)
{
    initialize_basic_typedescs();
  
    if (syntree == NULL) {
        errorcount = 1;
    } else {
        node *globlist = syntree->internal.child[0];
        node *funlist = syntree->internal.child[1];

        errorcount = 0;
        curlevel = 0;       /* initialize current nesting level */
        scopestack[curlevel] = NULL;  /* initialize list of declarations
                                       * made in current scope */

        applytolist(globlist, resolve_vardecl);
        applytolist(funlist, resolve_funbody);
    }
}
