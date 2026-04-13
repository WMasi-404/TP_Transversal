#include "TAD_pila.h"
#include <stdlib.h>
#include <stdio.h>

Pila pila_crear(){
  return NULL;  //creo la pila = NULL
}

void pila_push(Pila *pila, int valor){//inserta el elemento en la cima
    Pila nuevoNodo = (Pila)malloc(sizeof(T_nodo)); //reserva un espacio de memoria
    if (nuevoNodo != NULL)
    {
      nuevoNodo->Dato = valor;  
      nuevoNodo->sig = (*pila);
      (*pila ) = nuevoNodo;
    }
    else printf("Error en la asignacion de memoria para el nodo.");
}

int pila_pop(Pila *pila) {
  Pila temp = (*pila); //guarda el primer nodo o sea la cima
  int valor = (temp)->Dato; //guarda el valor que vas a devolver
  (*pila)   = (*pila)->sig; //mueve la pila al siguiente nodo
  free(temp);//libera memoria del nodo eliminado
  return valor;//devuelve el elemento que sacaste
}

int pila_top(Pila *pila){ //solo mira el valor de la cima
  return (*pila)->Dato;
}

int pila_vacia(Pila *pila){
  return ((*pila) == NULL);  //retorna si pila esta vacia o no
}

void pila_destruir(Pila *pila){
    while (!pila_vacia(pila)){//recorro la pila mientras sea distntinto de nulp
        printf("Desapilando %d",pila_pop(pila));
  }
}