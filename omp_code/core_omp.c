#include <stdio.h>
#include <omp.h>
#include <sched.h>

int main() {
    #pragma omp parallel
    {
        int core = sched_getcpu();  // Get actual CPU core
        printf("Thread %d running on core %d\n", omp_get_thread_num(), core);
    }
    return 0;
}

