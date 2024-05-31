#include <omp.h>
#include <stdio.h>

void process(int n) {
    printf("proceso %d\n", n);
}

int main() {

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < 20; i++) {
            process(i);
        }
    }
        
    return 0;
}