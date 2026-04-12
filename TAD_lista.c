#include "TAD_lista.h"

Lista lista_crear(void){
    return NULL;
}

void lista_insertarxcab(Lista* l, int i){
    Lista nvo = (Lista)malloc(sizeof(T_nodo)); //reserva un espacio de memoria
    if (nvo != NULL)
    {
      nvo->Dato = i;  
      nvo->sig = (*l);
      (*l) = nvo;
    }
    else printf("Error en la asignacion de memoria para el nodo.");
}

void lista_insertarxcola(Lista* l, int i){
    Lista nvo,aux;
    nvo = (Lista)(malloc(sizeof(T_nodo)));
    if(nvo != NULL){
        nvo->Dato = i;
        nvo->sig = NULL;
        if((*l) == NULL)   (*l) = nvo;
        else{
            aux = (*l);
            while(aux->sig != NULL)  aux=aux->sig;
            aux->sig = nvo;
        }    
    }
    else    printf("---ERROR AL ASIGNAR MEMORIA---");
}


int lista_elimina(Lista* l, int i){
    Lista aux,ant;
    aux = (*l);
    ant = NULL;
    int j;
    j = 0;
    while(aux != NULL && i != aux->Dato){
        ant = aux;
        aux = aux->sig;
    }
    if(ant == NULL){
        (*l) = (*l)->sig;
        j = 1;
    }    
    else{
        ant->sig = aux->sig;
        free(aux);
        j = 1;
    }

    return j;
}

void lista_buscar(Lista l, int i){
    Lista aux;
    aux = l;
    while(aux != NULL && i != aux->Dato)  aux = aux->sig;
    if(aux != NULL)     printf("elemento encontrado\n");
    else    printf("El elemento no esta en la lista\n");
}

int lista_longitud(Lista l){
    Lista aux;
    int j;
    j = 0;
    aux = l;
    while(aux != NULL){ 
        j++;
        aux = aux->sig;
    }
    return j;
}

void lista_mostrar(Lista l){
    Lista aux;
    aux = l;
    if(l != NULL){
        while(aux != NULL){
            printf("%d-",aux->Dato);
            aux = aux->sig;
        }
        printf("\n");
    }
    else    printf("La lista esta vacia\n");
}

void lista_liberar(Lista *l){
    Lista aux;
    aux = (*l);
    while((*l) != NULL){
        aux = (*l);
        (*l) = (*l)->sig;
        free(aux);
    }
}


