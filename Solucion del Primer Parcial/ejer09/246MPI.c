// Genere la serie 2, 4, 6, 8, 10, 12, 14, 16, 18… en M vectores(procesadores) para N términos con MPI 

// cd ejer09
// mpiexec -n 8 246MPI.exe 
#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int ip,np;
    MPI_Comm_rank(MPI_COMM_WORLD, &ip);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    int n = 10;
    int v[n];
    int nro_elem = n / np, resto = n % np;
    int seccion_actual = nro_elem + (( ip < resto) ? 1 : 0);
    for (int i = 0; i < n; i++)
        v[i]=-1;
    

    // el vector local 
    int vector_local[seccion_actual];

    // este es el ajuste para cada seccion
    int ajuste = nro_elem * ip + ((ip < resto) ? ip : resto);

    // Crear los arreglos para el nro de terminos y posiciones a recibir 
    int nro_elem_sec[np];
    int pos_sec[np];
    
    // repartiendo datos 
    MPI_Allgather(&seccion_actual, 1, MPI_INT, nro_elem_sec, 1, MPI_INT,MPI_COMM_WORLD); // para el vector de nro elementos
    MPI_Allgather(&ajuste, 1, MPI_INT,pos_sec,1,MPI_INT,MPI_COMM_WORLD); //para el vector de posiciones
    
    for (int i = 0; i < seccion_actual; i++){
        vector_local[i] = 2 * (i + ajuste + 1);
        printf("%d, ",vector_local[i]);
    }

    // recolectar todo en el resultado
    
    MPI_Gatherv(vector_local, seccion_actual, MPI_INT, v, nro_elem_sec, pos_sec, MPI_INT, 0, MPI_COMM_WORLD);
        

    // mostrar los resultados
    if (ip == 0)
    {
        for (int  i = 0; i < n; i++)
            printf("%d, ",v[i]);
    }


    MPI_Finalize();
    return 0;
}