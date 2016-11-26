%{
#include <stdio.h>
#include "../../COMMON_FILES/COMMON_H_FILES/util.h"
#include "../../COMMON_FILES/COMMON_H_FILES/errormsg.h"

#define alloca malloc

int yylex(void); /* function prototype */

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}
%}


%union {
	int pos;
	int ival;
	float fval;
	string sval;
	}

%token INT
%token FLOAT
%token STRING
%token ID
%token COMMA
%token COLON
%token SEMICOLON
%token LPAREN
%token RPAREN
%token LBRACK
%token RBRACK
%token LBRACE
%token RBRACE
%token DOT
%token PLUS
%token MINUS
%token TIMES
%token DIVIDE
%token EQ
%token NEQ
%token LT
%token LE
%token GT
%token GE
%token AND
%token OR
%token ASSIGN
%token ARRAY
%token IF
%token THEN
%token ELSE
%token WHILE
%token FOR
%token TO
%token DO
%token LET
%token IN
%token END
%token OF 
%token BREAK
%token NIL
%token FUNCTION
%token VAR
%token TYPE 

%right PLUS
%right MINUS
%right TIMES
%right DIVIDE

%start program

%%

program:	E					{printf("S --> E$\n");}

E:			INT					{printf("E --> INT\n");}
			| E PLUS E			{printf("E --> E + E\n");}
			| E MINUS E			{printf("E --> E - E\n");}
			| E TIMES E			{printf("E --> E * E\n");}
			| E DIVIDE E		{printf("E --> E / E\n");}
			| LPAREN E RPAREN	{printf("E --> (E)\n");}

%%

	
