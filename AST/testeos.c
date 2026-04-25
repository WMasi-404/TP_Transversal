// #include "TAD_ast.h"
// #include <stdio.h>
// //esto me genero la ia para probar si andan las funciones que implemente en el TAD AST xd
// /* ── utilidad para crear un nodo STR con contenido ── */
// Tdata make_str(const char* texto) {
//     Tdata n = create_str_ast();
//     cadena_desde_string(&n->string, (char*)texto);
//     return n;
// }

// /* ── helper para imprimir resultado de prueba ── */
// void resultado(const char* nombre, int ok) {
//     printf("  [%s] %s\n", ok ? "OK" : "FAIL", nombre);
// }

// /* ════════════════════════════════════════════════
//    1. PRUEBAS DE CREACION
//    ════════════════════════════════════════════════ */
// void test_creacion() {
//     printf("\n=== 1. Creacion de nodos ===\n");

//     Tdata s = create_str_ast();
//     resultado("create_str_ast devuelve no-NULL",  s != NULL);
//     resultado("nodeType es STR",                  s->nodeType == STR);
//     resultado("string inicia en NULL",            s->string == NULL);

//     Tdata set = create_set();
//     resultado("create_set devuelve no-NULL",      set != NULL);
//     resultado("nodeType es SET",                  set->nodeType == SET);
//     resultado("data inicia en NULL",              set->data == NULL);
//     resultado("next inicia en NULL",              set->next == NULL);

//     Tdata lst = create_list();
//     resultado("create_list devuelve no-NULL",     lst != NULL);
//     resultado("nodeType es LIST",                 lst->nodeType == LIST);
// }

// /* ════════════════════════════════════════════════
//    2. PRUEBAS DE equals / cadena_comparar
//    ════════════════════════════════════════════════ */
// void test_equals() {
//     printf("\n=== 2. equals (comparacion general) ===\n");

//     Tdata a = make_str("hola");
//     Tdata b = make_str("hola");
//     Tdata c = make_str("chau");

//     resultado("STR igual a si mismo",             equals(a, a));
//     resultado("STR igual con mismo contenido",    equals(a, b));
//     resultado("STR distinto contenido",          !equals(a, c));
//     resultado("NULL == NULL",                     equals(NULL, NULL));
//     resultado("NULL != STR",                     !equals(NULL, a));
// }

// /* ════════════════════════════════════════════════
//    3. PRUEBAS DE clone (deep copy)
//    ════════════════════════════════════════════════ */
// void test_clone() {
//     printf("\n=== 3. clone (deep copy) ===\n");

//     Tdata original = make_str("test");
//     Tdata copia    = clone(original);

//     resultado("clone no devuelve el mismo puntero", original != copia);
//     resultado("clone STR: contenido igual",         equals(original, copia));

//     /* modificar la copia no debe afectar el original */
//     cadena_destruir(&copia->string);
//     cadena_desde_string(&copia->string, "otro");
//     resultado("independencia: original intacto tras modificar copia",
//               !equals(original, copia));
// }

// /* ════════════════════════════════════════════════
//    4. PRUEBAS DE LIST
//    ════════════════════════════════════════════════ */
// void test_list() {
//     printf("\n=== 4. Operaciones sobre LIST ===\n");

//     Tdata lista = NULL;
//     Tdata e1 = make_str("a");
//     Tdata e2 = make_str("b");
//     Tdata e3 = make_str("c");

//     /* append_list */
//     append_list(&lista, e1);
//     append_list(&lista, e2);
//     append_list(&lista, e3);
//     resultado("length tras 3 appends == 3",       length(lista) == 3);

//     /* search */
//     resultado("search encuentra 'a'",             search(lista, e1));
//     resultado("search encuentra 'b'",             search(lista, e2));
//     Tdata no = make_str("z");
//     resultado("search no encuentra 'z'",         !search(lista, no));

