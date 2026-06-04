#include "TAD_AF.h"

int main() {
	
	Automata A = cargarAF();
	printf("\n--- AUTOMATA ---\n");
	
	StateNode* e = A.states;
	
	while (e != NULL) {
		printf("\nEstado: ");
		printList(str_to_list(e->name));
		
		if (e->isFinal) {
			printf(" | Final: SI\n");
		} else {
			printf(" | Final: NO\n");
		}	
		Transition* t = e->transitions;
		
		while (t != NULL) {
			
			printf("  --");
			printList(str_to_list(t->symbol));
			printf("--> ");
			printSet(t->to); 
			printf("\n");
			
			t = t->next;
		}
		e = e->next;
	}
	printf("\nEstado inicial: ");
	printList(str_to_list(A.q0));
	printf("\n");
	
	return 0;
}
