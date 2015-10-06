/* symtab.h
 *
 * CS 433
 *
 * symbol table definitions for homework 1
 */

/* size of the symbol table (should be prime for good hash distribution) */
#define ST_SIZE 407

/* Structure specification for symbol table records.  There will be
 * one of these records for each distinct identifier encountered in
 * the program.  They are allocated and initialized by the scanner.
 */

typedef struct strec {
    char *lexptr;             /* pointer to lexeme */
    struct strec *hashlink;   /* Link for hash chains */
} STrec;

/**************************************************************************/
/* declarations for symbol table manipulation routines */

/* Initialize the symbol table  */
void init_symtab();

/* Return pointer to ST record of lexeme s, or NULL if not found */
STrec *STlookup(char *s);

/* Insert lexeme s into symbol table and return pointer to new STrec */
STrec *STinsert(char *s);

/**************************************************************************/
