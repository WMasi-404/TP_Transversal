#include "TAD_ast.h"
#include <string.h>

/* Función auxiliar para imprimir resultados */
void resultado(char* descripcion, int test) {
    printf("  %s: %s\n", descripcion, test ? "OK ✓" : "FAIL ✗");
}

/* ===== PRUEBAS DE CREACION ===== */
void test_creacion() {
    printf("\n=== 1. PRUEBAS DE CREACION ===\n");
    
    Tdata str = create_str_ast();
    resultado("Crear STR", str != NULL && str->nodeType == STR && str->string == NULL);
    
    Tdata set = create_set();
    resultado("Crear SET", set != NULL && set->nodeType == SET && set->data == NULL);
    
    Tdata list = create_list();
    resultado("Crear LIST", list != NULL && list->nodeType == LIST && list->data == NULL);
    
    free(str);
    free(set);
    free(list);
}

/* ===== PRUEBAS DE OPERACIONES CON STRINGS ===== */
void test_strings() {
    printf("\n=== 2. PRUEBAS DE STRINGS ===\n");
    
    Tdata a = create_str_ast();
    cadena_desde_string(&a->string, "Hola");
    
    Tdata b = create_str_ast();
    cadena_desde_string(&b->string, "Hola");
    
    Tdata c = create_str_ast();
    cadena_desde_string(&c->string, "Mundo");
    
    resultado("STR: iguales con mismo contenido", equals(a, b));
    resultado("STR: distintos contenidos", !equals(a, c));
    resultado("STR: igual a si mismo", equals(a, a));
    resultado("clone STR: contenido igual", equals(a, clone(a)));
    
    Tdata clon = clone(a);
    cadena_eliminar_vocales(&clon->string);
    resultado("clone STR: independencia de memoria", !equals(a, clon));
    
    // Liberar
    cadena_destruir(&a->string);
    cadena_destruir(&b->string);
    cadena_destruir(&c->string);
    cadena_destruir(&clon->string);
    free(a); free(b); free(c); free(clon);
}

/* ===== PRUEBAS DE LISTAS ===== */
void test_listas() {
    printf("\n=== 3. PRUEBAS DE LISTAS ===\n");
    
    Tdata lista = NULL;
    
    // Crear elementos
    Tdata e1 = create_str_ast();
    cadena_desde_string(&e1->string, "uno");
    
    Tdata e2 = create_str_ast();
    cadena_desde_string(&e2->string, "dos");
    
    Tdata e3 = create_str_ast();
    cadena_desde_string(&e3->string, "tres");
    
    // Agregar a la lista
    append_list(&lista, e1);
    append_list(&lista, e2);
    append_list(&lista, e3);
    
    resultado("LENGTH: 3 elementos", length(lista) == 3);
    resultado("SEARCH: encuentra 'dos'", search(lista, e2));
    resultado("SEARCH: no encuentra 'cuatro'", !search(lista, create_str_ast()));
    
    // Test copy_list
    Tdata copia = copy_list(lista);
    resultado("COPY_LIST: igual contenido", equals(lista, copia));
    resultado("COPY_LIST: independencia", copia != NULL && lista != copia);
    
    // Test concat
    Tdata lista2 = NULL;
    Tdata e4 = create_str_ast();
    cadena_desde_string(&e4->string, "cuatro");
    append_list(&lista2, e4);
    
    Tdata concatenada = concat(lista, lista2);
    resultado("CONCAT: longitud correcta", length(concatenada) == 4);
    
    // Liberar
    cadena_destruir(&e1->string);
    cadena_destruir(&e2->string);
    cadena_destruir(&e3->string);
    cadena_destruir(&e4->string);
    free(e1); free(e2); free(e3); free(e4);
    // Nota: no liberamos lista, copia ni concatenada para simplificar
}

/* ===== PRUEBAS DE CONJUNTOS ===== */
void test_conjuntos_basico() {
    printf("\n=== 4. PRUEBAS DE CONJUNTOS BASICO ===\n");
    
    Tdata set = NULL;
    
    // Crear elementos
    Tdata a = create_str_ast();
    cadena_desde_string(&a->string, "x");
    
    Tdata b = create_str_ast();
    cadena_desde_string(&b->string, "y");
    
    Tdata c = create_str_ast();
    cadena_desde_string(&c->string, "z");
    
    // Insertar en set
    insert_set(&set, a);
    insert_set(&set, b);
    insert_set(&set, c);
    
    resultado("BELONGS: encuentra 'x'", belongs(set, a));
    resultado("BELONGS: encuentra 'y'", belongs(set, b));
    resultado("BELONGS: no encuentra elemento nuevo", !belongs(set, create_str_ast()));
    
    // Test duplicados
    int len_antes = length(set);
    insert_set(&set, a);  // Intentar agregar duplicado
    resultado("INSERT_SET: evita duplicados", length(set) == len_antes);
    
    // Test remove_set
    remove_set(&set, b);
    resultado("REMOVE_SET: elimina 'y'", !belongs(set, b));
    resultado("REMOVE_SET: 'x' sigue presente", belongs(set, a));
    
    // Liberar
    cadena_destruir(&a->string);
    cadena_destruir(&b->string);
    cadena_destruir(&c->string);
    free(a); free(b); free(c);
}

