#include <stdio.h>

// Función para sumar dos números
int suma(int *a, int *b) {
    return *a + *b;
}

// Funcion para restar dos numeros
int resta(int *a, int *b){
    return *a - *b;
}

// Función para multiplicar dos números usando sumas
int multiplicar(int *a, int *b) {
    int resultado = 0;
    for (int i = 0; i < *b; ++i) {
        resultado += *a;
    }
    return resultado;
}

// Divicion entera de dos numeros usando restas
int div_entera(int *a, int *b){
    int resultado = 0;
    for (int i = *a; i > *b; i-=*b){
        resultado += 1;
    }
    return resultado;
}
// otra forma de ver el panorama
// Divicion con decimales 
/*float div_decimal(int *a, int*b){
    float resultado = 0;
    int residuo = *a;
    int contador_decimales = 0;

    while (residuo > *b)
    {
        residuo -= *b;
        resultado++;
    }
    // cosas que ya no convencen....
    // mejor usar una serie de taylor 
    while(contador_decimales < 8){
        residuo *= 10;
        float parte_decimal = 0;
        while (residuo > *b)
        {
            residuo -= *b;
            parte_decimal++;
        }
        resultado = resultado + parte_decimal/10;
        contador_decimales++;
    }
    return resultado;
}*/

int main() {
    int num1 = 5;
    int num2 = 3;

    printf("Suma: %d\n", suma(&num1, &num2));
    printf("Resta: %d\n", resta(&num1, &num2));
    printf("Multiplicación: %d\n", multiplicar(&num1, &num2));
    printf("Divicion Entera: %d\n",div_entera(&num1, &num2));

    return 0;
}

