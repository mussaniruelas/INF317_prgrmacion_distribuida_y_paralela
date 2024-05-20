#include <stdio.h>
#include <omp.h>

int main() {
    int n = 20; // n terminos
    int m = 8;  // m procesadores
    int v[n];
    int ns = n/m, r = n %m;
    omp_set_num_threads(m); 

    #pragma omp parallel
    {
        // falta hacer 
        #pragma omp for
        for (int i = 1; i <= m; i++)
        {
            int id = omp_get_thread_num();
            int ini,fin;
            if (id < r ){
                ini = id * ns + id ;
                fin = (id == 0) ? ini+ns+1 : ini+ns+id;
            }else{
                ini = id * ns + r;
                fin = ini + ns; 
            }
            //printf("id: %d, ini: %d, fin: %d\n\n",id,ini,fin);
            for (int j = ini; j < fin; j++)
            {
                v[j] = 2 * j+2;
                //printf("j:%d :hilo %d: %d\n",j, id, v[i]);
            }
        }
        

        /*int id = omp_get_thread_num();
        #pragma omp for //schedule(static)
        for (int i = 1; i <= n; i++) {
            v[i] = 2 * i;
            printf("%d:hilo %d: %d\n",ns, id, v[i]);
        }*/
    }
    for (int i = 0; i < n; i++)
        printf("%d, ",v[i]);
    return 0;
}
