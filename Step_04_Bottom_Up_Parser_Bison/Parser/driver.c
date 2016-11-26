/***********************/
/* FILE NAME: driver.c */
/***********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>

/*****************/
/* INCLUDE FILES */
/*****************/
#include "../../HEADER_FILES/util.h"
#include "../../HEADER_FILES//errormsg.h"

extern int yyparse(void);

void parse(string fname) 
{
	EM_reset(fname);
	if (yyparse() == 0)
	{
		/******************/
		/* parsing worked */
		/******************/
		fprintf(stderr,"Parsing successful!\n");
	}
	else
	{
		fprintf(stderr,"Parsing failed\n");
	}
}

int main(int argc, char **argv)
{
	if (argc!=2)
	{
		fprintf(stderr,"usage: a.out filename\n");
		exit(1);
	}

	parse(argv[1]);
	
	return 0;
}
