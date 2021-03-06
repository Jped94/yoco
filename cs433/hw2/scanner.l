/* scanner.l
 *
 * CS 433 - input file for lex
 *
 * HW 2
 * Josh Pedowitz, based on Code by Daniel Scharstein
 */

/* lexical definitions for #YOCO */

%{
#include <string.h>
#include <stdlib.h>
#include "symtab.h"
#include "syntree.h"
#include "syntax.h"
#include "tokens.h"

int num = 0;
int curlineno = 1;

YYSTYPE yylval;

#define RETURN(toknum) yylval.lexeme.line = curlineno; return(toknum)

void create_ident_node();
void create_type_node(basictype t);
void create_const_node(basictype t);

%}

/* regular definitions */


id 				[A-Za-z][A-Za-z0-9_]*
numconst		-?[0-9]+
sinquote 		"\\'"
backslash		"\\\\"
newline 		"\n"
charconst		'[a-zA-Z!-&(-.:-@[-`{-~^']+'
comment			["//"]+.*
multiline		\/\*([^*]|\*[^/])*\*+\/
ws 			    ["\t" ]*
illegal			.
 
/* rules and actions are next: */
%%


retweet         {RETURN(RETWEET);}
global			{RETURN(GLOBAL);}
if				{RETURN(IF);}
else			{RETURN(ELSE);}
while			{RETURN(WHILE);}
end				{RETURN(END);}
or				{RETURN(OR);}
and				{RETURN(AND);}
not				{RETURN(NOT);}
like			{RETURN(LIKE);}
ref				{RETURN(REF);}
"#"				{RETURN(HASH);}
"<"				{RETURN(LT);}	
"<="			{RETURN(LE);}
">"				{RETURN(GT);}
">="			{RETURN(GE);}
"+"				{RETURN(PLUS);}
"-"				{RETURN(MINUS);}
"*"				{RETURN(MULT);}
"/"				{RETURN(DIV);}
"%"				{RETURN(MOD);}
"@"				{RETURN(ASSIGN);}
":"				{RETURN(COLON);}
"!"				{RETURN(BANG);}	
"("				{RETURN(LPAREN);}
")"				{RETURN(RPAREN);}
"["				{RETURN(LBRACK);}
"]"				{RETURN(RBRACK);}
".."			{RETURN(DOTDOT);}
","				{RETURN(COMMA);}
int             {create_type_node(integer); return(INT);}
yono			{create_type_node(bool); return(YONO);}
yo              {create_const_node(bool); return(CONST);}
no				{create_const_node(bool); return(CONST);}
{id}            {create_ident_node(); return(ID);}
{newline}		{printf("\n"); curlineno++;}
{sinquote}		{create_const_node(integer); return(CONST);}
{backslash}		{create_const_node(integer); return(CONST);}
{numconst}      {create_const_node(integer); return(CONST);}
{charconst}     {create_const_node(integer); return(CONST);}
{ws} 			{printf("");}
{comment}		{printf("");}
{multiline}		{printf("");}
{illegal}		{printf("Error: Illegal Character");}



%%
/* user functions: */

/* First, install the lexeme, whose first character is pointed to
   by yytext and whose length is yyleng, into the symbol table.
   Then create an "identnode" leaf for the syntax tree. */

void create_ident_node(void) 
{
    STrec *p = STlookup(yytext);
    if (p == NULL)                /* insert s into symbol table */
	p = STinsert(yytext);

    yylval.treenode = (node *)malloc(sizeof(struct identnode));
    yylval.treenode->ident.type = Nident;
    yylval.treenode->ident.line = curlineno;
    yylval.treenode->ident.STentry = p;
}

/* For integer or bool, create a "typenode" leaf for the syntax tree. */
void create_type_node(basictype t)
{
    yylval.treenode = (node *)malloc(sizeof(struct typenode));
    yylval.treenode->type.type = Ntype;
    yylval.treenode->type.line = curlineno;
    yylval.treenode->type.typespec = t;
}

/* For numbers and 'yo'/'no', create a "constnode" leaf for the syntax tree. */
void create_const_node(basictype t)
{
    yylval.treenode = (node *)malloc(sizeof(struct constnode));
    yylval.treenode->constant.type = Nconst;
    yylval.treenode->constant.line = curlineno;
    yylval.treenode->constant.typespec = t;

    /*
        need to look at the lexeme (yytext) and store the value
	of the constant in yylval.treenode->constant.val

	if t == bool store 0 or 1
	if t == integer store numerical value of integers or char constants

    */

	if (t == bool){
		if (yytext == "yo"){
			yylval.treenode->constant.val = 1;
		} else {
			yylval.treenode->constant.val = 0;
		}
	}
	
	else if (t == integer) {
		
		if (yytext[0] == '\''){
			if (yytext[1] != '\\'){
				yylval.treenode->constant.val = yytext[1];
			}
			else {yylval.treenode->constant.val = yytext[2];}
		}
		else {
			yylval.treenode->constant.val = atoi(yytext);
		}
	
	}
			
		
		
}

int yywrap() 
{
    return(1);
}       
