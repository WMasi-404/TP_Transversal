#include <stdio.h>
#include "TAD_AF.h"

int main() {

    // ============================
    // 1. Cargar AFND hardcodeado
    // ============================
    Automata afnd;
    afnd.states = NULL;
    afnd.deterministic = 0;

    StateNode* q0 = crear_estado(make_str("q0"), 0);
    StateNode* q1 = crear_estado(make_str("q1"), 0);
    StateNode* q2 = crear_estado(make_str("q2"), 1);

    agregar_estado(&afnd, q2);
    agregar_estado(&afnd, q1);
    agregar_estado(&afnd, q0);

    afnd.q0 = make_str("q0");

    // q0 --0--> {q0, q1}
    Tdata dest1 = NULL;
    insert_set(&dest1, make_str("q0"));
    insert_set(&dest1, make_str("q1"));
    agregaTransicion(q0, make_str("0"), dest1);

    // q0 --1--> {q2}
    Tdata dest2 = NULL;
    insert_set(&dest2, make_str("q2"));
    agregaTransicion(q0, make_str("1"), dest2);

    // q1 --0--> {q2}
    Tdata dest3 = NULL;
    insert_set(&dest3, make_str("q2"));
    agregaTransicion(q1, make_str("0"), dest3);

    printf("=== AFND cargado ===");
    printAF(afnd);

    // ============================
    // 2. Probar cadenas
    // ============================
    printf("\n=== Prueba de cadenas ===\n");

    // "00" → ACEPTADA (q0->q1->q2)
    Cadena c1 = cadena_crear();
    cadena_desde_string(&c1, "00");
    printf("Cadena '00': %s\n", aceptar_cadena(afnd, c1) ? "ACEPTADA" : "RECHAZADA");

    // "1" → ACEPTADA (q0->q2)
    Cadena c2 = cadena_crear();
    cadena_desde_string(&c2, "1");
    printf("Cadena '1' : %s\n", aceptar_cadena(afnd, c2) ? "ACEPTADA" : "RECHAZADA");

    // "0" → RECHAZADA
    Cadena c3 = cadena_crear();
    cadena_desde_string(&c3, "0");
    printf("Cadena '0' : %s\n", aceptar_cadena(afnd, c3) ? "ACEPTADA" : "RECHAZADA");

    // "000" → RECHAZADA
    Cadena c4 = cadena_crear();
    cadena_desde_string(&c4, "000");
    printf("Cadena '000': %s\n", aceptar_cadena(afnd, c4) ? "ACEPTADA" : "RECHAZADA");

    // ============================
    // 3. Convertir AFND a AFD
    // ============================
    printf("\n=== Conversion AFND -> AFD ===");
    AFD afd = convertirAFND(afnd);
    printf("\n--- AFD antes de renombrar ---");
    printAFD(&afd);

    renombrarEstados(&afd, afnd);
    printf("\n--- AFD renombrado ---");
    printAFD(&afd);

    obtenerOperativos(&afd, afnd);
    printf("\n--- AFD operativos ---");
    printAFD(&afd);

    return 0;
}