//1/1^2 + 1/2^2 + 1/3^2 + 1/4^2 + 1/5^2.... = pi^2/6
#include <mpi.h>
#include <stdio.h>
#include <math.h>

// cd ../ejer06
// mpiexec -n 8 piMPI.exe

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int ip,np;
    MPI_Comm_rank(MPI_COMM_WORLD, &ip);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    double sl = 0.0;
    int n=1000;
    /*if (ip == 0)
        scanf("%d",&n);
    printf("----------- n=%d\n",n);
    MPI_Barrier(MPI_COMM_WORLD);*/
    for (int i = ip + 1; i <= n; i+=np)  {
        double x = 1.0 / (i * i);
        sl += x;
        //printf("Proceso %d: i = %d, x = %lf, sl = %lf\n", ip, i, x, sl);
    }
    double st;
    MPI_Reduce(&sl, &st, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (ip == 0)
    {
        double pi = sqrt(st*6);
        printf("Aproximacion de pi: %f\n", pi);
    }
    
    
    MPI_Finalize();
    return 0;
}