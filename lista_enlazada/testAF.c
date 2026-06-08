#include "TAD_AF.h"

int main() {
	printf("Ingrese El AF: ");
	Automata A = cargarAF();
	printAF(A);
	return 0;
}
