#include "TAD_AF.h"
StateNode* crear_estado(State name,int esFinal){
StateNode* nuevo=malloc(sizeof(StateNode));
nuevo->name=name;
nuevo->isFinal=esFinal;
nuevo->transitions=NULL;
nuevo->next=NULL;
return nuevo;
}
StateNode* buscar_estado(Automata* A,State name){
StateNode* aux=A->states;
StateNode* encontrado=NULL;
while(aux!=NULL){
if(equals(aux->name,name))
encontrado=aux;
aux=aux->next;
}
return encontrado;
}
void agregar_estado(Automata*A,StateNode*nuevo){
nuevo->next=A->states;
A->states=nuevo;

}
void agregaTransicion(StateNode* A,Symbol symbol,Tdata to){
Transition* nuevo= malloc(sizeof(Transition));
nuevo->symbol=clone(symbol);
nuevo->to=clone(to);
nuevo->next=A->transitions;
A->transitions=nuevo;
}

	Automata cargarAF() {
		Automata A;
		A.states = NULL;
		
		char c;
		char ca[50];
		int j;
		do {
			scanf("%c", &c);
		} while (c != '(');
		scanf(" %c", &c); 
		
		j = 0;
		scanf("%c", &c);
		
		while (c != '}') {
			
			if (c == ',') {
				ca[j] = '\0';
				agregar_estado(&A,crear_estado(make_str(ca), 0));
				
				j = 0;
			} else {
				ca[j++] = c;
			}
			
			scanf("%c", &c);
		}
		
		ca[j] = '\0';
		
		agregar_estado(&A,crear_estado(make_str(ca), 0));
		
		do {
			scanf("%c", &c);
		} while (c != '{');
		
		do {
			scanf("%c", &c);
		} while (c != '}');
		
		do {
			scanf("%c", &c);
		} while (c != '{');
		
		scanf(" %c", &c);
		
		while (c != '}') {
			
			if (c == '(') {
				
				char from[50];
				char symbol[50];
				j = 0;
				scanf("%c", &c);
				
				while (c != ',') {
					from[j++] = c;
					scanf("%c", &c);
				}
				
				from[j] = '\0';
				j = 0;
				scanf("%c", &c);
				
				while (c != ',') {
					symbol[j++] = c;
					scanf("%c", &c);
				}
				
				symbol[j] = '\0';
				
				Tdata destinos = create_set();
				
				scanf("%c", &c);
				if (c == '{') {
					
					char to[50];
					
					j = 0;
					scanf("%c", &c);
					
					while (c != '}') {
						
						if (c == ',') {
							
							to[j] = '\0';
							insert_set(&destinos, make_str(to));
							
							j = 0;
						} else {
							to[j++] = c;
						}
						
						scanf("%c", &c);
					}
					
					to[j] = '\0';
					insert_set(&destinos, make_str(to));
					
					scanf("%c", &c); 
				}
				else {
					
					char to[50];
					
					j = 0;
					
					while (c != ')') {
						to[j++] = c;
						scanf("%c", &c);
					}
					
					to[j] = '\0';
					
					insert_set(&destinos, make_str(to));
				}
				
				Tdata origenBuscado = make_str(from);
				
				StateNode* origen =
					buscar_estado(&A, origenBuscado);
				
				if (origen != NULL) {
					agregaTransicion(origen,make_str(symbol),destinos);
				}
			}
			
			scanf(" %c", &c);
		}
		
		do{
			scanf(" %c", &c);
		} while(c == ','||c==' ');
		j = 0;
		
		while (c != ',') {
			ca[j++] = c;
			scanf("%c", &c);
		}
		
		ca[j] = '\0';
		
		A.q0 = make_str(ca);
		
		scanf(" %c", &c); 
		j = 0;
		scanf("%c", &c);
		
		while (c != '}') {
			
			if (c == ',') {
				
				ca[j] = '\0';
				
				Tdata buscado = make_str(ca);
				
				StateNode* e =buscar_estado(&A, buscado);
				if (e != NULL)
					e->isFinal = 1;
				j = 0;
			} else {
				ca[j++] = c;
			}
			
			scanf("%c", &c);
		}
		
		ca[j] = '\0';
		
		Tdata buscado = make_str(ca);
		
		StateNode* e =
			buscar_estado(&A, buscado);
		
		if (e != NULL)
			e->isFinal = 1;
		
		return A;
	}
void printAF(Automata A){
		printf("\n--- AUTOMATA ---\n");
		
		StateNode* e = A.states;
		
		while (e != NULL){
			printf("\nEstado: ");
			
			printList(str_to_list(e->name));
			
			if (e->isFinal)
				printf(" | Final: SI\n");
			else
				printf(" | Final: NO\n");
			
			Transition* t = e->transitions;
			
			while (t != NULL){
				printf("          --");
				
				printList(str_to_list(t->symbol));
				printf("--> ");
				printSet(t->to);
				
				printf("\n");
				
				t = t->next;
			}
			
			e = e->next;
		}
		
		printf("\nEstado inicial: ");
		printList(str_to_list(A.q0));
		printf("\n");
	}
