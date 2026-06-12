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

Tdata mover(Automata afnd, Tdata subconjunto, Symbol simbolo){
	Tdata resultado = NULL;// El resultado es el conjunto de estados a los que se puede llegar desde cualquier estado en el subconjunto dado, siguiendo una transición con el símbolo dado.
	Tdata aux = subconjunto;
	while (aux != NULL) {//mientras haya estados en el subconjunto
		StateNode* estado = buscar_estado(&afnd, aux->data);//busco el estado en el AFND
		if (estado != NULL) {//si el estado existe en el AFND
			Transition* t = estado->transitions;//recorro las transiciones del estado
			while (t != NULL) {//mientras haya transiciones
				if (equals(t->symbol, simbolo)) {//si la transición tiene el símbolo buscado
					Tdata destinos = t->to;
					Tdata destAux = destinos;
					while (destAux != NULL) {
						insert_set(&resultado, destAux->data);
						destAux = destAux->next;
					}
				}
				t = t->next;
			}
		}
		aux = aux->next;
	}
	return resultado;
}

int existeEstado(Tdata estadosDFA,Tdata subconjunto){//funcion que verifica si dos conjuntos de estados del AFND son iguales
	Tdata aux = estadosDFA;
	while(aux != NULL){
		if(equals(aux->data, subconjunto))return 1;
		aux = aux -> next;
	}
	return 0;
}

int contieneFinal(Automata afnd, Tdata subconjunto){
	Tdata aux = subconjunto;
	while(aux != NULL){
		StateNode* estado = buscar_estado(&afnd, aux-> data);
		if(estado != NULL && estado->isFinal) return 1;
		aux = aux -> next;
	}
	return 0;	
}
Tdata obtenerAlfabeto(Automata afnd){

    Tdata alfabeto = NULL;

    StateNode* estado = afnd.states;

    while(estado != NULL){

        Transition* t = estado->transitions;

        while(t != NULL){

            insert_set(&alfabeto, t->symbol);

            t = t->next;
        }

        estado = estado->next;
    }

    return alfabeto;
}

DFA convertirAFND(Automata afnd){

    DFA afd;

    afd.states = NULL;
    afd.delta = NULL;
    afd.deltaCount = 0;
    afd.F = NULL;

    Tdata alfabeto = obtenerAlfabeto(afnd);

    // Estado inicial del DFA = {q0}
    Tdata estadoInicial = NULL;
    insert_set(&estadoInicial, afnd.q0);

    insert_set(&afd.states, estadoInicial);

    Tdata pendientes = NULL;
    append_list(&pendientes, estadoInicial);

    while(pendientes != NULL){

        Tdata actual = pendientes->data;

        Tdata simboloAux = alfabeto;

        while(simboloAux != NULL){

            Symbol simbolo = simboloAux->data;

            Tdata destino =
                mover(afnd, actual, simbolo);

            if(destino != NULL){

                if(!existeEstado(
                        afd.states,
                        destino)){

                    insert_set(
                        &afd.states,
                        destino);

                    append_list(
                        &pendientes,
                        destino);
                }

				afd.delta = realloc( afd.delta,(afd.deltaCount + 1) * sizeof(DFA_Transition));

				afd.delta[afd.deltaCount].from = clone(actual);
				afd.delta[afd.deltaCount].symbol = clone(simbolo);
				afd.delta[afd.deltaCount].to = clone(destino);

				afd.deltaCount++;
            }

            simboloAux = simboloAux->next;
        }

        pendientes = pendientes->next;
    }

	Tdata aux = afd.states;

	while(aux != NULL){

    if(contieneFinal(afnd, aux->data)){
        insert_set(&afd.F, aux->data);
    }

    	aux = aux->next;
	}

    return afd;
}

void renombrarEstados(DFA* afd, Automata afnd) {
    
    // 1. Contar cuántos estados tiene el DFA
	int estadoCount = length(afd->states);
    // 2. Crear la tabla de mapeo con ese tamaño
	Mapeo* mapeo = malloc(estadoCount * sizeof(Mapeo));
	// 3. Asignar un nombre nuevo a cada subconjunto de estados
	Tdata aux = afd->states;
	int index = 0;

	while (aux != NULL) {
    	char nombre[2] = {(char)('A' + index), '\0'};
    	mapeo[index].subset = aux->data;
    	mapeo[index].nombre = make_str(nombre);
    	aux = aux->next;
    	index++;
	}

	// 4. Actualizar delta: reemplazar from y to por el nombre nuevo
	for(int i = 0; i < afd->deltaCount; i++){
		DFA_Transition* t = &afd->delta[i];

		for(int j = 0; j < estadoCount; j++){
			if(equals(t->from, mapeo[j].subset)){
				t->from = clone(mapeo[j].nombre);
			}
			if(equals(t->to, mapeo[j].subset)){
				t->to = clone(mapeo[j].nombre);
			}
		}
	}


	// 5. Reconstruir F
	afd->F = NULL;
	for (int i = 0; i < estadoCount; i++) {
    	if (contieneFinal(afnd, mapeo[i].subset)) {
        insert_set(&afd->F, clone(mapeo[i].nombre));
    }
}
	//6. actualizar states: reemplazar cada subconjunto por su nombre nuevo
	Tdata nuevosEstados = NULL;
	aux = afd->states;
	while (aux != NULL) {
		for (int j = 0; j < estadoCount; j++) {
			if (equals(aux->data, mapeo[j].subset)) {
				insert_set(&nuevosEstados, clone(mapeo[j].nombre));
				break;
			}
		}
		aux = aux->next;
	}
	afd->states = nuevosEstados;

	free(mapeo);//libero la memoria del mapeo ya que no lo necesito más
}

