#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20130304

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 7 "parser.y"
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

#line 37 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define ID 257
#define CONST 258
#define INT 259
#define YONO 260
#define GLOBAL 261
#define RETWEET 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define END 266
#define OR 267
#define AND 268
#define NOT 269
#define LIKE 270
#define REF 271
#define HASH 272
#define LT 273
#define LE 274
#define GT 275
#define GE 276
#define PLUS 277
#define MINUS 278
#define MULT 279
#define DIV 280
#define MOD 281
#define ASSIGN 282
#define COLON 283
#define BANG 284
#define LPAREN 285
#define RPAREN 286
#define LBRACK 287
#define RBRACK 288
#define DOTDOT 289
#define COMMA 290
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    3,    3,    4,    4,    5,    5,
    6,    6,    7,    7,    8,    8,    9,    9,   10,   10,
   11,   11,   12,   12,   12,   13,   13,   14,   14,   14,
   14,   14,   14,   15,   16,   16,   17,   17,   18,   18,
   19,   20,   20,   20,   21,   22,   22,   23,   23,   24,
   24,   25,   25,   26,   26,   26,   26,   26,   26,   26,
   27,   27,   27,   28,   28,   28,   28,   29,   29,   29,
   29,   29,
};
static const short yylen[] = {                            2,
    2,    0,    3,    3,    1,    6,    1,    1,    1,    2,
    1,    3,    2,    4,    0,    2,    8,    9,    0,    1,
    1,    3,    3,    4,    5,    0,    2,    1,    1,    2,
    1,    1,    1,    4,    2,    5,    3,    4,    2,    3,
    7,    0,    6,    3,    6,    1,    3,    1,    3,    1,
    3,    1,    2,    1,    3,    3,    3,    3,    3,    4,
    1,    3,    3,    1,    3,    3,    3,    2,    1,    1,
    1,    3,
};
static const short yydefred[] = {                         2,
    0,    0,    0,    0,    7,    8,    3,    0,    0,    0,
    0,   16,    0,    0,   11,    0,    0,    0,    0,    4,
    0,    9,    0,    0,    0,    0,    0,    0,   21,    0,
    0,   12,   10,    0,    0,    0,    0,    0,    0,    0,
    0,   71,    0,    0,    0,    0,   69,   70,    0,    0,
   50,   52,    0,    0,   64,    0,    0,   23,    0,   26,
   22,    0,    0,   53,    0,   68,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    6,   24,    0,    0,   26,   37,    0,    0,    0,   72,
    0,   51,    0,    0,    0,    0,    0,    0,    0,    0,
   65,   66,   67,   25,    0,    0,    0,    0,   28,   27,
   29,    0,    0,   31,   32,   33,    0,   38,    0,    0,
    0,   39,    0,    0,    0,   17,    0,   30,    0,    0,
   36,   40,   26,   26,    0,   18,    0,    0,   34,    0,
    0,    0,    0,   26,    0,   45,    0,    0,   41,   26,
    0,   43,
};
static const short yydgoto[] = {                          1,
    2,  109,    8,    9,   24,   14,   15,    4,   12,   27,
   28,   29,   84,  110,  111,   47,   48,  114,  115,  141,
  116,   87,   49,   50,   51,   52,   53,   54,   55,
};
static const short yysindex[] = {                         0,
    0, -238, -123,  -89,    0,    0,    0, -253, -240, -233,
 -203,    0, -173, -276,    0, -251, -177, -194, -181,    0,
 -253,    0, -154, -161, -123, -267, -179, -178,    0, -177,
 -180,    0,    0, -251, -125, -105, -134, -114, -177, -112,
 -109,    0, -172,  -79, -172, -180,    0,    0,  -83,  -74,
    0,    0,   90,  -37,    0, -103,  -62,    0,  -72,    0,
    0,  -85, -236,    0,  -81,    0, -221, -180, -180,  -68,
 -172, -172, -172, -172, -172, -172, -172, -172, -172, -172,
    0,    0,  -50,   45,    0,    0, -242,  -83, -180,    0,
  -74,    0, -172, -133, -133, -133, -133, -133,  -37,  -37,
    0,    0,    0,    0, -182, -180, -180,  -66,    0,    0,
    0,  -60,  -65,    0,    0,    0,   56,    0, -180, -254,
 -133,    0, -222, -216, -195,    0, -180,    0,  -58,  -83,
    0,    0,    0,    0, -214,    0,   67,   78,    0, -252,
  -56,  -53, -180,    0,  -48,    0, -188,   89,    0,    0,
   67,    0,
};
static const short yyrindex[] = {                         0,
    0,    1,    0,  212,    0,    0,    0,    0,  -44,    0,
    0,    0,    0,    0,    0,    0,  -52,    0, -272,    0,
    0,    0,    0,    0,    0,    0,    0,  -45,    0,  -52,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0, -191,    4,
    0,    0, -258, -135,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -159,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0, -160,    0,    0,
   13,    0,    0,  -75,  -63,  -51,  -38,  -14, -111,  -87,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   -5,    0,    0,    0,    0,    0,    0,    0,    0, -140,
    0,    0,    0,    0,    0,    0,  -42,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -28,    0,    0,
  -42,    0,
};
static const short yygindex[] = {                         0,
    0,  211,    0,   -1,  206,    0,  226,    0,    0,  219,
    0,  216,  -70,    0,    0,  -82,  -80,    0,    0,  100,
    0,    0,  -46,  188,  190,  214,  193,   84,  -39,
};
#define YYTABLESIZE 368
static const short yytable[] = {                         67,
   15,  112,   11,  113,   36,   66,   22,   20,   54,   54,
  143,   13,   68,   21,  117,   26,   88,   13,   13,   37,
   41,   42,    3,   35,   54,   54,   23,   54,   26,   54,
  144,   54,   43,  131,  112,   44,  113,   26,  101,  102,
  103,   45,  120,  118,   68,   68,   16,  119,   46,   86,
   68,   17,   68,   18,  112,  112,  113,  113,  123,  124,
  125,  132,  137,  138,   90,  112,  133,  113,  112,  139,
  113,   68,  130,  148,   41,   42,   41,   42,   68,  151,
  135,    5,    6,   19,   41,   42,   43,  134,   43,   44,
   30,   44,   14,   25,  150,   45,  147,   45,   14,   44,
   31,  122,   46,   33,   46,   45,   38,   35,   35,   35,
   35,   39,   46,   35,   35,   35,   35,   35,   35,   35,
   35,   35,   35,   35,   35,   46,   35,   34,   35,   46,
   35,   61,   61,   61,   61,    5,    6,   61,   61,   61,
   61,   61,   61,   76,   77,   47,   57,   61,   61,   47,
   61,   58,   61,   59,   61,   62,   62,   62,   62,   99,
  100,   62,   62,   62,   62,   62,   62,   10,   60,    5,
    6,   62,   62,   62,   62,   63,   62,   65,   62,   63,
   63,   63,   63,   68,   81,   63,   63,   63,   63,   63,
   63,   59,   59,   69,   82,   63,   63,   85,   63,   83,
   63,   93,   63,   55,   55,   89,  104,   59,   59,  145,
   59,    1,   59,    7,   59,   56,   56,  126,  128,   55,
   55,  127,   55,   42,   55,  136,   55,    5,   57,   57,
  146,   56,   56,   19,   56,  149,   56,   44,   56,   56,
   20,   78,   79,   80,   57,   57,   32,   57,   40,   57,
  152,   57,   58,   58,   61,   91,   64,   15,   92,   15,
   15,   60,   60,   94,   95,   96,   97,   98,   58,   58,
   48,   58,    0,   58,    0,   58,    0,   60,   60,   49,
   60,    0,   60,    0,   60,  121,   48,   48,    0,   48,
    0,   48,    0,   48,    0,   49,   49,    0,   49,    0,
   49,   41,   49,    5,    6,    0,  105,  106,    0,  107,
  108,    0,   41,    0,    5,    6,   44,  105,  106,    0,
  107,  129,    0,   41,    0,    5,    6,   44,  105,  106,
  140,  107,    0,    0,   41,    0,    5,    6,   44,  105,
  106,    0,  107,  142,    0,   41,    0,    5,    6,   44,
  105,  106,    0,  107,    0,    0,    0,    0,   70,   71,
   44,    0,   72,   73,   74,   75,   76,   77,
};
static const short yycheck[] = {                         46,
    0,   84,    4,   84,  272,   45,  258,  284,  267,  268,
  263,  284,  267,  290,   85,   17,   63,  290,  272,  287,
  257,  258,  261,   25,  283,  284,  278,  286,   30,  288,
  283,  290,  269,  288,  117,  272,  117,   39,   78,   79,
   80,  278,   89,  286,  267,  267,  287,  290,  285,  286,
  267,  285,  267,  257,  137,  138,  137,  138,  105,  106,
  107,  284,  133,  134,  286,  148,  283,  148,  151,  284,
  151,  267,  119,  144,  257,  258,  257,  258,  267,  150,
  127,  259,  260,  257,  257,  258,  269,  283,  269,  272,
  285,  272,  284,  271,  283,  278,  143,  278,  290,  272,
  282,  284,  285,  258,  285,  278,  286,  267,  268,  269,
  270,  290,  285,  273,  274,  275,  276,  277,  278,  279,
  280,  281,  282,  283,  284,  286,  286,  289,  288,  290,
  290,  267,  268,  269,  270,  259,  260,  273,  274,  275,
  276,  277,  278,  277,  278,  286,  272,  283,  284,  290,
  286,  257,  288,  288,  290,  267,  268,  269,  270,   76,
   77,  273,  274,  275,  276,  277,  278,  257,  283,  259,
  260,  283,  284,  286,  286,  285,  288,  257,  290,  267,
  268,  269,  270,  267,  288,  273,  274,  275,  276,  277,
  278,  267,  268,  268,  257,  283,  284,  283,  286,  272,
  288,  270,  290,  267,  268,  287,  257,  283,  284,  266,
  286,    0,  288,    3,  290,  267,  268,  284,  284,  283,
  284,  282,  286,  266,  288,  284,  290,  272,  267,  268,
  284,  283,  284,  286,  286,  284,  288,  266,  290,   34,
  286,  279,  280,  281,  283,  284,   21,  286,   30,  288,
  151,  290,  267,  268,   39,   68,   43,  257,   69,  259,
  260,  267,  268,   71,   72,   73,   74,   75,  283,  284,
  267,  286,   -1,  288,   -1,  290,   -1,  283,  284,  267,
  286,   -1,  288,   -1,  290,   93,  283,  284,   -1,  286,
   -1,  288,   -1,  290,   -1,  283,  284,   -1,  286,   -1,
  288,  257,  290,  259,  260,   -1,  262,  263,   -1,  265,
  266,   -1,  257,   -1,  259,  260,  272,  262,  263,   -1,
  265,  266,   -1,  257,   -1,  259,  260,  272,  262,  263,
  264,  265,   -1,   -1,  257,   -1,  259,  260,  272,  262,
  263,   -1,  265,  266,   -1,  257,   -1,  259,  260,  272,
  262,  263,   -1,  265,   -1,   -1,   -1,   -1,  269,  270,
  272,   -1,  273,  274,  275,  276,  277,  278,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 290
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"ID","CONST","INT","YONO",
"GLOBAL","RETWEET","IF","ELSE","WHILE","END","OR","AND","NOT","LIKE","REF",
"HASH","LT","LE","GT","GE","PLUS","MINUS","MULT","DIV","MOD","ASSIGN","COLON",
"BANG","LPAREN","RPAREN","LBRACK","RBRACK","DOTDOT","COMMA",
};
static const char *yyrule[] = {
"$accept : program",
"program : globlist funlist",
"globlist :",
"globlist : globlist GLOBAL vardecl",
"vardecl : type decllist BANG",
"type : basictype",
"type : basictype LBRACK sconst DOTDOT sconst RBRACK",
"basictype : INT",
"basictype : YONO",
"sconst : CONST",
"sconst : MINUS CONST",
"decllist : decl",
"decllist : decllist COMMA decl",
"decl : HASH ID",
"decl : HASH ID ASSIGN expr",
"funlist :",
"funlist : funlist fundecl",
"fundecl : ID LPAREN params RPAREN COLON stmtlist END BANG",
"fundecl : basictype ID LPAREN params RPAREN COLON stmtlist END BANG",
"params :",
"params : paramlist",
"paramlist : param",
"paramlist : paramlist COMMA param",
"param : basictype HASH ID",
"param : REF basictype HASH ID",
"param : basictype LBRACK RBRACK HASH ID",
"stmtlist :",
"stmtlist : stmtlist stmt",
"stmt : vardecl",
"stmt : assignment",
"stmt : funcall BANG",
"stmt : retstmt",
"stmt : ifstmt",
"stmt : whilestmt",
"assignment : variable ASSIGN expr BANG",
"variable : HASH ID",
"variable : HASH ID LBRACK expr RBRACK",
"funcall : ID LPAREN RPAREN",
"funcall : ID LPAREN exprlist RPAREN",
"retstmt : RETWEET BANG",
"retstmt : RETWEET expr BANG",
"ifstmt : IF expr COLON stmtlist elsestmt END BANG",
"elsestmt :",
"elsestmt : ELSE IF expr COLON stmtlist elsestmt",
"elsestmt : ELSE COLON stmtlist",
"whilestmt : WHILE expr COLON stmtlist END BANG",
"exprlist : expr",
"exprlist : exprlist COMMA expr",
"expr : logterm",
"expr : expr OR logterm",
"logterm : logfactor",
"logterm : logterm AND logfactor",
"logfactor : relexpr",
"logfactor : NOT relexpr",
"relexpr : arithexpr",
"relexpr : arithexpr LT arithexpr",
"relexpr : arithexpr LE arithexpr",
"relexpr : arithexpr GT arithexpr",
"relexpr : arithexpr GE arithexpr",
"relexpr : arithexpr LIKE arithexpr",
"relexpr : arithexpr NOT LIKE arithexpr",
"arithexpr : term",
"arithexpr : arithexpr PLUS term",
"arithexpr : arithexpr MINUS term",
"term : factor",
"term : term MULT factor",
"term : term DIV factor",
"term : term MOD factor",
"factor : MINUS factor",
"factor : variable",
"factor : funcall",
"factor : CONST",
"factor : LPAREN expr RPAREN",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 410 "parser.y"

/* report parsing error (required by yacc) */
void yyerror(char *s)
{
    fprintf(stderr, "line %d: %s\n", curlineno, s);
}
#line 405 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 100 "parser.y"
	{ syntree = makenode2(Nprogram, yystack.l_mark[-1].treenode, yystack.l_mark[0].treenode,
                                  yystack.l_mark[-1].treenode? yystack.l_mark[-1].treenode->internal.line :
                                  (yystack.l_mark[0].treenode? yystack.l_mark[0].treenode->internal.line :
                                   1)); /* line number for empty prog... */
              production("program -> globlist funlist\n"); yyval.treenode = NULL; }
break;
case 2:
#line 110 "parser.y"
	{ yyval.treenode = NULL;
                  production("globlist -> epsilon\n"); }
break;
case 3:
#line 114 "parser.y"
	{ yyval.treenode = makelist(Ngloblist, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-1].lexeme.line);
                  production("globlist -> globlist GLOBAL vardecl\n"); }
