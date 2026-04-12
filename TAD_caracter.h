#ifndef TAD_CARACTER_H
#define TAD_CARACTER_H
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct nodo{
        char Dato;
        struct nodo* sig;
    }T_nodo;

    typedef T_nodo* ListaC;

    ListaC caracter_crear_lista(void);
    void  caracter_inserta_final(ListaC* , char);
    void caracter_elimina(ListaC*, char);
    void caracter_busca(ListaC, char);
    void caracter_mostrarL(ListaC);
    ListaC caracter_limpiaL(ListaC*);


#endif