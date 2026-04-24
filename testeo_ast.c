#include   "TAD_ast.h"

int main(){
    Tdata A = create_set();
    Tdata B = create_set();

    insert_set(&A, create_str_ast());
    insert_set(&B, create_str_ast());

    printf("A: ");
    printSet(A);
    printf("\nB: ");
    printSet(B);

    printf("\nA es subconjunto de B? %d\n", subset(A, B));
    printf("A y B son iguales? %d\n", equals_set(A, B));

    return 0;
}