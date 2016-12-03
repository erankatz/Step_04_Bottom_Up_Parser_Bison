
#ifndef __LINEARALGEBRA1MASTER_H__
#define __LINEARALGEBRA1MASTER_H__


#define M 3
#define N 3
typedef struct AST_RowOp_					*AST_RowOp;
typedef struct AST_Number_					*AST_Number;


void replace_rows(AST_Number** matrix, int i,int j);

void multiple_row(AST_Number** matrix, AST_Number c, int i);

AST_Number** multiple_row_plus_crj(AST_Number** matrix, int i, int op, AST_Number c, int j);

AST_Number** CreateMatrix(int m, int n);

AST_Number** MatrixMultiplication(AST_Number** mat1, AST_Number** mat2);

/*
float myrandom();

float** RandomizeMatrix(int m, int n);


void SaveMatrixToFile(float** mat, int m, int n, const char* filename);


void FreeMatrix(float** mat, int m);
float** CreateElementaryMatrix(int m, int n);

float** MatrixMultiplication(float** mat1, float** mat2);
void replace_rows(float **mat, int left);

*/

#endif
