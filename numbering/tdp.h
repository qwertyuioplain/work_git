/*
 * Teeth numbering correction based on DP matching
 * Copyright (C) 2021, K.Kita  All rights reserved.
 */

#ifndef TDP_H
#define TDP_H

#include <cstdio>
#include <cmath>

enum dentition
{
  UPPER_DENTITION, LOWER_DENTITION
};

enum category
{
  CatW = 0, CatM = 1, CatP = 2, CatCa = 3, CatLa = 4, CatCe = 5, CatI = 6
};

/* num. teeth categories */
const int num_categories = 7;
/* intact dentition length */
const int dentition_length = 16;
/* FDI teeth number arrangement */
const int dentition_U[] = {18,17,16,15,14,13,12,11,21,22,23,24,25,26,27,28};
const int dentition_L[] = {48,47,46,45,44,43,42,41,31,32,33,34,35,36,37,38};
/* cat[teethID] --> category */
const int cat[]
= { -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1, -1,
    -1, CatCe, CatLa, CatCa,  CatP,  CatP,  CatM,  CatM,  CatW, -1,
    -1, CatCe, CatLa, CatCa,  CatP,  CatP,  CatM,  CatM,  CatW, -1,
    -1,  CatI,  CatI, CatCa,  CatP,  CatP,  CatM,  CatM,  CatW, -1,
    -1,  CatI,  CatI, CatCa,  CatP,  CatP,  CatM,  CatM,  CatW, -1  };
/* similarity matrix between categories */
const double similarity_U[num_categories][num_categories]
   /* W    M    P   Ca   La   Ce    - */
= { {0.9, 0.8, 0.0, 0.0, 0.0, 0.0, 0.0},   /*W*/
    {0.8, 0.9, 0.0, 0.0, 0.0, 0.0, 0.0},   /*M*/
    {0.0, 0.0, 0.9, 0.6, 0.4, 0.4, 0.0},   /*P*/
    {0.0, 0.0, 0.6, 0.9, 0.6, 0.8, 0.0},   /*Ca*/
    {0.0, 0.0, 0.4, 0.6, 0.9, 0.8, 0.0},   /*La*/
    {0.0, 0.0, 0.4, 0.8, 0.8, 0.9, 0.0},   /*Ce*/
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0} }; /*-*/
const double similarity_L[num_categories][num_categories]
   /* W    M    P   Ca   -    -    I */
= { {0.9, 0.7, 0.0, 0.0, 0.0, 0.0, 0.0},   /*W*/
    {0.7, 0.9, 0.0, 0.0, 0.0, 0.0, 0.0},   /*M*/
    {0.0, 0.0, 0.9, 0.5, 0.0, 0.0, 0.3},   /*P*/
    {0.0, 0.0, 0.5, 0.9, 0.0, 0.0, 0.5},   /*Ca*/
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},   /*-*/
    {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},   /*-*/
    {0.0, 0.0, 0.3, 0.5, 0.0, 0.0, 0.9} }; /*I*/

class TDP
{
	int	verbose = 0;
	int	*tdp(const int *x, const int *y, const int length,
		const double similarity[][num_categories]);
	void	align(const int *x, const int *y, const int i, const int j,
		const double s[][dentition_length+1], int *xa, int *ya, int &len);

public:

	void	set_verbose() { verbose = 1 - verbose; }

	int	*renumbering(enum dentition dent, const int *arr, const int length)
	{
		if(dent == UPPER_DENTITION)
			return(tdp(dentition_U, arr, length, similarity_U));
		else
			return(tdp(dentition_L, arr, length, similarity_L));
	}
};

int*	TDP::tdp(const int *x, const int *y, const int length,
	const double similarity[][num_categories])
{
	double	s[dentition_length+1][dentition_length+1];

	for(int i = 0; i <= dentition_length; i++)
		s[i][0] = 0.0;
	for(int i = 1; i <= length; i++)
		s[0][i] = -9999.0;
	for(int i = 1; i <= dentition_length; i++)
	{
		for(int j = 1; j <= length; j++)
		{
			double	score;
			if(x[i-1] == y[j-1])
				score = 1.0;
			else
				score = similarity[cat[x[i-1]]][cat[y[j-1]]];
			s[i][j] = std::fmax(s[i-1][j], s[i-1][j-1]+score);
		}
	}

	if(verbose)
	{
	    printf("DP score matrix:\n");
	    for(int i = 1; i <= dentition_length; i++)
	    {
		for(int j = 1; j <= length; j++)
		{
			if(s[i][j] < 0.0)
				break;
			printf("%lf ", s[i][j]);
		}
		printf("\n");
	    }
	}

	int	xa[dentition_length+1];
	int	ya[dentition_length+1];
	int	n;

	align(x, y, dentition_length, length, s, xa, ya, n);

	// show alignment
	if(verbose)
	{
		printf("Dentition alignment:\n");
		for(int i = 0; i < n; i++)
			printf("%02d ", xa[i]);
		printf("\n");
		for(int i = 0; i < n; i++)
			printf("%02d ", ya[i]);
		printf("\n");
	}

	int	*y_renum = new int[length];
	int	k = 0;
	for(int i = 0; i < n; i++)
	{
		if(ya[i] != 0)
			y_renum[k++] = xa[i];
	}

	if(verbose)
	{
		printf("Org numbering: ");
		for(int i = 0; i < length; i++)
			printf("%d ", y[i]);
		printf("\nNew numbering: ");
		for(int i = 0; i < length; i++)
			printf("%d ", y_renum[i]);
		printf("\n");
	}

	return(y_renum);
}

void	TDP::align(const int *x, const int *y, const int i, const int j,
	const double s[][dentition_length+1], int *xa, int *ya, int &len)
{
	if(i == 0 && j == 0)
	{
		len = 0;
	}
	else if(i > 0 && s[i][j] == s[i-1][j])
	{
		align(x, y, i-1, j, s, xa, ya, len);
		xa[len] = x[i-1];
		ya[len] = 0;
		len = len + 1;
	}
	else if(i > 0 && j > 0)
	{
		align(x, y, i-1, j-1, s, xa, ya, len);
		xa[len] = x[i-1];
		ya[len] = y[j-1];
		len = len + 1;
	}
}

#endif
