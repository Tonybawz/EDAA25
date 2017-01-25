#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{

	int index = 20;
	char *maxarraypointer = malloc(sizeof(char)*index);
	char *arraypointer = malloc(sizeof(char)*index);
	int maxpos = 0;
	int pos = 0;
	int temp;

	while ((temp = getchar()) != EOF)
	{
		if (isalpha(temp))
		{
			if (pos == index)
			{
				index = 2*index;
				arraypointer = realloc(arraypointer, sizeof(char)*index);
			}
			arraypointer[pos] = temp;
			pos++;
		}
		else if (pos > maxpos)
		{
			maxarraypointer = realloc(maxarraypointer, sizeof(char)*pos);
			maxpos = pos;
			strcpy(maxarraypointer, arraypointer);
			pos = 0;
			}
		else
		{
			pos = 0;
		}
	}
	printf("%d", maxpos);
	printf(" characters in longest word: ");
	printf("%s\n", maxarraypointer);
	free(maxarraypointer);
	free(arraypointer);
	return 0;
}
