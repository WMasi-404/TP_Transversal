#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ====== STRING SIMPLE : Esto deberìa estar en String.h*/
typedef char* str;

str load2(const char* s){
    str r = (str)malloc(strlen(s)+1);
    strcpy(r, s);
    return r;
}

void print_string(str s){
    printf("%s", s);
}

/* TIPOS  */
#define STR 1
#define SET 2
#define LIST 3

typedef struct dataType{
    int nodeType;   //este es un nodo  que tiene el campo que dice que tipo es , 

    union{// esto significa que usa  str o struct
        str string;

        struct{
            struct dataType* data;
            struct dataType* next;
        };
    };

} *Tdata;

/* CREACION */

Tdata create_str_ast(){
    Tdata n = (Tdata)malloc(sizeof(struct dataType));//reservo memoria
    n->nodeType = STR;//le asgino el tipo STR
    n->string = NULL;//la cadena es vacia por el momento
    return n;
}

Tdata create_set(){
    Tdata n = (Tdata)malloc(sizeof(struct dataType));//reservo memoria
    n->nodeType = SET;//le asigno el tipi SET
    n->data = NULL;//campos vacios
    n->next = NULL;
    return n;
}

Tdata create_list(){
    Tdata n = (Tdata)malloc(sizeof(struct dataType));
    n->nodeType = LIST;
    n->data = NULL;//campos vacios
    n->next = NULL;
    return n;
}

/* DEEP COPY */

Tdata clone(Tdata n){
    if(n == NULL) return NULL; // si esta null no va a clonar nada oue

    Tdata nuevo = NULL; // creo un nuevo 

    if(n->nodeType == STR){
        nuevo = create_str_ast();
        nuevo->string = load2(n->string);
    }

    else if(n->nodeType == SET || n->nodeType == LIST){
        nuevo = (n->nodeType == SET) ? create_set() : create_list();//pregunto si es de tipo set o tipo LIST

        Tdata aux = n;
        Tdata head = NULL;//Es el primer nodo de la lista sirve para no perder el inicio de la lista
        Tdata tail = NULL;//Es el último nodo actual de la lista Sirve para agregar nuevos nodos al final rápido.

        while(aux != NULL){//recorro la lista
            Tdata nodo_lista = create_set();  // nodo contenedor

            nodo_lista->data = clone(aux->data);//copio profundamente el contenido del nodo actual
            nodo_lista->next = NULL;

            if(head == NULL){// es el primer nodo de la lista nueva
                head = nodo_lista;
                tail = nodo_lista;
            } else {//sino enlazo pongo al ultimo nodo al final y depues actualizado quien es la cola
                tail->next = nodo_lista;
                tail = nodo_lista;
            }

            aux = aux->next;//avanzo
        }

        return head; //retorno la cabeza la cual hace referencia al primer nodo de la lista nueva
    }

    return nuevo;
}

/* =APPEND  es para agregar al final*/

void append_set(Tdata *A, Tdata e){ //A -> puntero al conjunto
    Tdata nuevo = create_set();     //e -> elemento a insertar

    nuevo->data = clone(e);// clono  el elemento a insertar para no compartir memoria
    nuevo->next = NULL; 

    if(*A == NULL){ //si esta vacio
        *A = nuevo;
    } else {//Sino reccorro hasta el final y lo agrego ahi
        Tdata aux = *A;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = nuevo;
    }
}

void append_list(Tdata *A, Tdata e){//A -> puntero al conjunto, e -> elemento a insertar
    Tdata nuevo = create_list();

    nuevo->data = clone(e);
    nuevo->next = NULL;

    if(*A == NULL){
        *A = nuevo;
    }else{
        Tdata aux = *A;
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = nuevo;
    }

}
/* print */

void printSet(Tdata A){
    if(A == NULL){
        printf("{}");
        return;
    }

    printf("{ ");

    Tdata aux = A;

    while(aux != NULL){

        if(aux->data != NULL){

            if(aux->data->nodeType == STR){
                print_string(aux->data->string);
            }

            else if(aux->data->nodeType == SET){
                printSet(aux->data);  
            }

            else if(aux->data->nodeType == LIST){
                printf("[LIST]");
            }

            if(aux->next != NULL)
                printf(", ");
        }

        aux = aux->next;
    }

    printf(" }");
}

/* ====== MAIN ====== */

int main(){
    Tdata A = NULL;
    Tdata B = NULL;

    Tdata l = NULL;

    /* A = {"hola", "mundo"} */
    Tdata s1 = create_str_ast();
    s1->string = load2("hola");//cargo la cadena hola

    Tdata s2 = create_str_ast();
    s2->string = load2("mundo");//cargo la cadena mundo

    append_set(&A, s1); 
    append_set(&A, s2);
                       //A = {"hola","mundo"}

    append_list(&l, s1);    

                      /* B = {"palabra", {A}} */
    Tdata s3 = create_str_ast();
    s3->string = load2("palabra");// cargo la cadena palabra

    append_set(&B, s3);
    append_set(&B, A);   //mete a A dentro de B, sino clono B y A comparten memoria 

    printf("A = ");
    printSet(A);   

    printf("\nB = ");
    printSet(B);

    printf("\n");

    return 0;
}