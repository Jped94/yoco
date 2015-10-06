/* main.c
 *
 * Main program for CS 433 compiler project
 *
 * version for hw2
 */

static char usage[] = "  usage: %s sourcefile\n";

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "symtab.h"
#include "syntree.h"
#include "syntax.h"

#include "tokens.h"
#include "tokennames.h"

extern FILE *yyin;

int main (int argc, char *argv[])
{
    char *inputfile;
    int token;
    int line, oldline;

    if (argc != 2) {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }

    inputfile = argv[1];

    init_symtab();              /* initialize the symbol table */

    yyin = fopen(inputfile, "r"); /* open the source file */
    if (yyin == NULL) {
        fprintf(stderr, "Cannot open input file '%s'\n", inputfile);
        exit(1);
    }

    oldline = 0;

    /* loop that keeps calling the scanner 
       (will soon be done by the parser) */

    while ((token = yylex()) > 0) {
        if (token == ID) {
            line = yylval.treenode->ident.line;
        } else if (token == INT || token == YONO) {
            line = yylval.treenode->type.line;
        } else if (token == CONST) {
            line = yylval.treenode->constant.line;
        } else {
            line = yylval.lexeme.line;
        }

        if (line != oldline) {
            oldline = line;
            printf("\nline %3d: ", line);
        }
    
        printf(" %s", tokenname[token-ID]);
        if (token == ID) {
            printf("(%s)", yylval.treenode->ident.STentry->lexptr);
        } else if (token == CONST) {
            printf("(%d)", yylval.treenode->constant.val);
        }
    }

    printf("\n");

    return 0;
}
