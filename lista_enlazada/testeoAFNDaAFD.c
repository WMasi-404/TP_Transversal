#include <stdio.h>
#include "TAD_AF.h"

int main() {
    Automata afnd = cargarAF();
    printAF(afnd);

    DFA afd = convertirAFND(afnd);
    printf("\n--- AFD antes de renombrar ---\n");
    printDFA(&afd);

    renombrarEstados(&afd, afnd);
    printf("\n--- AFD renombrado ---\n");
    printDFA(&afd);

    obtenerOperativos(&afd, afnd);
    printf("\n--- AFD operativos ---\n");
    printDFA(&afd);

    return 0;
}