#include "TAD_caracter.h"

int main(void){
    ListaC lc;
    lc = caracter_crear_lista();
    caracter_inserta_final(&lc,'a');
    caracter_inserta_final(&lc,'b');
    caracter_inserta_final(&lc,'c');
    caracter_inserta_final(&lc,'d');
    caracter_busca(lc,'b');
    caracter_busca(lc,'g');
    caracter_elimina(&lc,'a');
    caracter_mostrarL(lc);
    caracter_inserta_final(&lc,'e');
    caracter_elimina(&lc,'c');
    caracter_mostrarL(lc);
    lc = caracter_limpiaL(&lc);
    caracter_mostrarL(lc); 
    
    return 0;
}