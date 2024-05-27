#include <mpi.h>
#include <stdio.h>

// mpiexec -n 8 hola2.exe

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int np;
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int ip;
    MPI_Comm_rank(MPI_COMM_WORLD, &ip);

    printf("hola mundo desde el proceso %d de %d procesadores\n", ip, np);

    MPI_Finalize();
    return 0;
}
