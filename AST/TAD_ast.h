#ifndef TAD_AST_H
#define TAD_AST_H
#include "TAD_cadena.h"
#include <stdio.h>
#include <stdlib.h>

 /*Definicion de tipos de datos*/
#define STR 1
#define SET 2
#define LIST 3

    /*Estructura de un nodo*/
    typedef struct dataType{
        int nodeType;
        union{// esto significa que usa  str o struct
            Cadena string;
            struct{
                struct dataType* data;
                struct dataType* next;
            };
        };
    }*Tdata;

int equals(Tdata, Tdata);  /* comparador general, usado internamente */
/*Creacion de los nodos */
Tdata create_str_ast();//ya esta implementada
Tdata create_set();//ya esta implementada
Tdata create_list();//ya esta implementada
/*DEep copy*/
 Tdata clone(Tdata);//ya esta implementada
/* =APPEND  es para agregar al final, no tiene sentido con cadenas*/
void append_set(Tdata*, Tdata);//ya esta implementada

/* print */
void printSet(Tdata);//ya esta implementada
void print_string(Tdata);//deberia estar en TAD CADENA
void printList(Tdata);        

/*funciones para LIST*/
void append_list(Tdata*, Tdata); //ya esta implementado
int length(Tdata);//ya esta implementada
Tdata copy_list(Tdata) ;//ya esta implementada
Tdata concat(Tdata, Tdata);//ya esta implementada
int search(Tdata, Tdata);//ya esta implementada

/*funciones para SET*/
void insert_set(Tdata*, Tdata);//ya esta implementada
int  belongs(Tdata , Tdata );//(1 si encontró, 0 si no), ya esta implementada
void remove_set(Tdata* , Tdata);//ya esta implementada
Tdata union_set(Tdata , Tdata );  
Tdata intersection_set(Tdata , Tdata );
Tdata difference_set(Tdata , Tdata );
int subset(Tdata , Tdata );//Devuelve si es subconjunto:
int  equals_set(Tdata , Tdata );//si son iguales o no

#endif