#include <stdio.h>
#include <stdlib.h>

//Declaracion de las funciones
int a(char* lookAhead);
int b(char* lookAhead);
int c(char* lookAhead);
int cp(char* lookAhead,int cph);
int d(char* lookAhead);
int dp(char* lookAhead);
int dpp(char* lookAhead);
int e(char* lookAhead);
int ep(char* lookAhead,int eph);
int f(char* lookAhead);
int fp(char* lookAhead);
int fpp(char* lookAhead);
int g(char* lookAhead);
int gp(char* lookAhead,int gph);
int h(char* lookAhead);
int hp(char* lookAhead);
int hpp(char* lookAhead);
int valor(char rom);
void match(char* lookAhead,char c);

int a(char* lookAhead)
{
	return b(lookAhead)+c(lookAhead)+e(lookAhead)+g(lookAhead);
}

int b(char* lookAhead)
{
	if(*lookAhead=='M')
	{
		match(lookAhead,'M');
		return valor('M');
	}
	else
	{
		return 0;
	}
}

int c(char* lookAhead)
{
	if(*lookAhead=='C')
	{
		match(lookAhead,'C');
		int cph=valor('C');
		return cp(lookAhead,cph);

	}
	else if(*lookAhead=='D')
	{
		match(lookAhead,'D');
		return valor('D')+ d(lookAhead);
	}
	else
	{
		return 0;
	}
}

int cp(char* lookAhead,int cph)
{
	if(*lookAhead=='M')
	{
		match(lookAhead,'M');
		return valor('M')-cph;
	}
	else if(*lookAhead=='D')
	{
		match(lookAhead,'D');
		return valor('D')-cph;
	}
	else
	{
		return cph + dp(lookAhead);
	}
}

int d(char* lookAhead)
{
	if(*lookAhead=='C')
	{
		match(lookAhead,'C');
		return valor('C') + dp(lookAhead);
	}
	else
	{
		return 0;
	}
}

int dp(char* lookAhead)
{
	if(*lookAhead=='C')
	{
		match(lookAhead,'C');
		return valor('C') + dpp(lookAhead);
	}
	else
	{
		return 0;
	}
}

int dpp(char* lookAhead)
{
	if(*lookAhead=='C')
	{
		match(lookAhead,'C');
		return valor('C');
	}
	else
	{
		return 0;
	}
}

int e(char* lookAhead)
{
	if(*lookAhead=='X')
	{
		match(lookAhead,'X');
		int eph=valor('X');
		return ep(lookAhead,eph);
	}
	if(*lookAhead=='L')
	{
		match(lookAhead,'L');
		return valor('L') + f(lookAhead);
	}
	else
	{
		return 0;
	}
}

int ep(char* lookAhead,int eph)
{
	if(*lookAhead=='C')
	{
		match(lookAhead,'C');
		return valor('C')-eph;
	}
	else if(*lookAhead=='L')
	{
		match(lookAhead,'L');
		return valor('L')-eph;
	}
	else
	{
		return eph + fp(lookAhead); 
	}
}

int f(char* lookAhead)
{
	if(*lookAhead=='X')
	{
		match(lookAhead,'X');
		return valor('X') + fp(lookAhead); 
	}
	else
	{
		return 0;
	}
}

int fp(char* lookAhead)
{
	if(*lookAhead=='X')
	{
		match(lookAhead,'X');
		return valor('X') + fpp(lookAhead);
	}
	else
	{
		return 0;
	}
}

int fpp(char* lookAhead)
{
	if(*lookAhead=='X')
	{
		match(lookAhead,'X');
		return valor('X');
	}
	else
	{
		return 0;
	}
}

int g(char* lookAhead)
{
	if(*lookAhead=='I')
	{
		match(lookAhead,'I');
		int gph=valor('I');
		return gp(lookAhead,gph);
	}
	else if(*lookAhead=='V')
	{
		match(lookAhead,'V');
		return valor('V') + h(lookAhead);
	}
	else
	{
		return 0;
	}
}

int gp(char* lookAhead,int gph)
{
	if(*lookAhead=='X')
	{
		match(lookAhead,'X');
		return valor('X')-gph;
	}
	else if(*lookAhead=='V')
	{
		match(lookAhead,'V');
		return valor('V')-gph;
	}
	else
	{
		return gph + hp(lookAhead);
	}
}

int h(char* lookAhead)
{
	if(*lookAhead=='I')
	{
		match(lookAhead,'I');
		return valor('I') + hp(lookAhead);
	}
}

int hp(char* lookAhead)
{
	if(*lookAhead=='I')
	{
		match(lookAhead,'I');
		return valor('I') + hpp(lookAhead);
	}
	else
	{
		return 0;
	}
}

int hpp(char* lookAhead)
{
	if(*lookAhead=='I')
	{
		match(lookAhead,'I');
		return valor('I');
	}
	else
	{
		return 0;
	}
}

int valor(char rom)
{
	if(rom=='I')
	{
		return 1;
	}
	if(rom=='V')
	{
		return 5;
	}
	if(rom=='X')
	{
		return 10;
	}
	if(rom=='L')
	{
		return 50;
	}
	if(rom=='C')
	{
		return 100;
	}
	if(rom=='D')
	{
		return 500;
	}
	if(rom=='M')
	{
		return 1000;
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
	char lookAhead=getchar();
	int val = a(&lookAhead);
	if(lookAhead == '\n')
    {
		if(val==0)
		{
			printf("Failure\n");
		}
		else
		{
			printf("%d\n", val);
		}
    }
    else
    {
        printf("Failure\n");
    }
	return 0;
}
