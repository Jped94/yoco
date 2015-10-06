/* symtab.c
 *
 * CS 433
 *
 * solutions for homework 1 by Daniel Scharstein
 * with some bugs for debugging exercise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

STrec *symtab[ST_SIZE];

/* Initialize the symbol table
 * Need to store NULL's in array
 */
void init_symtab()
{
    int i;

    for (i = 0; i < ST_SIZE; i++) // *** i--
	symtab[i] = NULL;
}


/* Compute a hash funtion used for identifiers
 * (e.g., simply the sum of all the letters in the identifier
 *  modulo the ST size) 
 */
int SThash(char *ident)
{
    int i, hash = 0;

    for(i = 0; ident[i] != '\0'; i++) // *** '0' -- results in unpredictable hashes
	hash += ident[i];

    return hash % ST_SIZE;  // ***use + instead of % results in hash values that are too high
}

/* Return pointer to ST record of lexeme s, or NULL if not found */
STrec *STlookup(char *s)
{
    STrec *node; // = (STrec *)malloc(sizeof(STrec)); // *** memory leak, can find with valgrind
    int hash = SThash(s);

    for (node = symtab[hash]; node != NULL; node = node->hashlink) { // *** node->hashlink != NULL
	if (strcmp(node->lexptr, s) == 0)
	    return node;
    }
    return NULL;
}


/* Insert lexeme s into symbol table and return pointer to new STrec */
STrec *STinsert(char *s)
{
    STrec *node;
    int hash = SThash(s);

    node = (STrec *)malloc(sizeof(STrec));
    node->lexptr = (char *)malloc(strlen(s)+1);
    strcpy(node->lexptr, s);

    /* insert 'node' at beginning of linked list at 'symtab[hash]' */
	
    node->hashlink = symtab[hash];
	symtab[hash] = node;   // *** swap lines, creates loop of hashlink back
    

    return node;
}
