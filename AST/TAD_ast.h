#ifndef TAD_AST_H
#define TAD_AST_H
#include "TAD_cadena.h"
#include <stdio.h>
#include <stdlib.h>

 /*Definicion de tipos de datos*/
#define STR 1
#define SET 2
#define LIST 3

typedef char* str;
    /*Estructura de un nodo*/
    typedef struct dataType{
        int nodeType;
        union{// esto significa que usa  str o struct
            str string;
            struct{
                struct dataType* data;
                struct dataType* next;
            };
        };
    }*Tdata;

/*Creacion de los nodos */
Tdata create_str_ast();
Tdata create_set();
Tdata create_list();
/*DEep copy*/
 Tdata clone(Tdata);
/* =APPEND  es para agregar al final, no tiene sentido con cadenas*/
void append_set(Tdata*, Tdata);

/* print */
void printSet(Tdata);
void print_string(Tdata);//deberia estar en TAD CADENA
void printList(Tdata);        

/*funciones para LIST*/
void append_list(Tdata*, Tdata); //ya esta implementado
int length(Tdata);
Tdata copy_list(Tdata) ;
Tdata concat(Tdata, Tdata);
int search(Tdata, Tdata);//busqueda (1 si encontró, 0 si no)

/*funciones para SET*/
void insert_set(Tdata*, Tdata);
int  belongs(Tdata , Tdata );//(1 si encontró, 0 si no)
void remove_set(Tdata* , Tdata);//el segudno es el elemento a eliminar
Tdata union_set(Tdata , Tdata );
Tdata intersection_set(Tdata , Tdata );
Tdata difference_set(Tdata , Tdata );
int subset(Tdata , Tdata );//Devuelve si es subconjunto:
int  equals_set(Tdata , Tdata );//si sob iguales o no

#endif