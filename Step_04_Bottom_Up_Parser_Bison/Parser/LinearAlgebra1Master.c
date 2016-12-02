#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#ifdef __unix__
# include <unistd.h>
#elif defined _WIN32
# include <windows.h>
#define sleep(x) Sleep(1000 * x)
#endif

#include "LinearAlgebra1Master.h"

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

float** CreateMatrix(int m, int n)
{
	int i;
	float **x, *y;

	x = (float **)malloc(m * sizeof(float));
	for (i = 0; i<m; i++)
		x[i] = (float *)malloc(n * sizeof(float));

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

void replace_rows(float **mat, int left)
{
	int tok = yylex();
	if (tok == ROWID && yylval.ival <= N && yylval.ival <= N)
	{
		float *temp = mat[yylval.ival - 1];
		mat[yylval.ival - 1] = mat[left - 1];
		mat[left - 1] = temp;
	}
	else
	{
		if (tok != ROWID)
		{
			EM_error(EM_tokPos, "Error Replace Operation Must be RX <->RY");
		}
		else {
			EM_error(EM_tokPos, "The Matrix Row is 3 by 3, replace operation error");
		}
	}
}

*/
