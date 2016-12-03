
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "LinearAlgebra1Master.h"
#include "AST.h"
#include <assert.h>

//#ifdef __unix__
//# include <unistd.h>
//#elif defined _WIN32
//#include <windows.h>
//#define sleep(x) Sleep(1000 * x)
//#endif

AST_Number** CreateMatrix(int m, int n)
{
	int i;
	AST_Number **x;

	x = (AST_Number **)malloc(m * sizeof(AST_Number));
	for (i = 0; i<m; i++)
		x[i] = (AST_Number *)malloc(n * sizeof(AST_Number));

	return x;
}

void replace_rows(AST_Number** matrix,int i, int j)
{
	AST_Number *temp = matrix[j -1];
	if (i != j)
	{
		matrix[j - 1] = matrix[i-1];
		matrix[i - 1] = temp;
	}
}


AST_Number** CreateElementaryMatrix(int m, int n)
{
	int i;
	int j;
	AST_Number** mat = CreateMatrix(m, n);

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				mat[i][j] = AST_Alloc_Number(1,1);
			}
			else {
				mat[i][j] = AST_Alloc_Number(0, 0);
			}
		}
	}

	return mat;
}

AST_Number** MatrixMultiplication(AST_Number** mat1, AST_Number** mat2)
{
	int i, j, k;
	AST_Number sum;
	AST_Number** mat3;
	AST_Number tmp;

	mat3 = CreateMatrix(3, 3);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sum = AST_Alloc_Number(0, 0);
			for (k = 0; k < 3; k++) {
				tmp = sum;
				sum = AST_Number_Multiplication_Operator(AST_Number_Addition_Operator(sum, mat1[i][k]), mat2[k][j]);
				free(tmp);
			}
			mat3[i][j] = sum;
		}
	}
	return mat3;
}

void multiple_row(AST_Number** matrix, AST_Number c, int i)
{
	AST_Number tmp;
	int j;
	for (j = 0; j < 3; j++)
	{
		tmp = matrix[i-1][j];
		matrix[i-1][j] = AST_Number_Multiplication_Operator(c, matrix[i-1][j]);
		free(tmp);
	}
	return;
}

void multiple_row_plus_crj(AST_Number** matrix, int i, int op, AST_Number c, int j)
{
	AST_Number** tmp = matrix;
	AST_Number** elem = CreateElementaryMatrix(3, 3);
	AST_Number Number_op = (AST_Alloc_Number(op, 1));
	elem[i - 1][j - 1] = AST_Number_Multiplication_Operator(Number_op, c);

	matrix = MatrixMultiplication(elem, matrix);
	//FreeMatrix(tmp);
	FreeMatrix(elem);
	free(Number_op);
}

void FreeMatrix(AST_Number** mat)
{
	int i,j;

	for (i = 0; i<3; i++)
	{
		for (j = 0; j <3 ; j++)
		{
			free(mat[i][j]);
		}
		free(mat[i]);
	}
	free(mat);
}

/*
float myrandom()
{
	sleep(557 / 1000);
	srand(time(NULL));
	return  (float)5 - rand() % 11;
}

float** RandomizeMatrix(int m, int n)
{
	int i, j, k;
	float **x, *y;

	x = CreateMatrix(m, n);
	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			x[i][j] = myrandom();
		}
	}

	return x;
}

void SaveMatrixToFile(float** mat, int m, int n, const char* filename)
{
	int i, j;
	FILE *file = fopen(filename, "w");
	fprintf(file, "[");

	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			fprintf(file, " %.2f", mat[i][j]);
		}
		if (i < m - 1)
		{
			fprintf(file, " ;");
		}
	}
	fprintf(file, "]");
	fflush(NULL);
	fclose(file);
}


void PrintMatrix(float** mat, int m, int n)
{
	int i, j;
	printf("[");

	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			printf(" %.2f", mat[i][j]);
		}
		if (i < m - 1)
		{
			printf(" ;");
		}
	}
	printf("]");
}


void FreeMatrix(float** mat, int m)
{
	int i;

	for (i = 0; i<m; i++)
	{
		free(mat[i]);
	}
	free(mat);
}

float** CreateElementaryMatrix(int m, int n)
{
	int i;
	int j;
	float** mat = CreateMatrix(m, n);

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				mat[i][j] = 1;
			}
			else {
				mat[i][j] = 0;
			}
		}
	}

	return mat;
}

float** MatrixMultiplication(float** mat1, float** mat2)
{
	int i, j, k;
	float sum;
	float** mat3;



	mat3 = CreateMatrix(3, 3);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			sum = 0;
			for (k = 0; k < 3; k++) {
				sum = sum + mat1[i][k] * mat2[k][j];
			}
			mat3[i][j] = sum;
		}
	}
	return mat3;
}

*/

