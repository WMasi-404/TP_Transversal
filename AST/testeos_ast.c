#include "TAD_ast.h"
#include <string.h>

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
    printf("A: "); printSet(A);
    printf("B: "); printSet(B);
    printf("Union: ");
    printSet(union_set(A, B));
    printf("\n");
    printf("Interseccion: ");
    printSet(intersection_set(A, B));
    printf("\n");
    printf("Diferencia: ");
    printSet(difference_set(A,B));
    printf("\n");
    printf("PRODUCTO CARTESIANO \n");
    Tdata P;
    P = product_cartesiano(A, B);
    printf("A x B: ");
    printSet(P);
    printf("\n");
    printf("\n");
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
    printf("A: "); printSet(A);
    printf("B: "); printSet(B);
    printf("V: "); printSet(Vacio);
    printf("Vacio: "); printSet(Vacio);
    printf("Union: ");
    printSet(union_set(A, Vacio));
    printf("Interseccion: ");
    printSet(intersection_set(A, Vacio));
    printf("Diferencia A-Vacio: ");
    printSet(difference_set(A,Vacio));
    printf("Diferencia Vacio-A: ");
    printSet(difference_set(Vacio,A));
    printf("A x Vacio: ");
    printSet(product_cartesiano(A,Vacio))
    printf("Vacio x A: ");
    printSet(product_cartesiano(Vacio,A))
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
    printSet(D);
    printf("\n"); printf("\n);
    */
    // equals,belongs y append  --->   [1,2,3]
    /*printf("LISTAS ANIDADAS\n");
    Tdata Lista,sublista;
    Lista=create_list();
    sublista=create_list();
    append_list(Lista,create_str_ast("h"));
    append_list(Lista,create_str_ast("o"));
    append_list(sublista,create_str_ast("l"));
    append_list(sublista,create_str_ast("a"));
    append_list(Lista,sublista)
    printf("Lista 1: ");
    printList(Lista);
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

    printf("A: "); 
    printSet(A);
    printf("\nB (ref): "); 
    printSet(B);
    printf("\nC (clone): ");
    printSet(C)
}
    return 0;
}
    */