//     /* copy_list (deep copy) */
//     Tdata copia = copy_list(lista);
//     resultado("copy_list: distinto puntero",      lista != copia);
//     resultado("copy_list: mismo length",          length(lista) == length(copia));
//     resultado("copy_list: primer elem igual",     equals(lista->data, copia->data));

//     /* concat */
//     Tdata l2 = NULL;
//     Tdata e4 = make_str("d");
//     append_list(&l2, e4);
//     Tdata cat = concat(lista, l2);
//     resultado("concat: length == 4",              length(cat) == 4);

//     printf("  Lista concatenada: ");
//     Tdata aux = cat;
//     while (aux != NULL) {
//         cadena_imprimir(aux->data->string);  /* imprime cada elemento */
//         aux = aux->next;
//     }
//     printf("\n");
// }

// /* ════════════════════════════════════════════════
//    5. PRUEBAS DE SET
//    ════════════════════════════════════════════════ */
// void test_set() {
//     printf("\n=== 5. Operaciones sobre SET ===\n");

//     Tdata set = NULL;
//     Tdata a   = make_str("x");
//     Tdata b   = make_str("y");
//     Tdata c   = make_str("z");

//     /* insert_set sin duplicados */
//     insert_set(&set, a);
//     insert_set(&set, b);
//     insert_set(&set, c);
//     insert_set(&set, a);  /* duplicado, no debe insertarse */
//     resultado("insert_set: sin duplicados, length == 3", length(set) == 3);

//     /* belongs */
//     resultado("belongs encuentra 'x'",            belongs(set, a));
//     resultado("belongs encuentra 'y'",            belongs(set, b));
//     Tdata no = make_str("w");
//     resultado("belongs no encuentra 'w'",        !belongs(set, no));

//     /* remove_set */
//     remove_set(&set, b);
//     resultado("remove_set: length == 2 tras eliminar 'y'", length(set) == 2);
//     resultado("remove_set: 'y' ya no pertenece",          !belongs(set, b));
//     resultado("remove_set: 'x' sigue perteneciendo",       belongs(set, a));

//     /* conjunto vacio */
//     Tdata vacio = NULL;
//     resultado("belongs en conjunto vacio == 0",  !belongs(vacio, a));

//     printf("  Set final: ");
//     printSet(set);
//     printf("\n");
// }

// /* ════════════════════════════════════════════════
//    6. PRUEBAS DE equals sobre SET y LIST
//    ════════════════════════════════════════════════ */
// void test_equals_colecciones() {
//     printf("\n=== 6. equals sobre SET y LIST ===\n");

//     /* dos listas iguales */
//     Tdata l1 = NULL, l2 = NULL;
//     append_list(&l1, make_str("a"));
//     append_list(&l1, make_str("b"));
//     append_list(&l2, make_str("a"));
//     append_list(&l2, make_str("b"));
//     resultado("LIST: iguales con mismo orden",    equals(l1, l2));

//     /* listas con distinto orden → no iguales */
//     Tdata l3 = NULL;
//     append_list(&l3, make_str("b"));
//     append_list(&l3, make_str("a"));
//     resultado("LIST: distinto orden → no iguales", !equals(l1, l3));

//     /* dos conjuntos iguales */
//     Tdata s1 = NULL, s2 = NULL;
//     insert_set(&s1, make_str("p"));
//     insert_set(&s1, make_str("q"));
//     insert_set(&s2, make_str("q"));
//     insert_set(&s2, make_str("p"));
//     resultado("SET: iguales sin importar orden",   equals(s1, s2));

//     /* conjuntos distintos */
//     Tdata s3 = NULL;
//     insert_set(&s3, make_str("p"));
//     resultado("SET: distintos tamaños → no iguales", !equals(s1, s3));
// }

// /* ════════════════════════════════════════════════
//    MAIN
//    ════════════════════════════════════════════════ */
// int main() {
//     printf(" PRUEBAS TAD AST \n");

//     test_creacion();
//     test_equals();
//     test_clone();
//     test_list();
//     test_set();
//     test_equals_colecciones();

//     printf("\n¡Pruebas finalizadas!\n");
//     return 0;
// }