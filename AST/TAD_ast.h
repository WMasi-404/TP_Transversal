#ifndef TAD_AST_H
#define TAD_AST_H
    #include <string.h>
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
        union{
            str string;
            struct{
                struct dataType* data;
                struct dataType* next;
            };
        };
    }*Tdata;

    /*Creacion de los nodos */
    Tdata create_str_ast(){
        Tdata n = (Tdata)(malloc(sizeof(dataType)));
        n->nodeType = STR;
        n->string = NULL;
        return n;
    }

    Tdata create_set(){
        Tdata n = (Tdata)(malloc(sizeof(dataType)));
        n->nodeType = SET;
        n->data = NULL;
        n->next = NULL;

        return n;
    }

    Tdata create_list(){
        Tdata n = (Tdata)(malloc(sizeof(dataType)));
        n->nodeType = LIST;
        n->data = NULL;
        n->next = NULL;

        return n;
    }

    

#endif