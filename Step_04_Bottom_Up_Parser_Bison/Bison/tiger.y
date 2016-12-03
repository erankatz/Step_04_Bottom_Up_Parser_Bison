%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "../Parser/AST.h"

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "../../HEADER_FILES/util.h"
#include "../../HEADER_FILES/errormsg.h"

#define alloca malloc

int yylex(void); /* function prototype */

void yyerror(char *s)
{
 EM_error(EM_tokPos, "%s", s);
}
%}
/********************************************************************************/
/* This union is a C replacement for an abstract class representing an AST node */
/********************************************************************************/
%union
{
	union
	{
		int							row;
		int							ival;
		float						fval;
		string						sval;
		AST_Number**				matrix;
		AST_RowOp					RowOp;
		AST_Number					Number;
		AST_RowOpList				RowOpList;
		AST_Ri_Swap_Rj				Ri_Swap_Rj;
		AST_Ri_Equals_cRi			Ri_Equals_cRi;
		AST_Ri_Equals_Ri_Plus_cRj	Ri_Equals_Ri_Plus_cRj;
	}
	gval;
}

%token <gval> TAB
%token <gval> INT
%token <gval> FLOAT
%token <gval> STRING
%token <gval> ID
%token <gval> COMMA
%token <gval> COLON
%token <gval> SEMICOLON
%token <gval> LPAREN
%token <gval> RPAREN
%token <gval> LBRACK
%token <gval> RBRACK
%token <gval> LBRACE
%token <gval> RBRACE
%token <gval> ARROW
%token <gval> PLUS
%token <gval> MINUS
%token <gval> TIMES
%token <gval> DIVIDE
%token <gval> EQ
%token <gval> NEQ
%token <gval> LT
%token <gval> LE
%token <gval> GT
%token <gval> GE
%token <gval> AND
%token <gval> OR
%token <gval> ASSIGN
%token <gval> ARRAY
%token <gval> IF
%token <gval> THEN
%token <gval> ELSE
%token <gval> WHILE
%token <gval> FOR
%token <gval> TO
%token <gval> DO
%token <gval> LET
%token <gval> IN
%token <gval> END
%token <gval> OF 
%token <gval> BREAK
%token <gval> NIL
%token <gval> FUNCTION
%token <gval> DOUBLE_ARROW
%token <gval> ROW
%token <gval> TYPE 

%type <gval> matrix
%type <gval> op
%type <gval> RowOp
%type <gval> Number
%type <gval> program
%type <gval> RowOpList

%start program

%%
program:				matrix RowOpList				{$$.matrix = MatrixRank($1.matrix,$2.RowOpList);}

matrix:					LBRACK Number Number Number SEMICOLON Number Number Number SEMICOLON Number Number Number RBRACK {$$.matrix=AST_Alloc_Matrix($2.Number,$3.Number,$4.Number,
																																					 $6.Number,$7.Number,$8.Number,
																																					 $10.Number,$11.Number,$12.Number);}
RowOpList:				RowOp							{$$.RowOpList = AST_Alloc_RowOpList($1.RowOp,NULL);}
						| RowOp RowOpList				{$$.RowOpList = AST_Alloc_RowOpList($1.RowOp,$2.RowOpList);}
						| RowOp TAB RowOpList			{$$.RowOpList = AST_Alloc_RowOpList($1.RowOp,$3.RowOpList);} 

op:						PLUS							{$$.ival =  1;}
						| MINUS							{$$.ival = -1;}

Number:					INT								{$$.Number = AST_Alloc_Number($1.ival,1);}
						| INT DIVIDE INT				{$$.Number = AST_Alloc_Number($1.ival,$3.ival);}

RowOp:					ROW DOUBLE_ARROW ROW 			{$$.RowOp = AST_Alloc_Ri_Swap_Rj($1.row,$3.row);}
						| ROW ARROW ROW op Number ROW	{
															if ($1.row != $3.row)
															{
																printf("INVLID ROW OPERATION\n");
																assert(0);
															}
															$$.RowOp = AST_Alloc_Ri_Equals_Ri_Plus_cRj($1.row,$4.ival,$5.Number,$6.row)
														}
						| ROW ARROW Number ROW			{$$.RowOp = AST_Alloc_Ri_Equals_cRi($1.row,$3.Number);}							
%%