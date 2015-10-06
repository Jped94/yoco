/* parser.y -- Yacc grammar file for CS 433 HW 3
 * Based on Code by Daniel Scharstein
 * Josh Pedowitz
 */

%{
#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"
#include "syntree.h"
#include "syntax.h"

#define YYDEBUG 1

/* yylex is the lexical analyzer created by Lex */
extern int yylex();

/* defined in parser.y below */
void yyerror(char *s);

int PRINT_PRODUCTIONS;
#define production(s) if (PRINT_PRODUCTIONS) printf(s)

%}

%token <treenode> ID
%token <treenode> CONST
%token <treenode> INT
%token <treenode> YONO

%token <lexeme> GLOBAL
%token <lexeme> RETWEET
%token <lexeme> IF
%token <lexeme> ELSE
%token <lexeme> WHILE
%token <lexeme> END
%token <lexeme> OR
%token <lexeme> AND
%token <lexeme> NOT
%token <lexeme> LIKE
%token <lexeme> REF
%token <lexeme> HASH
%token <lexeme> LT 
%token <lexeme> LE 
%token <lexeme> GT 
%token <lexeme> GE 
%token <lexeme> PLUS
%token <lexeme> MINUS
%token <lexeme> MULT
%token <lexeme> DIV
%token <lexeme> MOD
%token <lexeme> ASSIGN 
%token <lexeme> COLON 
%token <lexeme> BANG 
%token <lexeme> LPAREN
%token <lexeme> RPAREN
%token <lexeme> LBRACK
%token <lexeme> RBRACK
%token <lexeme> DOTDOT
%token <lexeme> COMMA


%type <treenode> program
%type <treenode> globlist
%type <treenode> vardecl
%type <treenode> type
%type <treenode> basictype
%type <treenode> sconst
%type <treenode> decllist
%type <treenode> decl
%type <treenode> funlist
%type <treenode> fundecl
%type <treenode> params
%type <treenode> paramlist
%type <treenode> param
%type <treenode> stmtlist
%type <treenode> stmt
%type <treenode> assignment
%type <treenode> variable
%type <treenode> funcall
%type <treenode> retstmt
%type <treenode> ifstmt
%type <treenode> elsestmt
%type <treenode> whilestmt
%type <treenode> exprlist
%type <treenode> expr
%type <treenode> logterm
%type <treenode> logfactor
%type <treenode> relexpr
%type <treenode> arithexpr
%type <treenode> term
%type <treenode> factor




%%

program : globlist funlist
            { syntree = makenode2(Nprogram, $1, $2,
                                  $1? $1->internal.line :
                                  ($2? $2->internal.line :
                                   1)); /* line number for empty prog... */
              production("program -> globlist funlist\n"); $$ = NULL; }
              

        ;

globlist: /* epsilon */
                { $$ = NULL;
                  production("globlist -> epsilon\n"); }

            | globlist GLOBAL vardecl
                { $$ = makelist(Ngloblist, $1, $3, $2.line);
                  production("globlist -> globlist GLOBAL vardecl\n"); }
            ;

vardecl     : type decllist BANG
                { $$ = makenode2(Nvardecl, $1, $2, $1->internal.line) ;
                  production("vardecl -> type decllist !\n"); }
            ;

type        : basictype
                { $$ = $1; 
                  production("type -> basictype \n"); }
            | basictype LBRACK sconst DOTDOT sconst RBRACK
                { $$ = makenode3(Narraytype, $1, $3, $5, $1->internal.line); 
                  production("type -> basictype [ sconst .. sconst ]\n"); }
            ;

basictype   : INT
              { $$ = $1; 
                production("basictype -> INT\n"); }
            | YONO
              { $$ = $1; 
                production("basictype -> YONO\n"); }
            ;

sconst      : CONST
              { $$ = $1; 
                production("sconst -> CONST\n"); }
            | MINUS CONST
              { $2->constant.val = $2->constant.val*-1; $$ = $2; 
                production("sconst -> - CONST\n"); }
            ;

decllist    : decl
              { $$ = makelist(Ndecllist, NULL, $1, $1->internal.line); 
                production("decllist -> decl\n"); }
            | decllist COMMA decl
              { $$ = makelist(Ndecllist, $1, $3, $1->internal.line); 
                production("decllist -> decllist , decl\n"); }
            ;

decl        : HASH ID
              { $$ = makenode2(Ndecl, $2, NULL, $2->internal.line); 
                production("decl -> # ID\n"); }
            | HASH ID ASSIGN expr
              { $$ = makenode2(Ndecl, $2, $4, $2->internal.line); 
                production("decl -> # ID @ expr\n"); }
            ;

