/* main.c
 *
 * CS 433
 *
 * driver for homework 1: symbol table test
 */

static char usage[] = "\n  usage: %s sourcefile\n\n";

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "symtab.h"

#define BUF_SIZ 200	/* size of buffer used to store words */

/* return whether c is a letter */
int is_letter(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

/* Implementation of a very primitive scanner:
 * consecutive strings of letters are treated as words and inserted
 * into the symbol table.  Everything else is ignored.
 */
int main (int argc, char *argv[])
{
    FILE *infile;
    char buffer[BUF_SIZ];
    char c;
    int i;
    
    if (argc != 2) {
	fprintf(stderr, usage, argv[0]);
	exit(1);
    }

    /* open file specified on command line for reading */
    infile = fopen(argv[1], "r");
    if (infile == NULL) {
        fprintf(stderr, "Cannot open input file\n");
        exit(1);
    }
    init_symtab();
  
    c = getc(infile);	        /* read first character */
    while (c != EOF) {		/* repeatedly look for words */
	if (is_letter(c)) {     /* found beginning of word */
	    i = 0;
	    buffer[i++] = c;		/* start copying into buffer */
	    while (is_letter(c = getc(infile)) && i < BUF_SIZ)
		buffer[i++] = c;	/* keep copying all letters into buffer */
	    assert(i < BUF_SIZ);	/* make sure buffer didn't overflow */
	    buffer[i] = 0;		/* terminate word with '0' */
	    if (STlookup(buffer) == NULL) {	/* check if word isn't already in ST */
		STinsert(buffer);	/* if not, insert it */
		printf("insert:   %s\n", buffer);
	    }
	    else
		printf("previously seen:   %s\n", buffer);
	}
	/* if we get to here, c is not a letter */
	while ((c != EOF) && (!is_letter(c)))
	    c = getc(infile);	/* keep skipping non-letters */
	/* now, c is either a letter or EOF */
    }
  
    return 0;
}
