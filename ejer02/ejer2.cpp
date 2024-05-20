#include <iostream>
using namespace std;

// Función para sumar dos números
int suma(int* a, int* b) {
    return *a + *b;
}

// Funcion para restar dos numeros
int resta(int* a, int* b){
    return *a - *b;
}

// Función para multiplicar dos números usando sumas
int mul(int* a, int* b) {
    int resultado = 0;
    for (int i = 0; i < *b; ++i) {
        resultado += *a;
    }
    return resultado;
}

// Divicion entera de dos numeros usando restas
int div_entera(int* a, int* b){
    int resultado = 0;
    for (int i = *a; i > *b; i-=*b){
        resultado += 1;
    }
    return resultado;
}

// Función para multiplicar dos números utilizando sumas repetidas
int multiplicar(const int& a, const int& b) {
    int resultado = 0;
    for (int i = 0; i < b; ++i) {
        resultado += a;
    }
    return resultado;
}

int main() {
    int num1 = 4;
    int num2 = 3;
    cout <<  num1 << " y " << num2 << " es: "<< endl;
    cout << "Multiplicación: " << multiplicar(num1, num2) << endl;
    cout << "Suma: " << suma(&num1,&num2) << endl;
    cout << "Resta: " << resta(&num1,&num2) << endl;
    cout << "Multiplicacion: " << mul(&num1,&num2) << endl;
    cout << "Division Entera: " << div_entera(&num1,&num2) << endl;

    return 0;
}
