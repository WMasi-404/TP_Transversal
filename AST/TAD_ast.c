#include "TAD_ast.h"

Tdata create_str_ast(){
    Tdata n = (Tdata)malloc(sizeof(struct dataType));//reservo memoria
    n->nodeType = STR;//le asgino el tipo STR
    n->string = NULL;//la cadena es vacia por el momento
    return n;
}

Tdata create_set(){
    Tdata n = (Tdata)malloc(sizeof(struct dataType));//reservo memoria
    n->nodeType = SET;//le asigno el tipi SET
    n->data = NULL;//campos vacios
    n->next = NULL;
    return n;
}

Tdata create_list(){
    Tdata n = (Tdata)malloc(sizeof(struct dataType));
    n->nodeType = LIST;
    n->data = NULL;//campos vacios
    n->next = NULL;
    return n;
}

/* DEEP COPY */

Tdata clone(Tdata n){
    if(n == NULL) return NULL; // si esta null no va a clonar nada oue

    Tdata nuevo = NULL; // creo un nuevo 

    if(n->nodeType == STR){
        nuevo = create_str_ast();
        nuevo->string = load2(n->string);
        return nuevo;
    }
         
    Tdata aux = n;
    Tdata head = NULL;//Es el primer nodo de la lista sirve para no perder el inicio de la lista
    Tdata tail = NULL;//Es el último nodo actual de la lista Sirve para agregar nuevos nodos al final rápido.

        while(aux != NULL){//recorro la lista
            Tdata nodo = (aux->nodeType == SET) ? create_set() : create_list();  // pregunto si el nodo actual es un conjunto o una lista para crear el nodo nuevo del mismo tipo
            nodo -> data = clone(aux->data);//copio profundamente el contenido del nodo actual
            nodo -> next = NULL;

            if(head == NULL){// es el primer nodo de la lista nueva
                head = nodo;
                tail = nodo;
            } else {//sino enlazo pongo al ultimo nodo al final y depues actualizado quien es la cola
                tail -> next = nodo;
                tail = nodo;
            }

            aux = aux->next;//avanzo
        }

        return head; //retorno la cabeza la cual hace referencia al primer nodo de la lista nueva
    }


/* =APPEND  es para agregar al final*/

void append_set(Tdata *A, Tdata e){ //A -> puntero al conjunto
    Tdata nuevo = create_set();     //e -> elemento a insertar

    nuevo->data = clone(e);// clono  el elemento a insertar para no compartir memoria
    nuevo->next = NULL; 

    if(*A == NULL){ //si esta vacio
        *A = nuevo;
    } else {//Sino reccorro hasta el final y lo agrego ahi
        Tdata aux = *A;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = nuevo;
    }
}

void append_list(Tdata *A, Tdata e){//A -> puntero al conjunto, e -> elemento a insertar
    Tdata nuevo = create_list();

    nuevo->data = clone(e);//copia  el elemento
    nuevo->next = NULL;//lo prepara como ultimo nodo

    if(*A == NULL){//si cabeza esta vacia
        *A = nuevo;
    }else{
        Tdata aux = *A;
        while(aux->next != NULL){//recorro hasta el final y lo inserta
            aux = aux->next;
        }
        aux->next = nuevo;
    }

}
/* print */

void printSet(Tdata A){
    if(A == NULL){
        printf("{}");
        return;
    }

    printf("{ ");

    Tdata aux = A;

    while(aux != NULL){

        if(aux->data != NULL){

            if(aux->data->nodeType == STR){
                cadena_imprimir(aux->data->string); //hace referencia al tad cadena donde tiene que tener TAD cadena
            }

            else if(aux->data->nodeType == SET){ //
                printSet(aux->data);  
            }

            else if(aux->data->nodeType == LIST){
                printf("[LIST]");
            }

            if(aux->next != NULL)
                printf(", ");
        }

        aux = aux->next;
    }

    printf(" }");
}

int length(Tdata list){//longitud de la lista
    int contador = 0;
    Tdata actual = list;

    while(actual != NULL){
        contador ++;
        actual = actual->next;
    }
    return contador;
}

