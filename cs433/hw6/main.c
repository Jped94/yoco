/* main.c
 *
 * Main program for CS 433 compiler project
 *
 * version for hw6
 */

static char usage[] = "\n\
  usage: %s [-t] [-y] [-p] sourcefile\n\
\n\
  options:\n\
        -t  print out syntax tree\n\
        -y  turn on yacc debugging\n\
        -p  print out productions\n\
        -d  print out declaration descriptors\n\
\n";


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <getopt.h>

#include "symtab.h"
#include "syntree.h"

int yyparse();
extern FILE *yyin;
extern int yydebug;
extern int PRINT_PRODUCTIONS;   /* defined in parser.y */

int errorcount;
void resolve(node *syntree);    /* defined in resolve.c */

void printdecldescs(node *syntree); /* defined in printdecl.c */

int main (int argc, char *argv[])
{
    int o;
    int ptree = 0;
    int pdecldescs = 0;
    char *inputfile = NULL;

    /* Parse the options */
    while ((o = getopt(argc, argv, "typd")) != -1)
        switch (o) {
        case 'y': yydebug = 1; break;           /* turn on yacc debugging */
        case 'p': PRINT_PRODUCTIONS = 1; break; /* print productions */
        case 't': ptree = 1; break;
        case 'd': pdecldescs = 1; break;
        default:
            fprintf(stderr, usage, argv[0]);
            exit(1);
        }
    if (argc == optind+1)
        inputfile = argv[optind];
    else {
        fprintf(stderr, usage, argv[0]);
        exit(1);
    }
  
    init_symtab();                /* initialize the symbol table */

    yyin = fopen(inputfile, "r"); /* open the source file */
    if (yyin == NULL) {
        fprintf(stderr, "Cannot open input file '%s'\n", inputfile);
        exit(1);
    }

    yyparse();                    /* invoke the parser */

    errorcount = 0;
    resolve(syntree);           /* do declaration resolution */

    if (ptree)
        printtree(syntree, 1);

    if (pdecldescs)
        printdecldescs(syntree);

    if (errorcount > 0)
        fprintf(stderr,"\n%d error%s detected.\n", errorcount,
                errorcount > 1 ? "s" : "");
  
    return 0;
}
