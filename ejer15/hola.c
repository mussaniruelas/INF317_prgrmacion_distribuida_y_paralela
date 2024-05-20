/*#include <omp.h>
#include <stdio.h>

int main() {
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hola mundo(%d) \n", ID);
    }
}*/
#include <omp.h>
#include <stdio.h>

void process(int n) {
    printf("Processing part %d\n", n);
}

int main() {
    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < 20; i++) {
                
                #pragma omp task
                {
                printf("i:%d\n",i);
                process(i);
                }
            }
        }
    }
    return 0;
}