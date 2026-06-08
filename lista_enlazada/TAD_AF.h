#ifndef TAD_AF_H
#define TAD_AF_H
#include "TAD_ast.h"
typedef Tdata State;
typedef Tdata Symbol;
typedef struct transition{
	Symbol symbol;
	
	Tdata to;
	
	struct transition* next;
} Transition;
	typedef struct stateNode{
	State name;
	
	Transition* transitions;
	
	int isFinal;
	
	struct stateNode* next;
} StateNode;
	typedef struct{
	StateNode* states;
	
	State q0;
	
	int deterministic;
} Automata;
Automata cargarAF();
void printAF(Automata);
StateNode* crear_estado(State ,int );
StateNode* buscar_estado(Automata* ,State );
void agregar_estado(Automata*,StateNode*);
void agregaTransicion(StateNode*,Symbol,State);

#endif