funlist     : /* epsilon */
              { $$ = NULL; 
                production("funlist -> epsilon\n");}
            | funlist fundecl
              { $$ = makelist(Nfunlist, $1, $2, 
                                  $1? $1->internal.line :
                                  ($2? $2->internal.line :
                                   1)); 
                production("funlist -> fundecl funlist\n");}
            ;

fundecl     : ID LPAREN params RPAREN COLON stmtlist END BANG
              { $$ = makenode4(Nfundecl, NULL, $1, $3, $6, $1->internal.line); 
                production("fundecl -> ID ( params ): stmtlist END !\n");}
            | basictype ID LPAREN params RPAREN COLON stmtlist END BANG
              { $$ = makenode4(Nfundecl, $1, $2, $4, $7, $1->internal.line); 
                production("fundecl -> basictype ID ( params ): stmtlist END !\n");}
            ;

params      : /* epsilon */
              { $$ = NULL; 
                production("params -> epsilon\n");}
            | paramlist
              { $$ = $1; 
                production("params -> paramlist\n");}
            ;

paramlist   : param
              { $$ = makelist(Nparamlist, NULL, $1, $1->internal.line); 
                production("paramlist -> param\n");}
            | paramlist COMMA param
              { $$ = makelist(Nparamlist, $1, $3, $3->internal.line); 
                production("paramlist -> paramlist , param\n");}
            ;

param       : basictype HASH ID
              { $$ = makenode2(Nvalparam, $1, $3, $3->internal.line); 
                production("param -> basictype # ID\n");}
            | REF basictype HASH ID
              { $$ = makenode2(Nrefparam, $2, $4, $4->internal.line); 
                production("param -> REF basictype # ID\n");}
            | basictype LBRACK RBRACK HASH ID
              { $$ = makenode2(Narrparam, $1, $5, $5->internal.line); 
                production("param -> basictype [ ] # ID\n");}
            ;

stmtlist    : /* epsilon */
              { $$ = NULL; 
                production("stmtlist -> epsilon\n");}
            | stmtlist stmt
              { $$ = makelist(Nstmtlist, $1, $2, $2->internal.line); 
                production("stmtlist -> stmtlist stmt\n");}
            ;

stmt        : vardecl
              { $$ = $1; 
                production("stmt -> vardecl\n");}
            | assignment
              { $$ = $1; 
                production("stmt -> assignment\n");}
            | funcall BANG
              { $$ = $1; 
                production("stmt -> funcall !\n");}
            | retstmt
              { $$ = $1; 
                production("stmt -> retstmt\n");}
            | ifstmt
              { $$ = $1; 
                production("stmt -> ifstmt\n");}
            | whilestmt
              { $$ = $1; 
                production("stmt -> whilestmt\n");}
            ;

assignment  : variable ASSIGN expr BANG
              { $$ = makenode2(Nassign, $1, $3, $1->internal.line); 
                production("assignment -> variable @ expr !\n");}
            ;

variable    : HASH ID
              { $$ = $2; 
                production("variable -> # ID\n");}
            | HASH ID LBRACK expr RBRACK
              { $$ = makenode2(Narray, $2, $4, $1.line); 
                production("variable -> # ID [ expr ]\n");}
            ;


funcall     : ID LPAREN RPAREN
              { $$ = makenode2(Nfuncall, $1, NULL, $1->internal.line); 
                production("funcall -> ID ( )\n");}
            | ID LPAREN exprlist RPAREN
              { $$ = makenode2(Nfuncall, $1, $3, $1->internal.line); 
                production("funcall -> ID ( exprlist )\n");}
            ;

retstmt     : RETWEET BANG
              { $$ = makenode1(Nreturn, NULL, $1.line); 
                production("retstmt -> RETWEET !\n");}
            | RETWEET expr BANG
              { $$ = makenode1(Nreturn, $2, $2->internal.line); 
                production("retstmt -> RETWEET expr !\n");}
            ;

ifstmt      : IF expr COLON stmtlist elsestmt END BANG
              { $$ = makenode3(Nif, $2, $4, $5, $1.line); 
                production("ifstmt -> IF expr : stmtlist elsestmt END !\n");}
            ;

elsestmt    : /* epsilon */
              { $$ = NULL; 
                production("elsestmt -> epsilon\n");}
            | ELSE IF expr COLON stmtlist elsestmt
              { $$ = makenode3(Nelseif, $3, $5, $6, $1.line); 
                production("elsestmt -> ELSE IF expr : stmtlist elsestmt\n");}
            | ELSE COLON stmtlist
              { $$ = makenode1(Nelse, $3, $1.line); 
                production("elsestmt -> ELSE : stmtlist\n");}
            ;

whilestmt   : WHILE expr COLON stmtlist END BANG
              { $$ = makenode2(Nwhile, $2, $4, $1.line); 
                production("whilestmt -> WHILE expr : stmtlist END !\n");}
            ;