break;
case 4:
#line 119 "parser.y"
	{ yyval.treenode = makenode2(Nvardecl, yystack.l_mark[-2].treenode, yystack.l_mark[-1].treenode, yystack.l_mark[-2].treenode->internal.line) ;
                  production("vardecl -> type decllist !\n"); }
break;
case 5:
#line 124 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                  production("type -> basictype \n"); }
break;
case 6:
#line 127 "parser.y"
	{ yyval.treenode = makenode3(Narraytype, yystack.l_mark[-5].treenode, yystack.l_mark[-3].treenode, yystack.l_mark[-1].treenode, yystack.l_mark[-5].treenode->internal.line); 
                  production("type -> basictype [ sconst .. sconst ]\n"); }
break;
case 7:
#line 132 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("basictype -> INT\n"); }
break;
case 8:
#line 135 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("basictype -> YONO\n"); }
break;
case 9:
#line 140 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("sconst -> CONST\n"); }
break;
case 10:
#line 143 "parser.y"
	{ yystack.l_mark[0].treenode->constant.val = yystack.l_mark[0].treenode->constant.val*-1; yyval.treenode = yystack.l_mark[0].treenode; 
                production("sconst -> - CONST\n"); }
break;
case 11:
#line 148 "parser.y"
	{ yyval.treenode = makelist(Ndecllist, NULL, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("decllist -> decl\n"); }
break;
case 12:
#line 151 "parser.y"
	{ yyval.treenode = makelist(Ndecllist, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("decllist -> decllist , decl\n"); }
break;
case 13:
#line 156 "parser.y"
	{ yyval.treenode = makenode2(Ndecl, yystack.l_mark[0].treenode, NULL, yystack.l_mark[0].treenode->internal.line); 
                production("decl -> # ID\n"); }
break;
case 14:
#line 159 "parser.y"
	{ yyval.treenode = makenode2(Ndecl, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("decl -> # ID @ expr\n"); }
break;
case 15:
#line 164 "parser.y"
	{ yyval.treenode = NULL; 
                production("funlist -> epsilon\n");}
break;
case 16:
#line 167 "parser.y"
	{ yyval.treenode = makelist(Nfunlist, yystack.l_mark[-1].treenode, yystack.l_mark[0].treenode, 
                                  yystack.l_mark[-1].treenode? yystack.l_mark[-1].treenode->internal.line :
                                  (yystack.l_mark[0].treenode? yystack.l_mark[0].treenode->internal.line :
                                   1)); 
                production("funlist -> fundecl funlist\n");}
break;
case 17:
#line 175 "parser.y"
	{ yyval.treenode = makenode4(Nfundecl, NULL, yystack.l_mark[-7].treenode, yystack.l_mark[-5].treenode, yystack.l_mark[-2].treenode, yystack.l_mark[-7].treenode->internal.line); 
                production("fundecl -> ID ( params ): stmtlist END !\n");}
break;
case 18:
#line 178 "parser.y"
	{ yyval.treenode = makenode4(Nfundecl, yystack.l_mark[-8].treenode, yystack.l_mark[-7].treenode, yystack.l_mark[-5].treenode, yystack.l_mark[-2].treenode, yystack.l_mark[-8].treenode->internal.line); 
                production("fundecl -> basictype ID ( params ): stmtlist END !\n");}
break;
case 19:
#line 183 "parser.y"
	{ yyval.treenode = NULL; 
                production("params -> epsilon\n");}
break;
case 20:
#line 186 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("params -> paramlist\n");}
break;
case 21:
#line 191 "parser.y"
	{ yyval.treenode = makelist(Nparamlist, NULL, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("paramlist -> param\n");}
break;
case 22:
#line 194 "parser.y"
	{ yyval.treenode = makelist(Nparamlist, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("paramlist -> paramlist , param\n");}
break;
case 23:
#line 199 "parser.y"
	{ yyval.treenode = makenode2(Nvalparam, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("param -> basictype # ID\n");}
break;
case 24:
#line 202 "parser.y"
	{ yyval.treenode = makenode2(Nrefparam, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("param -> REF basictype # ID\n");}
break;
case 25:
#line 205 "parser.y"
	{ yyval.treenode = makenode2(Narrparam, yystack.l_mark[-4].treenode, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("param -> basictype [ ] # ID\n");}
break;
case 26:
#line 210 "parser.y"
	{ yyval.treenode = NULL; 
                production("stmtlist -> epsilon\n");}
break;
case 27:
#line 213 "parser.y"
	{ yyval.treenode = makelist(Nstmtlist, yystack.l_mark[-1].treenode, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("stmtlist -> stmtlist stmt\n");}
break;
case 28:
#line 218 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("stmt -> vardecl\n");}
break;
case 29:
#line 221 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("stmt -> assignment\n");}
break;
case 30:
#line 224 "parser.y"
	{ yyval.treenode = yystack.l_mark[-1].treenode; 
                production("stmt -> funcall !\n");}
break;
case 31:
#line 227 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("stmt -> retstmt\n");}
break;
case 32:
#line 230 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("stmt -> ifstmt\n");}
break;
case 33:
#line 233 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("stmt -> whilestmt\n");}
break;
case 34:
#line 238 "parser.y"
	{ yyval.treenode = makenode2(Nassign, yystack.l_mark[-3].treenode, yystack.l_mark[-1].treenode, yystack.l_mark[-3].treenode->internal.line); 
                production("assignment -> variable @ expr !\n");}
break;
case 35:
#line 243 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("variable -> # ID\n");}
break;
case 36:
#line 246 "parser.y"
	{ yyval.treenode = makenode2(Narray, yystack.l_mark[-3].treenode, yystack.l_mark[-1].treenode, yystack.l_mark[-4].lexeme.line); 
                production("variable -> # ID [ expr ]\n");}
break;
case 37:
#line 252 "parser.y"
	{ yyval.treenode = makenode2(Nfuncall, yystack.l_mark[-2].treenode, NULL, yystack.l_mark[-2].treenode->internal.line); 
                production("funcall -> ID ( )\n");}
break;
case 38:
#line 255 "parser.y"
	{ yyval.treenode = makenode2(Nfuncall, yystack.l_mark[-3].treenode, yystack.l_mark[-1].treenode, yystack.l_mark[-3].treenode->internal.line); 
                production("funcall -> ID ( exprlist )\n");}
break;
case 39:
#line 260 "parser.y"
	{ yyval.treenode = makenode1(Nreturn, NULL, yystack.l_mark[-1].lexeme.line); 
                production("retstmt -> RETWEET !\n");}
break;
case 40:
#line 263 "parser.y"
	{ yyval.treenode = makenode1(Nreturn, yystack.l_mark[-1].treenode, yystack.l_mark[-1].treenode->internal.line); 
                production("retstmt -> RETWEET expr !\n");}
break;
case 41:
#line 268 "parser.y"
	{ yyval.treenode = makenode3(Nif, yystack.l_mark[-5].treenode, yystack.l_mark[-3].treenode, yystack.l_mark[-2].treenode, yystack.l_mark[-6].lexeme.line); 
                production("ifstmt -> IF expr : stmtlist elsestmt END !\n");}
break;
case 42:
#line 273 "parser.y"
	{ yyval.treenode = NULL; 
                production("elsestmt -> epsilon\n");}
break;
case 43:
#line 276 "parser.y"
	{ yyval.treenode = makenode3(Nelseif, yystack.l_mark[-3].treenode, yystack.l_mark[-1].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-5].lexeme.line); 
                production("elsestmt -> ELSE IF expr : stmtlist elsestmt\n");}
break;
case 44:
#line 279 "parser.y"
	{ yyval.treenode = makenode1(Nelse, yystack.l_mark[0].treenode, yystack.l_mark[-2].lexeme.line); 
                production("elsestmt -> ELSE : stmtlist\n");}
break;
case 45:
#line 284 "parser.y"
	{ yyval.treenode = makenode2(Nwhile, yystack.l_mark[-4].treenode, yystack.l_mark[-2].treenode, yystack.l_mark[-5].lexeme.line); 
                production("whilestmt -> WHILE expr : stmtlist END !\n");}
break;
case 46:
#line 289 "parser.y"
	{ yyval.treenode = makelist(Nexprlist, NULL, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("exprlist -> expr\n");}
break;
case 47:
#line 292 "parser.y"
	{ yyval.treenode = makelist(Nexprlist, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("exprlist -> exprlist , expr\n");}
break;
case 48:
#line 297 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("expr -> logterm\n");}
break;
case 49:
#line 300 "parser.y"
	{ yyval.treenode = makenode2(Nor, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("expr -> expr OR logterm\n");}
break;
case 50:
#line 305 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("logterm -> logfactor\n");}
break;
case 51:
#line 308 "parser.y"
	{ yyval.treenode = makenode2(Nand, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("logterm -> logterm AND logfactor\n");}
break;
case 52:
#line 313 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("logfactor -> relexpr\n");}
break;
case 53:
#line 316 "parser.y"
	{ yyval.treenode = makenode1(Nnot, yystack.l_mark[0].treenode, yystack.l_mark[-1].lexeme.line); 
                production("logfactor -> NOT relexpr\n");}
break;
case 54:
#line 321 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production ("relexpr -> arithexpr\n");}
break;
case 55:
#line 324 "parser.y"
	{ yyval.treenode = makenode2(Nlt, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production ("relexpr -> arithexpr < arithexpr\n");}
break;
case 56:
#line 327 "parser.y"
	{ yyval.treenode = makenode2(Nle, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production ("relexpr -> arithexpr <= arithexpr\n");}
break;
case 57:
#line 330 "parser.y"
	{ yyval.treenode = makenode2(Ngt, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production ("relexpr -> arithexpr > arithexpr\n");}
break;
case 58:
#line 333 "parser.y"
	{ yyval.treenode = makenode2(Nge, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production ("relexpr -> arithexpr >= arithexpr\n");}
break;
case 59:
#line 336 "parser.y"
	{ yyval.treenode = makenode2(Neq, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production ("relexpr -> arithexpr LIKE arithexpr\n");}
break;
case 60:
#line 339 "parser.y"
	{ yyval.treenode = makenode2(Nne, yystack.l_mark[-3].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-3].treenode->internal.line); 
                production ("relexpr -> arithexpr NOT LIKE arithexpr\n");}
break;
case 61:
#line 344 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("arithexpr -> term\n"); }
break;
case 62:
#line 347 "parser.y"
	{ yyval.treenode = makenode2(Nplus, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("arithexpr -> arithexpr + term\n"); }
break;
case 63:
#line 350 "parser.y"
	{ yyval.treenode = makenode2(Nminus, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("arithexpr -> arithexpr - term\n"); }
break;
case 64:
#line 355 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("term -> factor\n");}
break;
case 65:
#line 358 "parser.y"
	{ yyval.treenode = makenode2(Ntimes, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("term -> term * factor\n");}
break;
case 66:
#line 361 "parser.y"
	{ yyval.treenode = makenode2(Ndiv, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("term -> term / factor\n");}
break;
case 67:
#line 364 "parser.y"
	{ yyval.treenode = makenode2(Nmod, yystack.l_mark[-2].treenode, yystack.l_mark[0].treenode, yystack.l_mark[-2].treenode->internal.line); 
                production("term -> term MOD factor\n");}
break;
case 68:
#line 369 "parser.y"
	{ yyval.treenode = makenode1(Nneg, yystack.l_mark[0].treenode, yystack.l_mark[0].treenode->internal.line); 
                production("factor -> - factor\n");}
break;
case 69:
#line 372 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("factor -> variable\n");}
break;
case 70:
#line 375 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("factor -> funcall\n");}
break;
case 71:
#line 378 "parser.y"
	{ yyval.treenode = yystack.l_mark[0].treenode; 
                production("factor -> CONST\n");}
break;
case 72:
#line 381 "parser.y"
	{ yyval.treenode = yystack.l_mark[-1].treenode; 
                production("factor -> ( expr )\n");}
break;
#line 977 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
