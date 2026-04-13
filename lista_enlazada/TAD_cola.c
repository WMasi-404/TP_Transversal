#include "TAD_cola.h"

Cola cola_crear(){
    return NULL;
}

void cola_encolar(Cola* cola, int valor){
    Cola nvo,aux;
    nvo = (Cola)(malloc(sizeof(T_nodo)));
    if(nvo != NULL){
        nvo->Dato = valor;
        nvo->sig = NULL;
        if((*cola) == NULL)   (*cola) = nvo;
        else{
            aux = *cola;
            while(aux->sig != NULL)  aux=aux->sig;
            aux->sig = nvo;
        }    
    }
    else    printf("---ERROR AL ASIGNAR MEMORIA---");
}

int cola_desencolar(Cola* cola){
    Cola aux;
    int D;
    D = (*cola)->Dato;
    aux = *cola;
    (*cola) = (*cola)->sig;
    free(aux);

    return D;
}

int cola_frente(Cola c){
   return c->Dato; 
}

int cola_vacia(Cola cola){
    if(cola != NULL)    return 1;
    else    return 0;
}

void cola_destruir(Cola* c){
    while((*c) != NULL){
        int i;
        i = cola_desencolar(c);
        printf("Desencolando... %d\n",i);
    }
}

