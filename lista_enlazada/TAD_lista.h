#ifndef TAD_LISTA_H
#define TAD_LISTA_H
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct nodo{
        int Dato;
        struct nodo* sig;
    }T_nodo;

    typedef T_nodo* Lista;

    Lista lista_crear(void);
    void lista_insertarxcab(Lista*, int);
    void lista_insertarxcola(Lista*, int);
    int lista_elimina(Lista*, int);
    void lista_buscar(Lista, int);
    int lista_longitud(Lista);
    void lista_mostrar(Lista);
    void lista_liberar(Lista*);

#endif

