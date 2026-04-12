#include "TAD_cadena.h"

int main(){
   
// Crear la cadena
    printf("--- Test: Creando cadena ---\n");
    Cadena miCadena = cadena_crear();

    // 2. Probar cadena_desde_string
    printf("Insertando 'Hola Mundo'...\n");
    cadena_desde_string(&miCadena, "Hola Mundo");
    
    printf("Resultado esperado: Hola Mundo\n");
    printf("Resultado obtenido: ");
    cadena_imprimir(miCadena);
    printf("\n");

    //Probar cadena_eliminar_vocales
    printf("--- Test: Eliminando vocales ---\n");
    cadena_eliminar_vocales(&miCadena);
    printf("Resultado obtenido: ");
    cadena_imprimir(miCadena);
    printf("\n");

    //Probar caso borde: Solo vocales
    printf("--- Test: Caso solo vocales ---\n");
    Cadena soloVocales = cadena_crear();
    cadena_desde_string(&soloVocales, "aeiouAEIOU");
    printf("Original: aeiouAEIOU\n");
    cadena_eliminar_vocales(&soloVocales);
    printf("Resultado tras eliminar : ");
    cadena_imprimir(soloVocales);
    printf("\n");

    //Probar caso borde: Sin vocales
    printf("--- Test: Caso sin vocales ---\n");
    Cadena sinVocales = cadena_crear();
    cadena_desde_string(&sinVocales, "bcd fgh");
    printf("Original: bcd fgh\n");
    cadena_eliminar_vocales(&sinVocales);
    printf("Resultado tras eliminar (debe ser igual): ");
    cadena_imprimir(sinVocales);
    printf("\n");

    //Liberar memoria
    printf("--- Limpiando memoria ---\n");
    cadena_destruir(&miCadena);
    cadena_destruir(&soloVocales);
    cadena_destruir(&sinVocales);

    if (miCadena == NULL) {
        printf("Memoria liberada correctamente.\n");
    }

    return 0;
}