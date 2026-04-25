#include "TAD_cola.h"

Cola cola_crear() {
    Cola c;
    c.frente = NULL;
    c.final = NULL;
    return c;
}

void cola_encolar(Cola* cola, int valor) {
    Nodo* nvo = (Nodo*)malloc(sizeof(Nodo));
    if (nvo == NULL) {
        printf("---ERROR AL ASIGNAR MEMORIA---\n");
        return;
    }
    nvo->dato = valor;
    nvo->sig = NULL;

    if (cola->frente == NULL) {
        // Cola vacía
        cola->frente = nvo;
        cola->final = nvo;
    } else {
        // Agregar al final
        cola->final->sig = nvo;
        cola->final = nvo;
    }
}

int cola_desencolar(Cola* cola) {
    if (cola_vacia(*cola)) {
        printf("---ERROR: Cola vacía---\n");
        return -1; // Valor de error
    }
    Nodo* aux = cola->frente;
    int dato = aux->dato;
    cola->frente = cola->frente->sig;
    if (cola->frente == NULL) {
        cola->final = NULL; // Cola quedó vacía
    }
    free(aux);
    return dato;
}

int cola_frente(Cola cola) {
    if (cola_vacia(cola)) {
        printf("---ERROR: Cola vacía---\n");
        return -1; // Valor de error
    }
    return cola.frente->dato;
}

int cola_vacia(Cola cola) {
    return cola.frente == NULL;
}

void cola_destruir(Cola* cola) {
    while (!cola_vacia(*cola)) {
        int dato = cola_desencolar(cola);
        printf("Desencolando... %d\n", dato);
    }
}

