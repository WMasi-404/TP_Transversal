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
    while (aux->sig != NULL)//recorro hasta el final de la cadena
        aux = aux->sig;

    aux->sig = nuevo;
}

void cadena_desde_string(Cadena* cadena, char* texto) {//char* texto es la cadena de caracteres que quiero convertir a mi estructura de cadena enlazada
    int i = 0;
    while (texto[i] != '\0') { //ingreso el texto 
        cadena_agregar(cadena, texto[i]);//llamada recursiva para agregar cada caracter de la cadena de texto a la estructura de cadena enlazada
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

Cadena load2(char* texto) {
    Cadena cadena = NULL;
    cadena_desde_string(&cadena, texto);
    return cadena;
}   

Cadena load2(Cadena original) {//load2 es para cargar una cadena a partir de otra cadena, es decir hacer una copia de la cadena original
    Cadena nueva = cadena_crear();//creo una nueva cadena vacia
    Cadena aux = original;

    while(aux != NULL) {
        cadena_agregar(&nueva, aux->Dato);//agrego cada caracter de la cadena original a la nueva cadena
        aux = aux -> sig;
    }
    return nueva;
}

int cadena_comparar(Cadena c1, Cadena c2) {
    Cadena aux1 = c1;
    Cadena aux2 = c2;

    while(aux1 != NULL && aux2 != NULL){//recorro ambas cadenas 
        if(aux1->Dato != aux2 ->Dato) return 1;//si encuentro  un caracter distinto retorno 1
        aux1 = aux1 -> sig;
        aux2 = aux2 -> sig;
    }
    
    if(aux1 == NULL && aux2 == NULL) return 0;//si ambas cadenas llegaron al final al mismo tiempo  entonces son iguales

   return 1;//si una de las cadenas llego al final antes que la otra entonces son distintas
}
