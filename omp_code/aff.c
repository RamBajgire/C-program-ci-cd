#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel
    {
        int place = omp_get_place_num();
        printf("Thread %d bound to place %d\n", omp_get_thread_num(), place);
    }
    return 0;
}

