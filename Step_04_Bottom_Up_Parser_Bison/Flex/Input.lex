%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include "../../HEADER_FILES/util.h"
#include "../../HEADER_FILES/errormsg.h"

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include "../Parser/AST.h"

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include "../Bison/tiger.tab.h"

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

int charPos=1;

int yywrap(void)
{
 charPos=1;
 return 1;
}


void adjust(void)
{
 EM_tokPos=charPos;
 charPos+=yyleng;
}

%}

%%
" "									{adjust(); continue;}
\n									{adjust(); EM_newline(); continue;}
\t									{adjust(); return TAB;}
","									{adjust(); return COMMA;}
";"									{adjust(); return SEMICOLON;}
for									{adjust(); return FOR;}
while								{adjust(); return WHILE;}
"("									{adjust(); return LPAREN;}
")"									{adjust(); return RPAREN;}
"["									{adjust(); return LBRACK;}
"]"									{adjust(); return RBRACK;}
"{"									{adjust(); return LBRACE;}
"}"									{adjust(); return RBRACE;}
"+"									{adjust(); return PLUS;}
"-"									{adjust(); return MINUS;}
"*"									{adjust(); return TIMES;}
"/"									{adjust(); return DIVIDE;}
"<-"								{adjust(); return ARROW;}
"<->"								{adjust(); return DOUBLE_ARROW;}
"="									{adjust(); return EQ;}
":="								{adjust(); return ASSIGN;}
"R"[1-3]							{adjust(); yylval.gval.row =atoi(yytext+1); return ROW;}
[0-9]+[0-9]*						{adjust(); yylval.gval.ival=atoi(yytext); return INT;}
[a-zA-Z]+[0-9a-zA-Z]*				{adjust(); yylval.gval.sval=String(yytext); return ID;}
.									{adjust(); EM_error(EM_tokPos,"illegal token");}
