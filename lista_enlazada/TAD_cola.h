#ifndef TAD_COLA_H
#define TAD_COLA_H
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct Nodo {
        int dato;
        struct Nodo* sig;
    } Nodo;

    typedef struct {
        Nodo* frente;
        Nodo* final;
    } Cola;

    /*Funciones Publicas*/

    Cola cola_crear();
    void cola_encolar(Cola*, int);
    int cola_desencolar(Cola*);
    int cola_frente(Cola);
    int cola_vacia(Cola);
    void cola_destruir(Cola*);

#endif