Tdata ObtenerAccesibles(DFA* afd) {
	Tdata accesibles = NULL;
	Tdata pendientes = NULL;

	insert_set(&accesibles, afd->states->data);
	append_list(&pendientes, afd->states->data);

	while (pendientes != NULL) {
		Tdata actual = pendientes->data;

		for (int i = 0; i < afd->deltaCount; i++) {
			DFA_Transition* t = &afd->delta[i];

			if (equals(t->from, actual)) {
				if (!belongs(accesibles, t->to)) {
					insert_set(&accesibles, t->to);
					append_list(&pendientes, t->to);
				}
			}
		}

		pendientes = pendientes->next;
	}

	return accesibles;
}

Tdata ObtenerProductivos(DFA* afd) {
	Tdata productivos = NULL;
	Tdata pendientes = NULL;

	Tdata aux = afd->F;
	while (aux != NULL) {
		insert_set(&productivos, aux->data);
		append_list(&pendientes, aux->data);
		aux = aux->next;
	}

	while (pendientes != NULL) {
		Tdata actual = pendientes->data;

		for (int i = 0; i < afd->deltaCount; i++) {
			DFA_Transition* t = &afd->delta[i];

			if (equals(t->to, actual)) {
				if (!belongs(productivos, t->from)) {
					insert_set(&productivos, t->from);
					append_list(&pendientes, t->from);
				}
			}
		}

		pendientes = pendientes->next;
	}

	return productivos;
}

void obtenerOperativos(DFA* afd, Automata afnd) {
    Tdata accesibles  = ObtenerAccesibles(afd);
    Tdata productivos = ObtenerProductivos(afd);

    // intersección: accesibles ∩ productivos
    Tdata operativos = NULL;
    Tdata aux = accesibles;
    while (aux != NULL) {
        if (belongs(productivos, aux->data))
            insert_set(&operativos, aux->data);
        aux = aux->next;
    }

    // 1. Filtrar states
    Tdata nuevosStates = NULL;
    aux = afd->states;
    while (aux != NULL) {
        if (belongs(operativos, aux->data))
            insert_set(&nuevosStates, aux->data);
        aux = aux->next;
    }
    afd->states = nuevosStates;

    // 2. Filtrar delta
    DFA_Transition* nuevaDelta = NULL;
    int nuevoDeltaCount = 0;
    for (int i = 0; i < afd->deltaCount; i++) {
        DFA_Transition* t = &afd->delta[i];
        if (belongs(operativos, t->from) && belongs(operativos, t->to)) {
            nuevaDelta = realloc(nuevaDelta, (nuevoDeltaCount + 1) * sizeof(DFA_Transition));
            nuevaDelta[nuevoDeltaCount++] = *t;
        }
    }
    afd->delta = nuevaDelta;
    afd->deltaCount = nuevoDeltaCount;

    // 3. Filtrar F
    Tdata nuevaF = NULL;
    aux = afd->F;
    while (aux != NULL) {
        if (belongs(operativos, aux->data))
            insert_set(&nuevaF, aux->data);
        aux = aux->next;
    }
    afd->F = nuevaF;
}

void printDFA(DFA* afd) {
	printf("\n--- DFA ---\n");

	Tdata aux = afd->states;
	while (aux != NULL) {
		printf("Estado: ");
		printList(str_to_list(aux->data));
		if (belongs(afd->F, aux->data))
			printf(" | Final: SI\n");
		else
			printf(" | Final: NO\n");
		aux = aux->next;
	}

	printf("\nTransiciones:\n");
	for (int i = 0; i < afd->deltaCount; i++) {
		DFA_Transition* t = &afd->delta[i];
		printf("  ");
		printList(str_to_list(t->from));
		printf(" --");
		printList(str_to_list(t->symbol));
		printf("--> ");
		printList(str_to_list(t->to));
		printf("\n");
	}

	printf("\nEstado inicial: ");
	printList(str_to_list(afd->states->data));
	printf("\n");
}