Tdata copy_list(Tdata list) { //copia profunda Crear una nueva lista independiente con los mismos elementos que otra lista.
    return clone(list);//aprovecho la funcion clone que ya hace una copia profunda de cualquier Tdata 
                       //la funcion clone ya hace la copia profunda de la lista y sus elementos
}

Tdata concat(Tdata l1, Tdata l2){
    Tdata aux1 = l1, aux2 = l2;
    Tdata Resultado = NULL;

    while(aux1 != NULL){
        append_list(&Resultado,aux1->data);
        aux1 = aux1 -> next;
    }

    while(aux2 != NULL){
        append_list(&Resultado,aux2->data);
        aux2 = aux2 -> next;
    } 
       
    return Resultado;
}

//funcion privada para compararar Tdata general
int equals(Tdata A, Tdata B){ //1=verdadero , 2=falso
    if(A == NULL && B == NULL){// si ambos son nulos son iguales
        return 1;
    }
    if(A == NULL || B == NULL) return 0;//si uno es nulo y el otro no , entonces son distintos

    if(A->nodeType != B->nodeType) return 0; //si son de distinto tipo no son iguales
    
    int a = A->nodeType;

    switch (a){ //comparo segun el tipo que sea STR,LIST;SET
    case STR:{
        return cadena_comparar(A->string, B->string) == 0;}//Sel strcmp devuelve 0 si son iguales , entonces comparo con 0 para devolver 1 si son iguales y 0 si no lo son
    case SET:{
    // Cada elemento de A debe estar en B
       Tdata aux = A; //creo un puntero para recorrer el conjunto A
       while (aux != NULL) {
            if (!belongs(B, aux->data)) return 0;//utilizo la funcion belongs para verificar si el elemento actual de A esta en B
            aux = aux->next;
        }
    // Cada elemento de B debe estar en A
        aux = B;
        while (aux != NULL) {
            if (!belongs(A, aux->data)) return 0;
            aux = aux->next;
        }
        return 1;
    }
    case LIST:{
        if(length(A) != length(B)) return 0; //si longitudes son distintitan entonces la listas no son iguales
        
        Tdata aux1 = A;
        Tdata aux2 = B;

        while(aux1 != NULL && aux2 != NULL){
            if(equals(aux1->data,aux2->data) == 0 ) return 0;//llamada recuriva para comparar los elementos de la lista, los elementos de la lista pueden ser
                                                             // de cualquier tipo por eso la funcion equals es general para comparar cualquier Tdata
            aux1 = aux1 -> next;
            aux2 = aux2 -> next;
        }
        return 1;
    }
    }
    return 0;
}

int search(Tdata list, Tdata elem){//busqueda de un elemento en la lista devuelve 1 si lo encuentra y 0 si no lo encuentra
    int bandera = 0;
    Tdata actual = list;

    while(actual != NULL){
        if(equals(actual -> data, elem)){// me falta aca por eso estaba haciendo el comparador general de Tdato
            bandera = 1;
        }
        actual = actual -> next;
    }
    return bandera;
}

int belongs(Tdata set, Tdata elem){
    int b = 0;
    Tdata act = set;
    while(act != NULL && b != 1){
        if(act -> data == elem -> data){
            b = 1;
        }
        act = act->next;
    }
    return b;
}

void insert_set(Tdata *A, Tdata e) {
    append_set(A, e);
}

void remove_set(Tdata *set, Tdata elem) {
    Tdata aux = *set;
    Tdata prev = NULL;
    while (aux != NULL) {
        if (equals(aux->data, elem)) {
            if (prev == NULL) {
                *set = aux->next;
            } else {
                prev->next = aux->next;
            }
            return;
        }
        prev = aux;
        aux = aux->next;
    }
}

int subset(Tdata A, Tdata B) {
    Tdata aux = A;
    while (aux != NULL) {
        if (!belongs(B, aux->data)) return 0;
        aux = aux->next;
    }
    return 1;
}

int equals_set(Tdata A, Tdata B) {
    return equals(A, B);
}