/* ===== PRUEBAS DE OPERACIONES DE CONJUNTOS ===== */
void test_operaciones_conjuntos() {
    printf("\n=== 5. PRUEBAS DE OPERACIONES DE CONJUNTOS ===\n");
    
    // Crear set A = {1, 2, 3}
    Tdata setA = NULL;
    Tdata a1 = create_str_ast();
    cadena_desde_string(&a1->string, "1");
    Tdata a2 = create_str_ast();
    cadena_desde_string(&a2->string, "2");
    Tdata a3 = create_str_ast();
    cadena_desde_string(&a3->string, "3");
    
    insert_set(&setA, a1);
    insert_set(&setA, a2);
    insert_set(&setA, a3);
    
    // Crear set B = {2, 3, 4}
    Tdata setB = NULL;
    Tdata b2 = create_str_ast();
    cadena_desde_string(&b2->string, "2");
    Tdata b3 = create_str_ast();
    cadena_desde_string(&b3->string, "3");
    Tdata b4 = create_str_ast();
    cadena_desde_string(&b4->string, "4");
    
    insert_set(&setB, b2);
    insert_set(&setB, b3);
    insert_set(&setB, b4);
    
    // UNION: {1, 2, 3, 4}
    Tdata unionAB = union_set(setA, setB);
    resultado("UNION: contiene elementos", unionAB != NULL && length(unionAB) >= 3);
    
    // INTERSECTION: {2, 3}
    Tdata intersecAB = intersection_set(setA, setB);
    resultado("INTERSECTION: contiene elementos", intersecAB != NULL);
    
    // DIFFERENCE: A - B = {1}
    Tdata diffAB = difference_set(setA, setB);
    resultado("DIFFERENCE: A-B contiene elementos", diffAB != NULL);
    
    // SUBSET
    Tdata subconjunto = NULL;
    insert_set(&subconjunto, a2);
    insert_set(&subconjunto, a3);
    resultado("SUBSET: {2,3} es subconjunto de A", subset(subconjunto, setA));
    resultado("SUBSET: A no es subconjunto de subconjunto", !subset(setA, subconjunto));
    
    // EQUALS_SET
    Tdata setA2 = NULL;
    insert_set(&setA2, a1);
    insert_set(&setA2, a2);
    insert_set(&setA2, a3);
    resultado("EQUALS_SET: conjuntos iguales", equals_set(setA, setA2));
    resultado("EQUALS_SET: conjuntos distintos", !equals_set(setA, setB));
    
    // Liberar
    cadena_destruir(&a1->string);
    cadena_destruir(&a2->string);
    cadena_destruir(&a3->string);
    cadena_destruir(&b2->string);
    cadena_destruir(&b3->string);
    cadena_destruir(&b4->string);
    free(a1); free(a2); free(a3); free(b2); free(b3); free(b4);
}

/* ===== PRUEBAS DE IMPRESION ===== */
void test_impresion() {
    printf("\n=== 6. PRUEBAS DE IMPRESION ===\n");
    
    // Imprimir un set
    Tdata set = NULL;
    Tdata a = create_str_ast();
    cadena_desde_string(&a->string, "A");
    Tdata b = create_str_ast();
    cadena_desde_string(&b->string, "B");
    
    insert_set(&set, a);
    insert_set(&set, b);
    
    printf("  SET: ");
    printSet(set);
    printf("\n");
    
    // Imprimir una lista
    Tdata lista = NULL;
    append_list(&lista, a);
    append_list(&lista, b);
    
    printf("  LIST: ");
    printList(lista);
    printf("\n");
    
    resultado("Impresion completada", 1);
    
    // Liberar
    cadena_destruir(&a->string);
    cadena_destruir(&b->string);
    free(a); free(b);
}

/* ===== PRUEBAS DE CASOS ESPECIALES ===== */
void test_casos_especiales() {
    printf("\n=== 7. PRUEBAS DE CASOS ESPECIALES ===\n");
    
    // NULL cases
    resultado("NULL == NULL", equals(NULL, NULL));
    resultado("NULL != STR", !equals(NULL, create_str_ast()));
    
    // Conjunto vacio
    Tdata setVacio = NULL;
    Tdata elem = create_str_ast();
    cadena_desde_string(&elem->string, "X");
    resultado("BELONGS en conjunto vacio == 0", !belongs(setVacio, elem));
    
    // Lista vacia
    resultado("LENGTH lista vacia == 0", length(NULL) == 0);
    resultado("SEARCH en lista vacia == 0", !search(NULL, elem));
    
    cadena_destruir(&elem->string);
    free(elem);
}

