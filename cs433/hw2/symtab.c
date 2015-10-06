/* symtab.c
 *
 * CS 433
 * 
 * Josh Pedowitz
 *
 * skeleton for homework 1
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
	/* Loop through array setting lexptr and hashlink to Null */
	int i;
	for (i = 0; i < ST_SIZE; i++){
		symtab[i] = NULL;
}
    
}


/* Compute a hash funtion used for identifiers
 * simply the sum of all the letters in the identifier
 * modulo the ST size 
 */
int SThash(char *ident)
{
	int asciiSum = 0;
	char *ptr;
	for (ptr = ident; *ptr != '\0'; ptr++) {
		asciiSum += *ptr;
		}
	return asciiSum % ST_SIZE;

}

/* Return pointer to ST record of lexeme s, or NULL if not found */
STrec *STlookup(char *s)
{
    /*Get the hash of s*/
	int hash = SThash(s);
 /*Check to see if there are any lexemes at the given hash index.
 If there were, compare the strings. If theyre not the same, go on to the next STrec.
 */


	STrec *recpt = NULL;
	if (symtab[hash]!= NULL) {
	 recpt = symtab[hash];
	}
	
	char *lex;
	STrec *link;

	do {
		if (recpt != NULL){

			lex = recpt->lexptr;
			link = recpt->hashlink;


			if (lex == NULL){
				return NULL;
			}

			else {
				if (strcmp(lex, s) == 0) {
					return recpt;
				}
				else {
					recpt = link;
				}
			}
	} else {return NULL;}


	} while (link != NULL);

	/*Looped through without finding anything, so return NULL */

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

    /* (need to insert 'node' at beginning of linked list at 'symtab[hash]') */
	STrec *oldSTrec = NULL;
	
	/* If there was an STrec at that index before, save it then place the pointer in node's hashlink */
	if (symtab[hash] != NULL) {
	oldSTrec = symtab[hash];
	}
	symtab[hash] = node;
	node->hashlink = oldSTrec;

    return node;
}
