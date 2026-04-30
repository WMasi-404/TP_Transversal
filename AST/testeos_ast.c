#include "TAD_ast.h"
#include <stdio.h>
Tdata make_str(const char* texto) {
	Tdata n = create_str_ast();
	cadena_desde_string(&n->string, (char*)texto);
	return n;
}
int main() {
	
	Tdata A,B,P;
	A =create_set();
	B =create_set();
	
	printf("UNION E INTERSECCION\n");
	
	insert_set(&A,make_str("1"));
	insert_set(&A,make_str("2"));
	insert_set(&B,make_str("2"));
	insert_set(&B,make_str("3"));
	
	printf("A: "); 
	printSet(A); 
	printf("\n");
	printf("B: "); 
	printSet(B); 
	printf("\n");
	
	printf("Union: ");
	printSet(union_set(A,B));
	printf("\n");
	
	printf("Interseccion: ");
	printSet(intersection_set(A, B));
	printf("\n");
	
	printf("Diferencia: ");
	printSet(difference_set(A,B));
	printf("\n");
	
	printf("PRODUCTO CARTESIANO\n");
	P = product_cartesiano(A, B);
	printf("A x B: ");
	printSet(P); 
	printf("\n\n");
	
	/*
	// ================= STR -> LIST -> STR =================
	printf("STR -> LIST -> STR\n");
	
	Tdata str, str2, lista;
	
	str = make_str("hola");
	
	printf("Original: ");
	printList(str); printf("\n");
	
	lista = str_to_list(str);
	printf("Lista: ");
	printList(lista); printf("\n");
	
	str2 = list_to_str(lista);
	printf("Reconstruido: ");
	printList(str2); printf("\n\n");
	*/
	
	// ================= CONJUNTOS VACIOS =================
	printf("CONJUNTOS VACIOS\n");
	
	Tdata Vacio;
	A =create_set();
	B =create_set();
	Vacio=create_set();
	insert_set(&A,make_str("a"));
	insert_set(&A,make_str("b"));
	insert_set(&B,make_str("c"));
	insert_set(&B,make_str("d"));
	printf("A: ");
	printSet(A);
	printf("\n");
	printf("B: ");
	printSet(B);
	printf("\n");
	printf("Vacio: "); 
	printSet(Vacio); printf("\n");
	printf("Union: ");
	printSet(union_set(A, Vacio));
	printf("\n");
	printf("Interseccion: ");
	printSet(intersection_set(A, Vacio)); printf("\n");
	printf("Diferencia A-Vacio: ");
	printSet(difference_set(A,Vacio)); printf("\n");
	printf("Diferencia Vacio-A: ");
	printSet(difference_set(Vacio,A)); printf("\n");
	printf("A x Vacio: ");
	printSet(product_cartesiano(A,Vacio)); printf("\n");
	printf("Vacio x A: ");
	printSet(product_cartesiano(Vacio,A)); printf("\n\n");
	
	printf("DUPLICADOS\n");
	Tdata D = create_set();
	insert_set(&D, make_str("1"));
	insert_set(&D, make_str("1"));
	insert_set(&D, make_str("2"));
	insert_set(&D, make_str("2"));
	insert_set(&D, make_str("3"));
	printf("Conjunto (sin duplicados): ");
	printSet(D);
	printf("\n\n");
	printf("LISTAS ANIDADAS\n");
	Tdata Lista,sublista;
	Lista = create_list();
	sublista = create_list();
	append_list(&Lista, make_str("h"));
	append_list(&Lista, make_str("o"));
	append_list(&sublista, make_str("l"));
	append_list(&sublista, make_str("a"));
	append_list(&Lista, sublista);
	printf("Lista: ");
	printList(Lista);
	printf("\n\n");
	printf("COPIAS VS REFERENCIAS\n");
	Tdata O,C,D2;
	O=create_set();
	C=O;               
	D2=clone(O);       
	
	insert_set(&O,make_str("hola"));
	insert_set(&C,make_str("mundo"));
	
	printf("O: ");
	printSet(O);
	
	printf("\nC (ref): ");
	printSet(C);
	
	printf("\nD (clone): ");
	printSet(D2);
	
	printf("\n");
	
	return 0;
}
