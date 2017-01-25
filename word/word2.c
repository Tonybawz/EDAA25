#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int inttemp;
char temp;
int pos;
char wordchar[10];
char* arraypointer;

int word()
{
	temp = getchar();
	inttemp = temp;

	while (temp != '\n')
	{	
		if (pos / 10 < 1)
		{	
			continue;
		}
		else
		{
			realloc(arraypointer, 10);
			continue;
		}
		if (isalpha(temp))
			{
				wordchar[pos] = temp;
				pos++;
				temp = getchar();
				inttemp = temp;
			}
			else
			{
				printf("error char\n");
				temp = getchar();
				inttemp = temp;
			}
	}
	printf("%d", pos);
	printf(" characters in longest word: ");
	int nbr;
	for (nbr = 0; nbr < pos; nbr++)
	{
		printf("%c", wordchar[nbr]);
	}
	printf("\n");
	free(arraypointer);
	return 0;
}
int main(int argc, char** argv)
{
	arraypointer = calloc(10, sizeof(char));

	while (1)
	{
		if (inttemp == EOF)
		{
			return 0;
		}
		else
		{
			pos = 0;
			word();
		}
	}
	return 0;
}
