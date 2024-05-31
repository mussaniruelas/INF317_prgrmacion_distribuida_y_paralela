#include <stdio.h>

// Función para sumar dos números
void suma(int *a, int *b) {
    *a = *a + *b;
}

// Función para restar dos números
void resta(int *a, int *b) {
    *a = *a - *b;
}

// Función para multiplicar dos números usando sumas
int multiplicar(int *a, int *b) {
    int resultado = 0;
    for (int i = 0; i < *b; ++i) {
        int temp = *a;  
        suma(&resultado, &temp);
    }
    return resultado;
}

// División entera de dos números usando restas
int div_entera(int *a, int *b) {
    int resultado = 0;
    int temp = *a;
    while (temp >= *b) {
        resta(&temp, b);
        resultado++;
    }
    return resultado;
}

int main() {
    int num1 = 5;
    int num2 = 3;
    int s = num1;
    int r = num1;

    // Realizamos las operaciones
    suma(&s, &num2);
    resta(&r, &num2);

    // Imprimimos los resultados
    printf("Suma: %d\n", s);
    printf("Resta: %d\n", r);
    printf("Multiplicación: %d\n", multiplicar(&num1, &num2));
    printf("División Entera: %d\n", div_entera(&num1, &num2));

    return 0;
}
