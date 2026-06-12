#include <stdio.h>
#include "TAD_AF.h"

int main() {
    Automata afnd = cargarAF();
    printAF(afnd);

    DFA afd = convertirAFND(afnd);
    printf("\n--- DFA antes de renombrar ---\n");
    printDFA(&afd);

    renombrarEstados(&afd, afnd);
    printf("\n--- DFA renombrado ---\n");
    printDFA(&afd);

    obtenerOperativos(&afd, afnd);
    printf("\n--- DFA operativos ---\n");
    printDFA(&afd);

    return 0;
}