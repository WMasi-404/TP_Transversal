#include "TAD_pila.h"

int main(){
  Pila pila1 = pila_crear();
  
  pila_push(&pila1, 10);

  if(!pila_vacia(&pila1)){
    printf("Tope de la pila: %d\n", pila_top(&pila1));
  }else{
    printf("Error: La pila esta vacia. No se puede obtener el elemento superior.\n");
  }
  
  if(!pila_vacia(&pila1)){
    printf("Desapilando: %d\n", pila_pop(&pila1));
  }else{
    printf("Error: La pila esta vacia. No se puede realizar pop.\n");
  }
 
  if(!pila_vacia(&pila1)){
    printf("Tope de la pila despues de desapilar: %d\n", pila_top(&pila1));
  }else{
    printf("Error: La pila esta vacia. \n");
  }

}