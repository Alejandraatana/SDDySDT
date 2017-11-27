#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <utility>
#include <unordered_map>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;
using std::cout;
using std::endl;
using std::ifstream;
using std::set;
using std::map;
using std::make_pair;
using std::pair;
using std::unordered_map;


struct DFA
{
    unsigned int startingState = {0};
    set<unsigned int> finalStates;
    map<pair<unsigned int, char>, unsigned int> transitionTable;
};

void dfaAddTransition(DFA& dfa, unsigned int state, char symbol, unsigned int nextState)
{
    dfa.transitionTable.emplace(make_pair(pair<unsigned int, char>(state, symbol), nextState));
}

void dfaAddFinalState(DFA& dfa, unsigned int state)
{
    dfa.finalStates.emplace(state);
}


struct Lexer
{
	unordered_map<string,pair<string,string>> symbolTable;
	DFA dfa_numi;
	DFA dfa_numf;
	DFA dfa_suma;
	DFA dfa_resta;
	DFA dfa_multi;
	DFA dfa_div;
	DFA dfa_parizq;
	DFA dfa_parder;
	DFA dfa_saltol;
};

void inicializaLexer(Lexer& lex)
{

	//automata de numeros enteros
	dfaAddTransition(lex.dfa_numi,0,'n',1);
	dfaAddTransition(lex.dfa_numi,1,'n',1);
	dfaAddTransition(lex.dfa_numi,1,'.',2);
	dfaAddFinalState(lex.dfa_numi,1);

	//automata de numeros flotantes
	dfaAddTransition(lex.dfa_numf,0,'n',1);
	dfaAddTransition(lex.dfa_numf,1,'n',1);
	dfaAddTransition(lex.dfa_numf,1,'.',2);
	dfaAddTransition(lex.dfa_numf,2,'n',3);
	dfaAddTransition(lex.dfa_numf,3,'n',3);
	dfaAddFinalState(lex.dfa_numf,3);

	//automata de +
	dfaAddTransition(lex.dfa_suma,0,'+',1);
	dfaAddFinalState(lex.dfa_suma,1);

	//automata de -
	dfaAddTransition(lex.dfa_resta,0,'-',1);
	dfaAddFinalState(lex.dfa_resta,1);

	//automata de *
	dfaAddTransition(lex.dfa_multi,0,'*',1);
	dfaAddFinalState(lex.dfa_multi,1);

	//automata de /
	dfaAddTransition(lex.dfa_div,0,'/',1);
	dfaAddFinalState(lex.dfa_div,1);

	//automata de (
	dfaAddTransition(lex.dfa_parizq,0,'(',1);
	dfaAddFinalState(lex.dfa_parizq,1);

	//automata de )
	dfaAddTransition(lex.dfa_parder,0,')',1);
	dfaAddFinalState(lex.dfa_parder,1);

	//automata de salto de linea 
	dfaAddTransition(lex.dfa_saltol,0,'\n',1);
	dfaAddFinalState(lex.dfa_saltol,1);

}

struct Token
{
	string nombre;
	string atributo;
};


string dfaStart(DFA& dfa, std::ifstream& inputStream)
{
	unsigned int currentState = dfa.startingState;
	string word;

    while(inputStream.good())
    {
		char symbol = inputStream.get();
		char symbolAux=symbol;

		if(isdigit(symbol))
		{
			symbol='n';
		}

	 	pair<unsigned int, char> transition = {currentState, symbol};

     if(dfa.transitionTable.count(transition) == 0)
     {
            // Backtrack
	    inputStream.putback(symbolAux);
            if(dfa.finalStates.count(currentState) > 0)
            {
	       return word;
	    }
	    else
	    {
		    if(currentState>0)
		    {
			    inputStream.putback(word.back());
		    }
		return "No aceptado";
	    }
    }
	else
	{
		word=word+symbolAux;
	}
        currentState = dfa.transitionTable[transition];
    }
    return "";
}

bool addSymbolTable(Lexer& lexer,Token token)
{
	if(lexer.symbolTable.count(token.atributo)==0)
	{
		lexer.symbolTable.emplace(make_pair(token.nombre,make_pair(token.nombre,token.atributo)));
		return false;
	}
	return true;
}



Token getNextToken(Lexer& lexer,std::ifstream& inputStream)
{
	string cad;
	Token token;
	while(inputStream.good())
	{
		//ejecuta el DFA de numeros flotantes
		cad=dfaStart(lexer.dfa_numf,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="float";
			token.atributo=cad;
			addSymbolTable(lexer,token);
			return token;
		}
		//ejecuta el DFA de numeros enteros
		cad=dfaStart(lexer.dfa_numi,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="int";
			token.atributo=cad;
			addSymbolTable(lexer,token);
			return token;
		}

		//ejecuta el DFA de +
		cad=dfaStart(lexer.dfa_suma,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="OpeAri";
			token.atributo=cad;
			return token;
		}
		//ejecuta el DFA de -
		cad=dfaStart(lexer.dfa_resta,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="OpeAri";
			token.atributo=cad;
			return token;
		}
		//ejecuta el DFA de *
		cad=dfaStart(lexer.dfa_multi,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="OpeAri";
			token.atributo=cad;
			return token;
		}
		//ejecuta el DFA de /
		cad=dfaStart(lexer.dfa_div,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="OpeAri";
			token.atributo=cad;
			return token;
		}
		//ejecuta el DFA de (
		cad=dfaStart(lexer.dfa_parizq,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="OpeAgru";
			token.atributo=cad;
			return token;
		}
		//ejecuta el DFA de )
		cad=dfaStart(lexer.dfa_parder,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="OpeAgru";
			token.atributo=cad;
			return token;
		}
		//ejecuta el DFA de \n
		cad=dfaStart(lexer.dfa_saltol,inputStream);
		if(cad!="No aceptado")
		{
			token.nombre="Space";
			token.atributo=cad;
			return token;
		}
		//Verifica si hubo un error
		if(cad=="No aceptado")
		{
			cout<< "Error" <<endl;
			exit(1);
		}
		//Verifica si se termino el archivo
		if(cad=="")
		{
			token.nombre="EOF";
			token.atributo="";
			return token;
		}
	}
}
