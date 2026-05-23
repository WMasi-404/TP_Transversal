#include "TAD_ast.h"
#include <stdio.h>
 
/* ── imprime un par (LIST de dos elementos) ── */
void print_par(Tdata par) {
    if (par == NULL){ 
        printf("()");
        return;
    }
    printf("(");
    if (par->data != NULL && par->data->nodeType == STR)
        cadena_imprimir(par->data->string);
    if (par->next != NULL && par->next->data != NULL && par->next->data->nodeType == STR) {
        printf(", ");
        cadena_imprimir(par->next->data->string);
    }
    printf(")");
}
 
/* ── imprime el resultado del producto cartesiano ── */
void print_producto(Tdata prod) {
    if (prod == NULL) {
        printf("{}\n"); 
        return; 
    }
    printf("{ ");
    Tdata aux = prod;
    while (aux != NULL) {
        if (aux->data != NULL)
            print_par(aux->data);
        if (aux->next != NULL) printf(", ");
        aux = aux->next;
    }
    printf(" }\n");
}
 
int main() {
 
 
    printf("=== UNION, INTERSECCION Y DIFERENCIA ===\n");
 
    Tdata A = NULL;
    Tdata B = NULL;
 
    insert_set(&A, make_str("1"));
    insert_set(&A, make_str("2"));
    insert_set(&B, make_str("2"));
    insert_set(&B, make_str("3"));
 
    printf("A: ");
    printSet(A); printf("\n");
    printf("B: ");
    printSet(B); printf("\n");
 
    printf("Union A|B: ");
    printSet(union_set(A, B));
    printf("\n");
 
    printf("Interseccion A&B: ");
    printSet(intersection_set(A, B));
    printf("\n");
 
    printf("Diferencia A-B: ");
    printSet(difference_set(A, B));
    printf("\n\n");
 

    printf("=== PRODUCTO CARTESIANO ===\n");
 
    Tdata P = NULL;
    Tdata Q = NULL;
 
    insert_set(&P, make_str("a"));
    insert_set(&P, make_str("b"));
    insert_set(&Q, make_str("1"));
    insert_set(&Q, make_str("2"));
 
    printf("P: "); 
    printSet(P); 
    printf("\n");
    printf("Q: "); 
    printSet(Q); 
    printf("\n");

    printf("antes de producto\n");

    printf("antes de producto\n");
   
    printf("P x Q (esperado {(a,1),(a,2),(b,1),(b,2)}): ");
    print_producto(product_cartesiano(P, Q));
 
    /* producto con conjunto vacio */
    Tdata vacio_p = NULL;
    printf("P x vacio (esperado {}): ");
    print_producto(product_cartesiano(P, vacio_p));
    printf("\n");
 

    printf("=== CONVERSION STR -> LIST -> STR ===\n");
 
    Tdata str_original = make_str("hola");
    printf("Original STR: ");
    cadena_imprimir(str_original->string);
 
    Tdata lista_chars = str_to_list(str_original);
    printf("Convertido a LIST: ");
    printList(lista_chars);
    printf("\n");
 
    Tdata str_reconstruido = list_to_str(lista_chars);
    printf("Reconstruido STR: ");
    cadena_imprimir(str_reconstruido->string);
 
    printf("Son iguales: %s\n\n", equals(str_original, str_reconstruido) ? "SI" : "NO");
 

    printf("=== CONJUNTOS VACIOS ===\n");
 
    Tdata C     = NULL;
    Tdata vacio = NULL;
 
    insert_set(&C, make_str("a"));
    insert_set(&C, make_str("b"));
 
    printf("C: ");
    printSet(C);
    printf("\n");
    printf("Vacio: ");
    printSet(vacio);
    printf("\n");
 
    printf("Union C|vacio: ");
    printSet(union_set(C, vacio));
    printf("\n");
 
    printf("Interseccion C&vacio: ");
    printSet(intersection_set(C, vacio));
    printf("\n");
 
    printf("Diferencia C-vacio: ");
    printSet(difference_set(C, vacio));
    printf("\n");
 
    printf("Diferencia vacio-C: ");
    printSet(difference_set(vacio, C));
    printf("\n\n");

    printf("=== ELEMENTOS DUPLICADOS ===\n");
 
    Tdata D = NULL;
    insert_set(&D, make_str("1"));
    insert_set(&D, make_str("1")); /* duplicado, no debe insertarse */
    insert_set(&D, make_str("2"));
    insert_set(&D, make_str("2")); /* duplicado, no debe insertarse */
    insert_set(&D, make_str("3"));
 
    printf("Conjunto (esperado {1,2,3}): ");
    printSet(D);
    printf("\n");
    printf("Length (esperado 3): %d\n\n", length(D));
 
    printf("=== LISTAS ANIDADAS ===\n");
 
    Tdata lista1 = str_to_list(make_str("hola"));
    Tdata lista2 = str_to_list(make_str("pepe"));
 
    printf("Lista 1: ");
    printList(lista1); printf("\n");
    printf("Lista 2: ");
    printList(lista2); printf("\n");
 
    append_list(&lista1, lista2);
    printf("Lista 1 con Lista 2 anidada: ");
    printList(lista1);
    printf("\n\n");
 
    printf("=== COPIAS VS REFERENCIAS ===\n");
 
    Tdata original = NULL;
    insert_set(&original, make_str("10"));
    insert_set(&original, make_str("20"));
 
    Tdata referencia = original;           /* mismo puntero, memoria compartida */
    Tdata copia = clone(original);    /* memoria independiente             */
 
    insert_set(&copia, make_str("99"));    /* modificamos solo la copia         */
 
    printf("Original:   "); 
    printSet(original);
    printf("\n");
    printf("Referencia: ");
    printSet(referencia);
    printf("\n");
    printf("Copia (con 99 agregado): ");
    printSet(copia);
    printf("\n");
    printf("Original intacto (no tiene 99): %s\n\n",
    !belongs(original, make_str("99")) ? "SI" : "NO");
 
    printf("Pruebas finalizadas!\n");
    return 0;
}
