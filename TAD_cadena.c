#include "TAD_cadena.h"

Cadena cadena_crear() {
    return NULL; //creo la cadena
}

void cadena_agregar(Cadena* cadena, char c) {
    Cadena nuevo = malloc(sizeof(Cadena));
    nuevo->dato = c;
    nuevo->sig = NULL;

    if (*cadena == NULL) { 
        *cadena = nuevo;  // si la cabeza esta vacia agrego al inicio
        return;
    }

    Cadena aux = *cadena;//sino agrego al final 
    while (aux->sig != NULL)
        aux = aux->sig;

    aux->sig = nuevo;
}

void cadena_desde_string(Cadena* cadena, char* texto) {
    int i = 0;
    while (texto[i] != '\0') { //ingreso el texto 
        cadena_agregar(cadena, texto[i]);
        i++;
    }
}

int esVocal(char c){
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||  //retornar un valor 0 o 1 si es que es una vocal
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U');
}

void cadena_eliminar_vocales(Cadena* cadena) {

    Cadena actual = (*cadena);
    Cadena anterior = NULL;

    while (actual != NULL) {               //recorro la cadena

        if (esVocal(actual->Dato)) {       //pregunta si es una vocal

            if (anterior == NULL) {        //si el anterior es null entonces  la vocal esta en la cabeza
                (*cadena) = actual->sig;          
                free(actual);  //libero
                actual = (*cadena);
            } else {
                anterior->sig = actual->sig; 
                free(actual);
                actual = anterior->sig;
            }

        } else {
            anterior = actual;
            actual = actual->sig;
        }
    }
}

void cadena_imprimir(Cadena cadena) {
    Cadena aux = cadena;

    while (aux != NULL) {
        printf("%c", aux->Dato);
        aux = aux->sig;
    }
    printf("\n");
}

void cadena_destruir(Cadena* cadena) {

    Cadena aux = (*cadena);

    while (aux != NULL) {
        Cadena borrar = aux;
        aux = aux->sig;
        free(borrar);
    }

    (*cadena) = NULL;
}

