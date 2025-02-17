#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 1000000000  // 1 Billion iterations

void compute() {
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (long i = 0; i < N; i++) {
        sum += 1.0 / (i + 1);
    }
    printf("Final sum: %lf\n", sum);
}

int main() {
    double start, end;

    printf("Running on %d threads\n", omp_get_max_threads());

    start = omp_get_wtime();
    compute();
    end = omp_get_wtime();

    printf("Execution time: %f seconds\n", end - start);

    return 0;
}

