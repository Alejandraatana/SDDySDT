#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Declaraciones de las funciones
int E(char* lookAhead);
int Ep(char* lookAhead,int eph);
int T(char* lookAhead);
int Tp(char* lookAhead,int tph);
int F(char* lookAhead);
int costo(char ope);
void match(char* lookAhead,char c);

int E(char* lookAhead)
{
	int eph=T(lookAhead);
	return Ep(lookAhead,eph);
}

int Ep(char* lookAhead, int eph)
{
	if(*lookAhead=='+')
	{
		match(lookAhead,'+');
		int e1ph=eph + costo('+') + T(lookAhead);
		return Ep(lookAhead,e1ph);
	}
	else if(*lookAhead=='-')
	{
		match(lookAhead,'-');
		int e1ph=eph + costo('-') + T(lookAhead);
		return Ep(lookAhead,e1ph);
	}
	else
	{
		return eph;
	}
}

int T(char* lookAhead)
{
	int tph=F(lookAhead);
	return Tp(lookAhead,tph);
}

int Tp(char* lookAhead,int tph)
{
	if(*lookAhead=='*')
	{
		match(lookAhead,'*');
		int t1ph=tph + costo('*') + F(lookAhead);
		return Tp(lookAhead,t1ph);
	}
	else if(*lookAhead=='/')
	{
		match(lookAhead,'/');
		int t1ph=tph + costo('/') + F(lookAhead);
		return Tp(lookAhead,t1ph);
	}
	else
	{
		return tph;
	}
}

int F(char* lookAhead)
{
	int fcos;

	if(*lookAhead=='(')
	{
		match(lookAhead,'(');
		fcos=E(lookAhead);
		match(lookAhead,')');
	}
	else if(isdigit(*lookAhead))
	{
		fcos=0;
		match(lookAhead, *lookAhead);
	}
	else
	{
		printf("Failure\n");
		exit(1);
	}
	return fcos;
}

int costo(char ope)
{
	if(ope=='+')
	{
		return 1;
	}
	else if(ope=='-')
	{
		return 4;
	}
	else if(ope=='*')
	{
		return 20;
	}
	else if(ope=='/')
	{
		return 30;
	}
}

void match(char* lookAhead,char c)
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
    char lookAhead = getchar();
    int eval = E(&lookAhead);
    if(lookAhead == '\n')
    {
        printf("Costo = %d\n", eval);
    }
    else
    {
        printf("Failure\n");
    }
    return 0;
}