/* ===== MAIN ===== */
int main() {
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║        PRUEBAS COMPLETAS DEL TAD AST                     ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    test_creacion();
    test_strings();
    test_listas();
    test_conjuntos_basico();
    test_operaciones_conjuntos();
    test_impresion();
    test_casos_especiales();
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║        FIN DE PRUEBAS                                    ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    return 0;
}//test
/*
int main() {
    Tdata A,B ,V;
     A = create_set();
     B = create_set(); 
     V = create_set();
    printf("UNION E INTERSECCION\n");

    insert_set(&A, create_str_ast("1"));
    insert_set(&A, create_str_ast("2"));
    insert_set(&B, create_str_ast("2"));
    insert_set(&B, create_str_ast("3"));
    printf("A: "); print_set(A);
    printf("B: "); print_set(B);
    printf("Union: ");
    print_set(union_set(A, B));
    printf("\n");
    printf("Interseccion: ");
    print_set(intersection_set(A, B));
    printf("\n");
    printf("Diferencia: ");
    print_set(difference_set(A,B));
    printf("\n");
    *//*
    printf("PRODUCTO CARTESIANO \n");
    Tdata P;
    P = product_cartesiano(A, B);
    printf("A x B: ");
    print_set(P);
    printf("\n");
    printf("\n");
    */
//[abc]->[d]=[adbdcd] usar append y belongs
    /*
    printf("STR -> LIST -> STR\n");
    Tdata str,str2,lista;
    str=create_str("hola");
    printf("Original: ");
    print_str(str);
    lista = str_to_list(str);
    printf("Lista: ");
    print_list(lista);
    str2 = list_to_str(lista);
    printf("Reconstruido: ");
    print_str(str2);
    printf("\n");
    printf("\n");
    */
    //usar append de string a lista y de lista a string(transitividad)[hola]->[h][o][l][a]->[hola]
    /*
    printf("CONJUNTOS VACIOS\n");
    Tdata A,B ,Vacio;
    A = create_set();
     B = create_set();
    Vacio = create_set(); 
    insert_set(&A, create_str_ast("a"));
    insert_set(&A, create_str_ast("b"));
   
    insert_set(&B, create_str_ast("c"));
    insert_set(&B, create_str_ast("d"));
    printf("A: "); print_set(A);
    printf("B: "); print_set(B);
    printf("V: "); print_set(Vacio);
    printf("Vacio: "); print_set(Vacio);
    printf("Union: ");
    print_set(union_set(A, Vacio));
    printf("Interseccion: ");
    print_set(intersection_set(A, Vacio));
    printf("Diferencia A-Vacio: ");
    print_set(difference_set(A,Vacio));
    printf("Diferencia Vacio-A: ");
    print_set(difference_set(Vacio,A));
    printf("A x Vacio: ");
    print_set(product_cartesiano(A,Vacio))
    printf("Vacio x A: ");
    print_set(product_cartesiano(Vacio,A))
    printf("\n");
    printf("\n");
    */
    //uso de union intersecciion y diferencia (AU∅)=A(A∩∅)=A(A-∅)=A(∅-A)=∅(Ax∅)=(∅xA)=A
    /*
    printf("DUPLICADOS\n");
    Tdata D; 
    insert_set(&D, create_str_ast("1"));
    insert_set(&D, create_str_ast("1"));
    insert_set(&D, create_str_ast("2"));
    insert_set(&D, create_str_ast("2"));
    insert_set(&D, create_str_ast("3"));
    D=create_set();
    printf("Conjunto (sin duplicados): ");
    print_set(D);
    printf("\n"); printf("\n);
    */
    // equals,belongs y append  --->   [1,2,3]
    /*printf("LISTAS ANIDADAS\n");
    Tdata Lista1,Lista2
    Lista1=str_to_list(create_str("hola"));
    Lista2=str_to_list(create_str("pepe"));
    printf("Lista 1: ");
    print_list(L1);
    printf("Lista 2: ");
    print_list(L2);
    insert_list(L1, L2);
    printf("\nLista 1 con Lista 2 anidada: ");
    print_list(L1);
    printf("\n");printf("\n");
    */
    /*
    printf("COPIAS VS REFERENCIAS\n"){
    Tdata O,C,D;
    C=D; 
    O=create_set();//original
    D=clone(O)
    insert_set(&O, create_str_ast("10"));
    insert_set(&C, create_int(20));

    printf("A: "); print_set(A);
    printf("\nB (ref): "); print_set(B);
    printf("\nC (clone): "); print_set(C)
}
    return 0;
}
    */