#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#include "error.h"
#include "poly.h"

char *strdup(const char *s);
int get_exponent(char*);
int get_coefficient(char*);
void add_poly_term(poly_t*, int, int);
void construct_poly_array(poly_t* poly);

#define MAX 500

typedef struct term term;

struct term {
	int coefficient;
	int exponent;
	int printed;
};

struct poly_t {
	struct term t[MAX];
	int nbr_poly_terms;
};

poly_t* new_poly_from_string(const char* polystringin)
{
	poly_t* poly;
	char* polyduplicate;
	const char* temp;
	char* polysplit;
	int sign;

	polyduplicate = NULL;
	polysplit = NULL;
	temp = " ";
	sign = 1;

	poly = malloc(sizeof(poly_t));

	assert(poly != NULL);
	construct_poly_array(poly);
	polyduplicate = (char*)strdup(polystringin);
	polysplit = strtok(polyduplicate, temp);

	while (polysplit != NULL)
	{
		if (polysplit[0] == '+' || polysplit[0] == '-')
		{
			if (polysplit[0] == '+')
			{
				sign = 1;
				if (strlen(polysplit) > 1)
				{
					add_poly_term(poly, get_exponent(polysplit),
					get_coefficient(polysplit));
				}
			}
			else if (polysplit[0] == '-')
			{
				sign = -1;
				if (strlen(polysplit) > 1)
				{
					add_poly_term(poly, get_exponent(polysplit),
					get_coefficient(polysplit));
				}
			}
		}
		else
		{
			add_poly_term(poly, get_exponent(polysplit),
				sign*get_coefficient(polysplit));
		}
		polysplit = strtok(NULL, " ");
	}
	return poly;
}
void free_poly(poly_t *p)
{
	if (p != NULL)
	{
		free(p);
	}
}
poly_t*	mul(poly_t* poly_1, poly_t* poly_2)
{
	poly_t* poly;
	int p, q, coefficient, exponent;
	poly = malloc(sizeof(poly_t));
	assert(poly != NULL);

	construct_poly_array(poly);

	for (p = 0; p < poly_1->nbr_poly_terms; p++)
	{
		for (q = 0; q < poly_2->nbr_poly_terms; q++)
		{
			coefficient = poly_1->t[p].coefficient*poly_2->t[q].coefficient;
			exponent = poly_1->t[p].exponent+poly_2->t[q].exponent;
			add_poly_term(poly, exponent, coefficient);
		}
	}
	return poly;
}
void print_poly(poly_t* printpoly)
{
	int i, coefficient, exponent, printed, maxexponent, temppos;
	int tempcoeff, tempexp;
	coefficient = 0;
	exponent = 0;
	temppos = 0;
	i = 0;
	while (i < (printpoly->nbr_poly_terms))
	{
		maxexponent = INT_MIN;
		int j;
		for (j = 0; j<(printpoly->nbr_poly_terms); j++)
		{
			tempcoeff = printpoly->t[j].coefficient;
			tempexp = printpoly->t[j].exponent;
			printed = printpoly->t[j].printed;
			if (tempexp > maxexponent && printed == 0)
			{
				maxexponent = tempexp;
				coefficient = tempcoeff;
				exponent = tempexp;
				temppos = j;
			}
		}
		if (coefficient != 0)
		{
			if (i > 0)
			{
				if (coefficient > 0)
				{
					printf("+ ");
				}
				else
				{
					printf("- ");
				}
			}
			if (i == 0 && coefficient < 0)
			{
				printf("-");
			}
			if (exponent > 0)
			{
				if (coefficient == 1 || coefficient == -1)
				{
					if (exponent != 1)
					{
						printf("x^%d", exponent);
					}
					else
					{
						printf("x");
					}
				}
				else if (exponent == 1)
				{
					printf("%dx", abs(coefficient));
				}
				else
				{
					printf("%dx^%d", abs(coefficient), exponent);
				}
			}
			else
			{
				printf("%d", abs(coefficient));
			}
			if (i + 1 != (printpoly->nbr_poly_terms))
			printf(" ");
		}
		printpoly->t[temppos].printed = 1;
		i++;
	}
	printf("\n");
}
void add_poly_term(poly_t* poly, int exponent, int coefficient)
{
	int r;
	for (r = 0; r < poly->nbr_poly_terms; r++)
	{
		if (poly->t[r].exponent == exponent)
		{
			poly->t[r].coefficient += coefficient;
			return;
		}
	}
	poly->t[poly->nbr_poly_terms].exponent = exponent;
	poly->t[poly->nbr_poly_terms].coefficient = coefficient;
	(poly->nbr_poly_terms)++;
}
void construct_poly_array(poly_t* poly)
{
	int i;
	for (i = 0; i < MAX; i++)
	{
		poly->t[i].exponent = 0;
		poly->t[i].coefficient = 0;
		poly->t[i].printed = 0;

	}
	poly->nbr_poly_terms = 0;
}
int get_exponent(char* poly_term)
{
	char* temp;
	char* temp2;
	int j, exponent_length;
	if ((temp2 = strchr(poly_term, 'x')) != NULL)
	{
		if ((temp = strchr(poly_term, '^')) != NULL)
		{
			exponent_length = strlen(temp)-1;
			char exponent_array[exponent_length];
			for (j=0; j < exponent_length; j++)
			{
				exponent_array[j] = *(temp+j+1);
			}
			return atoi(exponent_array);
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}
int get_coefficient(char* poly_term)
{
	return atoi(poly_term);
}
