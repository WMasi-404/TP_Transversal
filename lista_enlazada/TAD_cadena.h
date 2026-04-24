#ifndef TAD_CADENA_H
#define TAD_CADENA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    char Dato;
    struct Nodo* sig;
} T_nodo;

typedef T_nodo* Cadena;

Cadena cadena_crear();
void cadena_agregar(Cadena* cadena, char c);
void cadena_desde_string(Cadena* cadena, char* texto);
void cadena_eliminar_vocales(Cadena* cadena);
void cadena_imprimir(Cadena cadena);
void cadena_destruir(Cadena* cadena);
Cadena load2(Cadena oringinal);
int cadena_comparar(Cadena c1, Cadena c2);


#endif 