#include <stdio.h>
#include <ctype.h>

int temp;
const char MAX = 11;
int prints;
int linecounter;

int ismathsign(int c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
	{
	return 1;
	}
	else if (c == EOF)
	{
		return 0;
	}
	return 2;
}
int domath(int operator, int nbr, int nbr2)
{
	if (operator == '+')
	{
		return nbr + nbr2;
	}
	else if (operator == '-')
	{
		return nbr - nbr2;
	}
	else if (operator == '/')
	{
		if (nbr2 != 0)
		{
			return nbr / nbr2;
		}
		else
		{
			printf("line %d", linecounter);
			printf(": error at /\n");
			prints++;
			return 1;
		}
	}
	else
	{
		return nbr * nbr2;
	}
	return 0;
}

int rpn(int linecounter)
{

int top = 0;
int stack[MAX];
int rpntemp = 0;
int next = 0;
int opcounter = 0;
temp = 0;
	while (top < MAX)
	{
		temp = getchar();

		if ((temp == '\n' && opcounter == 0) || (temp == '\n' && top == 0))
		{
			printf("line %d", linecounter);
			printf(": ");
			printf("error at \\n\n");
			prints++;
			return 0;
		}
		else if (temp == '\n')
		{
			break;
		}
		else if (ismathsign(temp) == 1)
		{
			opcounter++;
			if (top < 2)
			{
				printf("line %d", linecounter);
				printf(": error at ");
				char mathint2 = temp;
				printf("%c\n", mathint2);
				prints++;
				if (getchar() != '\n')
				{
					continue;
				}
				return 0;
			}
			else
			{
				stack[top-2] = domath(temp, stack[top-2], stack[top-1]);
				top--;
			}
		}
		else if (ismathsign(temp) == 0)
		{
			return 0;
		}
		else if (isdigit(temp))
		{
			stack[top] = temp - '0';
			top++;
			while (isdigit(temp))
			{
				next = getchar();
				if (next == '\n')
				{
					printf("line %d", linecounter);
					printf(": error at \\n\n");
					prints++;
					return 0;
				}
				else if (isdigit(next))
				{
					stack[top-1] = stack[top-1]*10 + next-'0';
				}
				else if (isspace(next))
				{
					if (top == MAX)
					{
						printf("line %d", linecounter);
						printf(": error at %d\n", stack[top-1]);
						prints++;
						if (getchar()!= '\n')
						{
							continue;
						}
						return 0;
					}
					break;
				}
				else if (ismathsign(next) == 1)
				{
					opcounter++;
					if (top < 2)
					{
						printf("line %d", linecounter);
						printf(": error at ");
						char mathint = next;
						printf("%c\n", mathint);
						prints++;
						if (getchar() != '\n')
						{
							continue;
						}
						return 0;
					}
					else
					{
						stack[top-2] = domath(next, stack[top-2], stack[top-1]);
						top--;
						break;
					}
				}
			}
			temp = next;
		}
		else if (!isspace(temp))
		{
			printf("line %d", linecounter);
			printf(": error at ");
			char errorchar = temp;
			printf("%c\n", errorchar);
			prints++;
			if (getchar() == '\n')
			{
				continue;
			}
			return 0;
		}
	}
	if (prints == 0)
	{
		rpntemp = stack[top-1];
		printf("line %d", linecounter);
		printf(": %d\n", rpntemp);
		return 0;
	}
		return 0;
}
int main(int argc, char** argv)
{
	linecounter = 1;

	while (1)
	{
		prints = 0;
		if (temp == EOF)
		{
			return 0;
		}
		else
		{
			rpn(linecounter);
			linecounter++;
		}
	}
	return 0;
}
