#include <mpi.h>
#include <stdio.h>

// mpiexec -n 8 pruebas.exe

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int ip, np;
    MPI_Comm_rank(MPI_COMM_WORLD, &ip);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int n = 20;
    double m[n][n];  
    double v[n];     
    double r[n];

    // Inicialización de la matriz y el vector en el proceso raíz (ip = 0)
    if (ip == 0) {
        for (int i = 0; i < n; i++) {
            v[i] = 2; //i + 1;
            for (int j = 0; j < n; j++) {
                m[i][j] = 2; //i * n + j + 1;  // Ejemplo de matriz
            }
        }
    }

    // Compartir el vector v a todos los procesos
    MPI_Bcast(v, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Determinar el número de filas que cada proceso manejará
    int nro_filas = n / np;
    int sobrante_filas = n % np;

    // Procesos adicionales toman una fila extra si hay un resto
    int nro_filas_actual = nro_filas + (ip < sobrante_filas ? 1 : 0);

    // Preparar submatrices y subresultados para cada proceso
    double ml[nro_filas_actual][n];
    double rl[nro_filas_actual];

    // Crear los arreglos de desplazamientos y cuentas para MPI_Scatterv
    int nro_elem_env[np]; // Número de elementos a enviar a cada proceso
    int pos_env[np];     // Desplazamientos en el buffer de envío

    // Crear los arreglos de desplazamientos y cuentas para MPI_Gatherv
    int nro_elem_rec[np]; // Número de elementos a recibir de cada proceso
    int pos_rec[np]; // Desplazamientos en el buffer de recepción

    // Calculo de desplazamientos y cuentas
    // para MPI_Scatterv 
    int nro_elem_env_aux = nro_filas_actual * n;
    int pos_env_aux = (nro_filas * ip + (ip < sobrante_filas ? ip : sobrante_filas)) * n;
    MPI_Allgather(&nro_elem_env_aux, 1, MPI_INT, nro_elem_env, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&pos_env_aux, 1, MPI_INT, pos_env, 1, MPI_INT, MPI_COMM_WORLD);

    // para MPI_Gatherv
    int nro_elem_rec_aux = nro_filas_actual;
    int pos_rec_aux = nro_filas * ip + (ip < sobrante_filas ? ip : sobrante_filas);
    MPI_Allgather(&nro_elem_rec_aux, 1, MPI_INT, nro_elem_rec, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&pos_rec_aux, 1, MPI_INT, pos_rec, 1, MPI_INT, MPI_COMM_WORLD);

    // Scatter de la matriz
    MPI_Scatterv(&(m[0][0]), nro_elem_env, pos_env, MPI_DOUBLE, &(ml[0][0]), nro_filas_actual * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Cálculo parcial del vector resultante
    for (int i = 0; i < nro_filas_actual; i++) {
        rl[i] = 0.0;
        for (int j = 0; j < n; j++) {
            rl[i] += ml[i][j] * v[j];
        }
    }

    // Gather del resultado parcial
    MPI_Gatherv(rl, nro_filas_actual, MPI_DOUBLE, r, nro_elem_rec, pos_rec, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // El proceso raíz imprime el resultado
    if (ip == 0) {
        printf("Resultado de A * v:\n");
        for (int i = 0; i < n; i++) {
            printf("%f\n", r[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
