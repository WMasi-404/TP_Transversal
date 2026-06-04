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
char ele[50];
Automata A;
State s;
StateNode* nuevo;
int n, t, i;

A.states = NULL;

printf("Cantidad de estados: ");
scanf("%d", &n);

for (i = 1; i <= n; i++) {

printf("Nombre del estado: ");
scanf("%s", ele);

 s = make_str(ele);

printf("Es final ? (1=SI, 0=NO): ");
int esFinal;
scanf("%d", &esFinal);

nuevo = crear_estado(s, esFinal);
agregar_estado(&A, nuevo);
}

printf("Estado inicial: ");
scanf("%s", ele);
A.q0 = make_str(ele);

printf("Cantidad de transiciones: ");
scanf("%d", &t);

for (i = 1; i <= t; i++) {

char from[50];
char symbol[50];
char to[50];

printf("Transicion %d (origen simbolo destino):\n", i);

printf("Origen: ");
scanf("%s", from);

printf("Simbolo: ");
scanf("%s", symbol);

printf("Destino/s: ");
scanf("%s", to);

StateNode* estadoOrigen = buscar_estado(&A, make_str(from));

if (estadoOrigen == NULL) {

printf("Estado origen no existe\n");

} else {

Tdata destinos = create_set();

char estado[50];
int j = 0;
int k = 0;

while (to[k] != '\0') {
	
	if (to[k] == ',') {
		
		estado[j] = '\0';
		
		insert_set(&destinos, make_str(estado));
		
		j = 0;
		
	} else {
		
		estado[j] = to[k];
		j++;
	}
	
	k++;
}

estado[j] = '\0';

insert_set(&destinos, make_str(estado));

agregaTransicion(estadoOrigen,make_str(symbol),destinos);
}
}

return A;
}
