#include <iostream>
#include <string>
#include <typeinfo>
#include "lexer.cpp"

//Declaracion de las funciones
char E(Token* tok,Lexer& lex,std::ifstream& inputStream);
char Ep(Token* tok,char eph,Lexer& lex,std::ifstream& inputStream);
char T(Token* tok,Lexer& lex,std::ifstream& inputStream);
char Tp(Token* tok,char tph,Lexer& lex,std::ifstream& inputStream);
char F(Token* tok,Lexer& lex,std::ifstream& inputStream);
char tipo(Token* tok);
char Fmas(char t1,char t2);
char Fmenos(char t1,char t2);
char Fpor(char t1,char t2);
char Fdiv(char t1,char t2);
void match(Token* tok,string c,Lexer& lex,std::ifstream& inputStream);

char E(Token* tok,Lexer& lex,std::ifstream& inputStream)
{
	char eph=T(tok,lex,inputStream);
	return Ep(tok,eph,lex,inputStream);
}

char Ep(Token* tok,char eph,Lexer& lex,std::ifstream& inputStream)
{
	if(tok->atributo.compare("+")==0)
	{
		match(tok,"+",lex,inputStream);
		char e1ph=Fmas(T(tok,lex,inputStream),eph);
		return Ep(tok,e1ph,lex,inputStream);
	}
	else if(tok->atributo.compare("-")==0)
	{
		match(tok,"-",lex,inputStream);
		char e1ph=Fmenos(T(tok,lex,inputStream),eph);
		return Ep(tok,e1ph,lex,inputStream);
	}
	else
	{
		return eph;
	}
}

char T(Token* tok,Lexer& lex,std::ifstream& inputStream)
{
	char tph=F(tok,lex,inputStream);
	return Tp(tok,tph,lex,inputStream);
}

char Tp(Token* tok,char tph,Lexer& lex,std::ifstream& inputStream)
{
	if(tok->atributo.compare("*")==0)
	{
		match(tok,"*",lex,inputStream);
		char t1ph=Fpor(F(tok,lex,inputStream),tph);
		return Tp(tok,t1ph,lex,inputStream);
	}
	else if(tok->atributo.compare("/")==0)
	{
		match(tok,"/",lex,inputStream);
		char t1ph=Fdiv(F(tok,lex,inputStream),tph);
		return Tp(tok,t1ph,lex,inputStream);
	}
	else
	{
		return tph;
	}
}

char F(Token* tok,Lexer& lex,std::ifstream& inputStream)
{
	char tip;
	if(tok->atributo.compare("(")==0)
	{
		match(tok,"(",lex,inputStream);
		tip=E(tok,lex,inputStream);
		match(tok,")",lex,inputStream);
	}
	else 
	{
		tip=tipo(tok);
		match(tok,"n",lex,inputStream);
	}
	return tip;
}

char tipo(Token* tok)
{
	if(tok->nombre.compare("int")==0)
	{
		return 'i';	
	}
	if(tok->nombre.compare("float")==0)
	{
		return 'f';
	}
}

char Fmas(char t1,char t2)
{
	if(t1=='i' && t2=='i')
	{
		return 'i';
	}
	if(t1=='i' && t2=='f')
	{
		return 'f';
	}
	if(t1=='f' && t2=='i')
	{
		return 'f';
	}
	if(t1=='f' && t2=='f')
	{
		return 'f';
	}
}

char Fmenos(char t1,char t2)
{
	if(t1=='i' && t2=='i')
	{
		return 'i';
	}
	if(t1=='i' && t2=='f')
	{
		return 'f';
	}
	if(t1=='f' && t2=='i')
	{
		return 'f';
	}
	if(t1=='f' && t2=='f')
	{
		return 'f';
	}
}

char Fpor(char t1,char t2)
{
	if(t1=='i' && t2=='i')
	{
		return 'i';
	}
	if(t1=='i' && t2=='f')
	{
		return 'f';
	}
	if(t1=='f' && t2=='i')
	{
		return 'f';
	}
	if(t1=='f' && t2=='f')
	{
		return 'f';
	}
}

char Fdiv(char t1,char t2)
{
	if(t1=='i' && t2=='i')
	{
		return 'i';
	}
	if(t1=='i' && t2=='f')
	{
		return 'f';
	}
	if(t1=='f' && t2=='i')
	{
		return 'f';
	}
	if(t1=='f' && t2=='f')
	{
		return 'f';
	}
}

void match(Token* tok,string c,Lexer& lex,std::ifstream& inputStream)
{
	if(tok->nombre.compare("int")==0 || tok->nombre.compare("float")==0 && inputStream.good())
	{
		*tok=getNextToken(lex,inputStream);
	}
	else if(tok->atributo.compare(c)==0 && inputStream.good())
	{
		*tok=getNextToken(lex,inputStream);
	}
	else
	{
		std::cout<<"Failure" << std::endl;
		exit(1);
	}
}

int main()
{
	Lexer lexer;
	Token tok;
	char tipo;
	inicializaLexer(lexer);
	ifstream inputStream("programa.txt");
	tok=getNextToken(lexer,inputStream);
	tipo=E(&tok,lexer,inputStream);
	if(tipo=='i')
	{
		std::cout << "int" <<std::endl;
	}
	if(tipo=='f')
	{
		std::cout << "float" <<std::endl;
	}
	inputStream.close();
}
