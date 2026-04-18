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
    }

    else if(n->nodeType == SET || n->nodeType == LIST){
        nuevo = (n->nodeType == SET) ? create_set() : create_list();//pregunto si es de tipo set o tipo LIST

        Tdata aux = n;
        Tdata head = NULL;//Es el primer nodo de la lista sirve para no perder el inicio de la lista
        Tdata tail = NULL;//Es el último nodo actual de la lista Sirve para agregar nuevos nodos al final rápido.

        while(aux != NULL){//recorro la lista
            Tdata nodo_lista = create_set();  // nodo contenedor

            nodo_lista->data = clone(aux->data);//copio profundamente el contenido del nodo actual
            nodo_lista->next = NULL;

            if(head == NULL){// es el primer nodo de la lista nueva
                head = nodo_lista;
                tail = nodo_lista;
            } else {//sino enlazo pongo al ultimo nodo al final y depues actualizado quien es la cola
                tail->next = nodo_lista;
                tail = nodo_lista;
            }

            aux = aux->next;//avanzo
        }

        return head; //retorno la cabeza la cual hace referencia al primer nodo de la lista nueva
    }

    return nuevo;
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
                print_string(aux->data->string);
            }

            else if(aux->data->nodeType == SET){
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
    Tdata nueva = NULL;
    Tdata aux = list;

    while(aux != NULL){
        append_list(&nueva, aux->data);
        aux = aux -> next;
    }
    
    return nueva;
    // return clone(list); esta es otra forma de hacer  ahorra codigo
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
    if(A == NULL || B == NULL) return 0;

    if(A->nodeType != B->nodeType) return 0; //si son de distinto tipo no son iguales
    
    int a = A->nodeType;

    switch (a){ //comparo segun el tipo que sea STR,LIST;SET
    case STR:
        return strcmp(A->string, B->string) == 0;
    case SET:
        break;//me falta comparar cojuntos tendria que  implementar el belong que es si pertenece un elemento a un conjunto 
    case LIST:
        if(length(A) != length(B)) return 0; //si longitudes son distintitan entonces la listas no son iguales
        
        Tdata aux1 = A;
        Tdata aux2 = B;

        while(aux1 != NULL && aux2 != NULL){
            if(equals(aux1->data,aux2->data) == 0 ) return 0;
            aux1 = aux1 -> next;
            aux2 = aux2 -> next;
        }
        return 1;
    }
    return 0;
}
int search(Tdata list, Tdata elem){//busqueda
    int bandera = 0;
    Tdata actual = list;

    while(actual != NULL){
        if(strcmp(actual->data->string, elem->string) == 0){// me falta aca por eso estaba haciendo el comparador general de Tdato
            bandera = 1;
        }
        actual = actual -> next;
    }
    return bandera;
}

