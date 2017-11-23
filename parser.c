#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//Decalracion de las funciones
void S(char* lookAhead);
void A(char* lookAhead);
void B(char* lookAhead);
void C(char* lookAhead);
void match(char* lookAhead, char c);


int main()
{
	char lookAhead =getchar();
	S(&lookAhead);
	if(lookAhead=='\n')
	{
		printf("Success\n");
	}
	else
	{
		printf("Failure\n");
	}
	return 0;
}

//S=Simbolo inicial de la gramatica (incluye S')
void S(char* lookAhead)
{
	A(lookAhead);
	while(1)
	{
		if(*lookAhead=='+')
		{
			match(lookAhead,'+');
			A(lookAhead);
		}
		else
		{
			return;
		}
	}
}

//A= incluye A' 
void A(char* lookAhead)
{
	B(lookAhead);
	while(1)
	{
		if(*lookAhead=='.')
		{
			match(lookAhead,'.');
			B(lookAhead);
		}
		else
		{
			return;
		}
	}
}

//B= incluye B' 
void B(char* lookAhead)
{
	C(lookAhead);
	while(1)
	{
		if(*lookAhead=='*')
		{
			match(lookAhead,'*');
		}
		else
		{
			return;
		}
	}
}

//C= Simbolo final de la gramatica 
void C(char* lookAhead)
{
	if(*lookAhead=='(')
	{
		match(lookAhead,'(');
		S(lookAhead);
		match(lookAhead,')');
	}
	else if(*lookAhead=='a')
	{
		match(lookAhead,*lookAhead);
	}
	else if(*lookAhead=='b')
	{
		match(lookAhead,*lookAhead);
	}
	else
	{
		printf("Failure\n");
		exit(1);
	}
}


//match=verifica que sea lo esperado
void match(char* lookAhead, char c)
{
	if(*lookAhead == c)
	{
		*lookAhead=getchar();
	}
	else
	{
		printf("Failure\n");
		exit(1);
	}
}
