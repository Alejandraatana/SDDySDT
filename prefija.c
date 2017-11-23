#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

//funciones de la gramatica
void E(char* lookAhead);
void T(char* lookAhead);
void F(char* lookAhead);
void match(char* lookAhead,char c);

//E=simbolo inicial de la gramatica 
void E(char* lookAhead)
{
    	if(*lookAhead=='+')
        {
			  match(lookAhead,'+');
			  E(lookAhead);
			  printf("+");
			  T(lookAhead);
        }
		else if(*lookAhead=='-')
		{
			match(lookAhead,'-');
		    E(lookAhead);
			printf("-");
			T(lookAhead);
		}
		else 
		{
			T(lookAhead);
		}
}

//T mayor precedencia 
void T(char* lookAhead)
{
    	if(*lookAhead=='*')
        {
			  match(lookAhead,'*');
			  T(lookAhead);
			  printf("*");
			  T(lookAhead);
        }
		else if(*lookAhead=='/')
		{
			  match(lookAhead,'/');
			  T(lookAhead);
			  printf("/");
			  F(lookAhead);
		}
		else
		{
			  F(lookAhead);
		}
}

//F numeros 
void F(char* lookAhead)
{
	if(isdigit(*lookAhead))
	{
		printf("%c",*lookAhead);
		match(lookAhead,*lookAhead);
	}
	else
	{
		printf("(");
		E(lookAhead);
		printf(")");
	}
}

//match=verifica que la entrada sea correcta
void match(char* lookAhead, char c)
{
    if(*lookAhead == c)
    {
        *lookAhead = getchar();
    }
    else
    {
        printf("Failure\n");
        exit(1);
    }
}

int main()
{
	char lookAhead=getchar();
	E(&lookAhead);
}
