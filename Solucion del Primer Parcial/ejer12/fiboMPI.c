#include <mpi.h>
#include <stdio.h>

// Función para calcular el n-ésimo término de Fibonacci
// cd ../ejer12
// mpiexec -n 8 fiboMPI.exe

int fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int MASTER = 0;
    const int REQUEST_TAG = 1;
    const int RESULT_TAG = 2;

    int n = 20;  // Número de términos de Fibonacci a calcular
    int results[n];  // Array para almacenar los resultados

    if (rank == MASTER) {  // Proceso maestro
        int next_term = 0;
        int active_slaves = size - 1;

        // Inicialmente enviar solicitudes a todos los esclavos
        for (int i = 1; i < size && next_term < n; i++) {
            MPI_Send(&next_term, 1, MPI_INT, i, REQUEST_TAG, MPI_COMM_WORLD);
            next_term++;
        }

        // Procesar resultados y enviar nuevas solicitudes
        while (active_slaves > 0) {
            int result[2];  // [0]: term index, [1]: Fibonacci value
            MPI_Status status;

            // Recibir el resultado de un esclavo
            MPI_Recv(result, 2, MPI_INT, MPI_ANY_SOURCE, RESULT_TAG, MPI_COMM_WORLD, &status);
            int slave_rank = status.MPI_SOURCE;  // Obtener el rango del proceso que envió el mensaje

            // Guardar el resultado
            results[result[0]] = result[1];

            // Si hay más términos para calcular, enviar nueva solicitud
            if (next_term < n) {
                MPI_Send(&next_term, 1, MPI_INT, slave_rank, REQUEST_TAG, MPI_COMM_WORLD);
                next_term++;
            } else {
                // No hay más términos, enviar señal de terminación
                int terminate = -1;
                MPI_Send(&terminate, 1, MPI_INT, slave_rank, REQUEST_TAG, MPI_COMM_WORLD);
                active_slaves--;
            }
        }

        // Imprimir los resultados
        for (int i = 0; i < n; i++) {
            printf("Fibonacci(%d) = %d\n", i, results[i]);
        }
    } else {  // Procesos esclavos
        while (1) {
            int term;
            MPI_Status status;

            // Recibir una solicitud del maestro
            MPI_Recv(&term, 1, MPI_INT, MASTER, REQUEST_TAG, MPI_COMM_WORLD, &status);

            // Comprobar si es una señal de terminación
            if (term == -1) {
                break;
            }

            // Calcular el término de Fibonacci
            int result = fibonacci(term);

            // Enviar el resultado de vuelta al maestro
            int result_message[2] = { term, result };
            MPI_Send(result_message, 2, MPI_INT, MASTER, RESULT_TAG, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
