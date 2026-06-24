#include "TAD_AF.h"

int main() {
	printf("=== CARGAR AUTOMATA ===\n");
	printf("Formato: ({q0,q1,...}, {a,b,...}, {(q0,a,q1),...}, q0, {q1})\n");
	printf("Ingrese el AF: ");
	Automata A = cargarAF();
	printAF(A);

	printf("\n=== PROBAR CADENAS ===\n");
	printf("Ingrese cadenas para probar (Enter solo para salir):\n");

	while (getchar() != '\n');

	char buffer[256];
	while (1) {
		printf("> ");
		if (fgets(buffer, sizeof(buffer), stdin) == NULL)
			break;

		size_t len = 0;
		while (buffer[len] != '\0' && buffer[len] != '\n')
			len++;
		buffer[len] = '\0';

		if (len == 0)
			break;

		if (aceptar(A, buffer))
			printf("  -> ACEPTADA\n");
		else
			printf("  -> RECHAZADA\n");
	}

	return 0;
}
