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

	typedef struct{// esto es para el AFD, AFD es un automata finito determinista, entonces cada estado es un conjunto de estados del AF
    	Tdata subset;// conjunto de estados del AF que representa este estado del AFD 
	} CompositeState;

	typedef struct{
    	Tdata from;
  
		Symbol symbol;
    
		Tdata to;

	} AFD_Transition;

	typedef struct{
    	Tdata states;

    	AFD_Transition* delta;

    	int deltaCount;

    	CompositeState q0;

    	Tdata F;
	} AFD;

	AFD convertirAFND(Automata afnd);
	Tdata mover(Automata ,Tdata ,Symbol );
	int existeEstado(Tdata ,Tdata);
	int contieneFinal(Automata ,Tdata);
	Tdata ObtenerAlfabeto(Automata);

	typedef struct {
    	Tdata subset;   // {q0, q1}  →  el subconjunto original
    	Tdata nombre;   // "A"       →  el nombre nuevo
	} Mapeo;

	void renombrarEstados(AFD*,Automata);
	Tdata obtenerAccesibles(AFD*);
	Tdata obtenerProductivos(AFD*);
	void obtenerOperativos(AFD*,Automata);
	void printAFD(AFD*);

	int aceptar_cadena(Automata, Cadena);
#endif