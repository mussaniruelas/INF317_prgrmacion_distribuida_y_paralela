#include <omp.h>
#include <stdio.h>

// cd../ejer03

int main() {
    int mul = 0;
    int div = 0;
    int a = 30;
    int b = 4;

    #pragma omp parallel for reduction(+:mul)
    for (int i = 0; i < b; i++) {
        mul += a;
    }
    int np = 0;
    #pragma omp parallel for shared(div)
    // opcion 2 :
    // #pragma omp parallel for
    for (int i = b; i < a; i +=  b) {
        // #pragma omp task
        div += 1;
    }

    printf("La multipliacion es: %d\n", mul);
    printf("La divicion es: %d\n", div);
    return 0;
}