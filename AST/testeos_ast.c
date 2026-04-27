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
    printf("PRODUCTO CARTESIANO \n");
    Tdata P;
    P = product_cartesiano(A, B);
    printf("A x B: ");
    print_set(P);
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