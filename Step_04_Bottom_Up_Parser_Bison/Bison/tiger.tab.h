typedef union
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
} YYSTYPE;
#define	TAB	258
#define	INT	259
#define	FLOAT	260
#define	STRING	261
#define	ID	262
#define	COMMA	263
#define	COLON	264
#define	SEMICOLON	265
#define	LPAREN	266
#define	RPAREN	267
#define	LBRACK	268
#define	RBRACK	269
#define	LBRACE	270
#define	RBRACE	271
#define	ARROW	272
#define	PLUS	273
#define	MINUS	274
#define	TIMES	275
#define	DIVIDE	276
#define	EQ	277
#define	NEQ	278
#define	LT	279
#define	LE	280
#define	GT	281
#define	GE	282
#define	AND	283
#define	OR	284
#define	ASSIGN	285
#define	ARRAY	286
#define	IF	287
#define	THEN	288
#define	ELSE	289
#define	WHILE	290
#define	FOR	291
#define	TO	292
#define	DO	293
#define	LET	294
#define	IN	295
#define	END	296
#define	OF	297
#define	BREAK	298
#define	NIL	299
#define	FUNCTION	300
#define	DOUBLE_ARROW	301
#define	ROW	302
#define	TYPE	303


extern YYSTYPE yylval;