exprlist    : expr
              { $$ = makelist(Nexprlist, NULL, $1, $1->internal.line); 
                production("exprlist -> expr\n");}
            | exprlist COMMA expr
              { $$ = makelist(Nexprlist, $1, $3, $1->internal.line); 
                production("exprlist -> exprlist , expr\n");}
            ;

expr        : logterm
              { $$ = $1; 
                production("expr -> logterm\n");}
            | expr OR logterm
              { $$ = makenode2(Nor, $1, $3, $1->internal.line); 
                production("expr -> expr OR logterm\n");}
            ;

logterm     : logfactor
              { $$ = $1; 
                production("logterm -> logfactor\n");}
            | logterm AND logfactor
              { $$ = makenode2(Nand, $1, $3, $1->internal.line); 
                production("logterm -> logterm AND logfactor\n");}
            ;

logfactor   : relexpr
              { $$ = $1; 
                production("logfactor -> relexpr\n");}
            | NOT relexpr
              { $$ = makenode1(Nnot, $2, $1.line); 
                production("logfactor -> NOT relexpr\n");}
            ;

relexpr     : arithexpr
              { $$ = $1; 
                production ("relexpr -> arithexpr\n");}
            | arithexpr LT arithexpr
              { $$ = makenode2(Nlt, $1, $3, $1->internal.line); 
                production ("relexpr -> arithexpr < arithexpr\n");}
            | arithexpr LE arithexpr
              { $$ = makenode2(Nle, $1, $3, $1->internal.line); 
                production ("relexpr -> arithexpr <= arithexpr\n");}
            | arithexpr GT arithexpr
              { $$ = makenode2(Ngt, $1, $3, $1->internal.line); 
                production ("relexpr -> arithexpr > arithexpr\n");}
            | arithexpr GE arithexpr
              { $$ = makenode2(Nge, $1, $3, $1->internal.line); 
                production ("relexpr -> arithexpr >= arithexpr\n");}
            | arithexpr LIKE arithexpr
              { $$ = makenode2(Neq, $1, $3, $1->internal.line); 
                production ("relexpr -> arithexpr LIKE arithexpr\n");}
            | arithexpr NOT LIKE arithexpr
              { $$ = makenode2(Nne, $1, $4, $1->internal.line); 
                production ("relexpr -> arithexpr NOT LIKE arithexpr\n");}
            ;

arithexpr   : term
              { $$ = $1; 
                production("arithexpr -> term\n"); }
            | arithexpr PLUS term
              { $$ = makenode2(Nplus, $1, $3, $1->internal.line); 
                production("arithexpr -> arithexpr + term\n"); }
            | arithexpr MINUS term
              { $$ = makenode2(Nminus, $1, $3, $1->internal.line); 
                production("arithexpr -> arithexpr - term\n"); }
            ;

term        : factor
              { $$ = $1; 
                production("term -> factor\n");}
            | term MULT factor
              { $$ = makenode2(Ntimes, $1, $3, $1->internal.line); 
                production("term -> term * factor\n");}
            | term DIV factor
              { $$ = makenode2(Ndiv, $1, $3, $1->internal.line); 
                production("term -> term / factor\n");}
            | term MOD factor
              { $$ = makenode2(Nmod, $1, $3, $1->internal.line); 
                production("term -> term MOD factor\n");}
            ;

factor      : MINUS factor
              { $$ = makenode1(Nneg, $2, $2->internal.line); 
                production("factor -> - factor\n");}
            | variable
              { $$ = $1; 
                production("factor -> variable\n");}
            | funcall
              { $$ = $1; 
                production("factor -> funcall\n");}
            | CONST
              { $$ = $1; 
                production("factor -> CONST\n");}
            | LPAREN expr RPAREN
              { $$ = $2; 
                production("factor -> ( expr )\n");}
            ;


/* *** FILL IN ***
   define other rules here

   Tips:
   1. First add the minimal amount of stuff to get everything to compile.
      this involves filling in the tokens and non-terminals above, and
      then adding "dummy rules" like

      type: {$$ = NULL;}

      for all nonterminals

   2. Add the grammar rules, but don't worry about the actions yet.  Now,
      all syntactically correct programs (like the ones in cs433/yoco/)
      should parse without a syntax error.

   3. Add the actions that print the productions and test them using ./yococo -p

   4. Add the actions that create the syntax tree and test them using
      ./yococo -t.  Be careful about getting line numbers from non-terminals -
      don't use one that could be NULL, like globlist.
*/

%%

/* report parsing error (required by yacc) */
void yyerror(char *s)
{
    fprintf(stderr, "line %d: %s\n", curlineno, s);
}
