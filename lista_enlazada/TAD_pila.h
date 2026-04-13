#ifndef TAD_PILA_H
#define TAD_PILA_H
#include <stdio.h>
#include <stdlib.h>

//fifo  : first in first out

typedef struct Nodo{
  int Dato;   
  struct Nodo *sig;
} T_nodo;

typedef T_nodo *Pila;

Pila pila_crear();
void pila_push(Pila *, int);
int pila_pop(Pila *);
int pila_top(Pila *);
int pila_vacia(Pila *);
void pila_destruir(Pila *);

#endif
