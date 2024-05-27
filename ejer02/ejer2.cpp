#include <iostream>
using namespace std;
// cd ../ejer02
// Definición de la clase Mate
class Mate {
public:
    // Función para sumar dos números
    static int suma(int* a, int* b) {
        return *a + *b;
    }

    // Función para restar dos números
    static int resta(int* a, int* b) {
        return *a - *b;
    }

    // Función para multiplicar dos números usando sumas
    static int mul(int* a, int* b) {
        int resultado = 0;
        for (int i = 0; i < *b; ++i) {
            resultado = suma(&resultado, a);
        }
        return resultado;
    }

    // División entera de dos números usando restas
    static int div_entera(int* a, int* b) {
        int resultado = 0;
        int i = *a;
        while (i >= *b) {
            i = resta(&i, b);
            resultado++;
        }
        return resultado;
    }

    // Función para multiplicar dos números utilizando sumas repetidas
    static int multiplicar(const int& a, const int& b) {
        int resultado = 0;
        for (int i = 0; i < b; ++i) {
            resultado += a;
        }
        return resultado;
    }
};

int main() {
    int num1 = 4;
    int num2 = 3;
    cout << "Los números son: " << num1 << " y " << num2 << endl;
    cout << "Multiplicación: " << Mate::multiplicar(num1, num2) << endl;
    cout << "Suma: " << Mate::suma(&num1, &num2) << endl;
    cout << "Resta: " << Mate::resta(&num1, &num2) << endl;
    cout << "Multiplicación usando sumas: " << Mate::mul(&num1, &num2) << endl;
    cout << "División Entera: " << Mate::div_entera(&num1, &num2) << endl;

    return 0;
}
