#ifndef __AST_H__
#define __AST_H__

/*********/
/* TYPES */
/*********/
typedef struct AST_RowOp_					*AST_RowOp;
typedef struct AST_Number_					*AST_Number;
typedef struct AST_RowOpList_				*AST_RowOpList;
typedef struct AST_Ri_Swap_Rj_				*AST_Ri_Swap_Rj;
typedef struct AST_Ri_equals_cRi_			*AST_Ri_Equals_cRi;
typedef struct AST_Ri_Equals_Ri_Plus_cRj_	*AST_Ri_Equals_Ri_Plus_cRj;

typedef enum
{
	AST_ROW_OP_TYPE_RI_SWAP_RJ,
	AST_ROW_OP_TYPE_RI_EQUALS_CRI,
	AST_ROW_OP_TYPE_RI_EQUALS_RI_PLUS_CRJ,
}   AST_ROW_OP_TYPE;

/*********/
/* CTORS */
/*********/
AST_RowOp		AST_Alloc_Ri_Swap_Rj(int i,int j);
AST_RowOp		AST_Alloc_Ri_equals_cRi(int i, AST_Number c);
AST_Number		AST_Alloc_Number(int nominator,int denominator);
AST_RowOpList	AST_Alloc_RowOpList(AST_RowOp head,AST_RowOpList tail);
AST_RowOp		AST_Alloc_Ri_Equals_Ri_Plus_cRj(int i, int op, AST_Number c,int j);
AST_RowOp		AST_Alloc_Ri_Equals_cRi(int i, AST_Number c);
AST_Number**	MatrixRank(AST_Number** matrix, AST_RowOpList RowOpList);
AST_Number**	AST_Alloc_Matrix(AST_Number num1, AST_Number num2, AST_Number num3,
								 AST_Number num4, AST_Number num5, AST_Number num6,
								 AST_Number num7, AST_Number num8, AST_Number num9);
/*********/
/* Operators */
/*********/
AST_Number AST_Number_Addition_Operator(AST_Number num1, AST_Number num2);
AST_Number AST_Number_Multiplication_Operator(AST_Number num1, AST_Number num2);

void FreeMatrix(AST_Number** mat);
#endif
