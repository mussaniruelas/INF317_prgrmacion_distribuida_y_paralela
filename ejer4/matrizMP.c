#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {

    struct timeval start, end;
    int n = 10;
    int m[n][n];
    int v[n], r[n];
    // iniciamos el contador de tiempo
    gettimeofday(&start, NULL);

    
    for (int i = 0; i < n; i++) {
        v[i] = 2; //rand() % 100;
        r[i] = 0;
        for (int j = 0; j < n; j++) {
            m[i][j] = 2; //rand() % 100;
        }
    }
    printf("Resultado:\n");
    #pragma omp parallel for
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            r[i]+=m[i][j]*v[i];
            //printf(" %d |",r[i]);
        }
        //printf(" %d |\n",r[i]);
    }
    
    for (int i = 0; i < n; i++)
        printf(" %d \n",r[i]);
    

    // finalizamos el contador de tiempo
    gettimeofday(&end, NULL);
    // se calcula el tiempo
    long seconds = (end.tv_sec - start.tv_sec);
    long micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    printf("Tiempo de ejecución: %ld microsegundos (%f segundos)\n", micros, micros / 1000000.0);

    return 0;
}