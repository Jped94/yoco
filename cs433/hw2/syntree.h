/* syntree.h
 *
 * CS 433
 *
 * Definitions for syntax tree
 *
 * preliminary version for hw 2
 */

/* Number of child pointers required in syntax tree nodes */
#define MAXKIDS 3       
                   
/* Enumeration type whose elements are used as phrase-type labels
 * in syntax tree nodes */
typedef enum nodeenum {

    /* leaf nodes */
    Nident,
    Ntype,
    Nconst,

    /* internal nodes - to come soon... */
} nodetype;

/* Syntax tree nodes come in four different flavors: internal nodes,
 * or one of the three leaf types (Nident, Ntype, Nconst).  The following
 * structure declarations describe each of the different types.  All
 * types of node begin with a 'type' field that is used to hold the
 * phrase-type of the node.  This field is sufficient to determine the
 * type and therefore the layout of the remainder of the node.  All
 * nodes also contain a 'line' component which indicates the source
 * line on which the first character belonging to the phrase
 * represented by the node occurred.  
 */

/* The type 'unknode' provides a template that can be used to access
 * the common components found in all node types when the actual type
 * of the node is unknown.
 */
struct unknode {
    nodetype type;
    int line;
};

/* Nodes of type 'internalnode' are used for all nodes that are
 * internal to the tree.
 */
struct internalnode {
    nodetype type;
    int line;
    union nodeunion *child[MAXKIDS]; /* pointers to the node's sub-trees */
};

/* Nodes of type 'ident' are used for leaf nodes corresponding to
 * identifiers in the source code.  The value in the 'type' component
 * of such a node will always be 'Nident'.
 */
struct identnode {
    nodetype type;
    int line;
    STrec *STentry;      /* Pointer to associated symbol table entry  */
};

/* Nodes of type 'typenode' are used for leaf nodes corresponding to
 * basic type specifications (integer and bool) in the source code.  The
 * value in the 'type' component of such a node will always be 'Ntype'.
 */

typedef enum basictypeenum {
    integer,
    bool
} basictype;

struct typenode {
    nodetype type;
    int line;
    basictype typespec;   /* integer or bool */
};

/* Nodes of type 'const' are used for leaf nodes corresponding to
 * constants (integers and 'yes'/'no') in the source code.  The value
 * in the 'type' component of such a node will always be 'Nconst'.
 */
struct constnode {
    nodetype type;
    int line;
    basictype typespec;	/* type of the constant (integer or bool) */
    int val;	   	/* value of the constant (use 0 and 1 for bool) */
};

/* Union type that combines the structure types described above */
typedef union nodeunion {
    struct unknode unk;
    struct internalnode internal;
    struct identnode ident;
    struct typenode type;
    struct constnode constant;
} node;
