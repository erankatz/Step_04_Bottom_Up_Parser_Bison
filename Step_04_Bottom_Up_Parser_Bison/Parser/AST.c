/********************/
/* FILE NAME: AST.c */
/********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "../../HEADER_FILES/util.h"
#include "LinearAlgebra1Master.h"
/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "AST.h"
#include <stdlib.h>

struct AST_Number_
{
	int nominator;
	int denominator;
};

struct AST_Ri_Swap_Rj_
{
	int i;
	int j;
};
struct AST_Ri_equals_cRi_
{
	int i;
	AST_Number c;
};
struct AST_Ri_Equals_Ri_Plus_cRj_
{
	int i;
	int j;
	AST_Number c;
};

struct AST_RowOp_
{
	AST_ROW_OP_TYPE type;
	union
	{
		struct {int i; int j;}							Ri_Swap_Rj;
		struct {int i; AST_Number c;}					Ri_Equals_cRi;
		struct {int i; int op; AST_Number c; int j;}	Ri_Equals_Ri_Plus_cRj;
	} u;
};
struct AST_RowOpList_
{
	AST_RowOp head;
	AST_RowOpList tail;
};

/*********/
/* CTORS */
/*********/
AST_RowOp		AST_Alloc_Ri_Swap_Rj(int i,int j)
{
	AST_RowOp p;
	
	p = (AST_RowOp) checked_malloc(sizeof(*p));

	p->type = AST_ROW_OP_TYPE_RI_SWAP_RJ;
	p->u.Ri_Swap_Rj.i = i;
	p->u.Ri_Swap_Rj.j = j;

	return p;
}
AST_RowOp		AST_Alloc_Ri_equals_cRi(int i, AST_Number c)
{
	AST_RowOp p;
	
	p = (AST_RowOp) checked_malloc(sizeof(*p));

	p->type = AST_ROW_OP_TYPE_RI_EQUALS_CRI;
	p->u.Ri_Equals_cRi.i = i;
	p->u.Ri_Equals_cRi.c = c;

	return p;
}
AST_Number	AST_Alloc_Number(int nominator,int denominator)
{
	AST_Number p;
	
	p = (AST_Number) checked_malloc(sizeof(*p));

	p->nominator = nominator;
	p->denominator = denominator;

	return p;
}

AST_Number**	AST_Alloc_Matrix(AST_Number num1, AST_Number num2, AST_Number num3,
								 AST_Number num4, AST_Number num5, AST_Number num6,
								 AST_Number num7, AST_Number num8, AST_Number num9)
{
	AST_Number **x = CreateMatrix(3, 3);

	x[0][0] = num1;
	x[0][1] = num2;
	x[0][2] = num3;
	x[1][0] = num4;
	x[1][1] = num5;
	x[1][2] = num6;
	x[2][0] = num7;
	x[2][1] = num8;
	x[2][2] = num9;

	return x;
}

AST_RowOpList	AST_Alloc_RowOpList(AST_RowOp head,AST_RowOpList tail)
{
	AST_RowOpList p;
	
	p = (AST_RowOpList) checked_malloc(sizeof(*p));

	p->head = head;
	p->tail = tail;

	return p;
}

AST_RowOp	AST_Alloc_Ri_Equals_Ri_Plus_cRj(int i, int op, AST_Number c,int j)
{
	AST_RowOp p;

	p = (AST_RowOp)checked_malloc(sizeof(*p));

	p->type = AST_ROW_OP_TYPE_RI_EQUALS_RI_PLUS_CRJ;
	p->u.Ri_Equals_Ri_Plus_cRj.i = i;
	p->u.Ri_Equals_Ri_Plus_cRj.c = c;
	p->u.Ri_Equals_Ri_Plus_cRj.op = op;
	p->u.Ri_Equals_Ri_Plus_cRj.j = j;
	return p;
}

AST_RowOp	AST_Alloc_Ri_Equals_cRi(int i, AST_Number c)
{
	AST_RowOp p;

	p = (AST_RowOp)checked_malloc(sizeof(*p));

	p->type = AST_ROW_OP_TYPE_RI_EQUALS_CRI;

	p->u.Ri_Equals_cRi.i = i;
	p->u.Ri_Equals_cRi.c = c;

	return p;
}

AST_Number AST_Number_Addition_Operator(AST_Number num1, AST_Number num2)
{
	int max, i;
	int denominator = num1->denominator * num2->denominator;
	int nominator = (num1->nominator * num2->denominator) + (num2->nominator * num1->denominator);
	max = nominator > denominator ? nominator : denominator;
	for (i = max; i > 1; i--)
	{
		if (nominator % i == 0 && denominator % i ==0)
		{
			denominator = denominator / i;
			nominator = nominator / i;
			break;
		}
	}
	return AST_Alloc_Number(nominator, denominator);
}

AST_Number AST_Number_Multiplication_Operator(AST_Number num1, AST_Number num2)
{
	int i, j, max;
	int denominator = num1->denominator * num2->denominator;
	int nominator = num1->nominator * num2->nominator;
	max = nominator > denominator ? nominator : denominator;
	for (i = max; i > 1; i--)
	{
		if (nominator % i == 0 && denominator % i == 0)
		{
			denominator = denominator / i;
			nominator = nominator / i;
			break;
		}
	}
	return AST_Alloc_Number(nominator, denominator);
}

AST_Number** MatrixRank(AST_Number** matrix, AST_RowOpList RowOpList)
{
	int i, j;
	float num,roundNum;
	AST_RowOpList tmp;
	while (RowOpList != NULL)
	{
		switch (RowOpList->head->type)
		{
		case AST_ROW_OP_TYPE_RI_SWAP_RJ:
			replace_rows(matrix, RowOpList->head->u.Ri_Swap_Rj.i, RowOpList->head->u.Ri_Swap_Rj.j);
			break;
		case AST_ROW_OP_TYPE_RI_EQUALS_CRI:
			multiple_row(matrix, RowOpList->head->u.Ri_Equals_cRi.c, RowOpList->head->u.Ri_Equals_cRi.i);
			break;
		case AST_ROW_OP_TYPE_RI_EQUALS_RI_PLUS_CRJ:
			matrix = multiple_row_plus_crj(matrix, RowOpList->head->u.Ri_Equals_Ri_Plus_cRj.i,
										  RowOpList->head->u.Ri_Equals_Ri_Plus_cRj.op,
										  RowOpList->head->u.Ri_Equals_Ri_Plus_cRj.c,
										  RowOpList->head->u.Ri_Equals_Ri_Plus_cRj.j);
			break;
		default:
			break;
		}
		tmp = RowOpList->tail;
		free(RowOpList);
		RowOpList = tmp;
	}

	printf("[");
	for (i = 0; i < 3;i++)
	{
		for (j = 0; j < 3; j++)
		{
			num = (float)(matrix[i][j]->nominator) / (float)(matrix[i][j]->denominator);
			roundNum = (int)num;
			if (num == roundNum)
				printf(" %d ", (int)num);
			else
				printf(" %d/%d ", matrix[i][j]->nominator, matrix[i][j]->denominator);
		}
		if (i != 2)
			printf(";");
	}
	printf("]\n");
	return matrix;
}

