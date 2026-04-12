#include "TAD_caracter.h"

ListaC caracter_crear_lista(void){
    return NULL;
}

void caracter_inserta_final(ListaC* lc, char c){
    ListaC nvo, aux;
    nvo = (ListaC)(malloc(sizeof(T_nodo)));
    if(nvo != NULL){
        nvo->Dato = c;
        nvo->sig = NULL;
        if((*lc) == NULL)   (*lc) = nvo;
        else{
        aux = (*lc);
        while(aux->sig != NULL) aux = aux->sig;
        aux->sig = nvo;
        }
    }
    else    printf("---ERROR AL ASIGNAR MEMORIA---\n");
}

int caracter_elimina(ListaC* lc, char c){
    ListaC aux,ant;
    aux = (*lc);
    ant = NULL;
    int j = 0;
    while(aux != NULL && c != aux->Dato){
        ant = aux;
        aux = aux->sig;
    }
    if(ant == NULL){
        (*lc) = (*lc)->sig;
        j = 1;
    }
    else{
        ant->sig = aux->sig;
        free(aux);
        j = 1;
    }

    return j;
}

void caracter_busca(ListaC lc, char c){
    ListaC aux;
    aux = lc;
    while(aux != NULL && c != aux->Dato)  aux = aux->sig;
    if(aux != NULL)     printf("Caracter encontrado\n");
    else    printf("El caracter no esta en la lista\n");
}

void caracter_mostrarL(ListaC lc){
    ListaC aux;
    aux = lc;
    if(lc != NULL){
        while(aux != NULL){
            printf("%c-",aux->Dato);
            aux = aux->sig;
        }
        printf("\n");
    }
    else    printf("La lista esta vacia\n");
}

ListaC caracter_limpiaL(ListaC* lc){
    ListaC aux;
    while((*lc) != NULL){
        aux = (*lc);
        (*lc) = (*lc)->sig;
        free(aux);
    }

    return NULL;
}