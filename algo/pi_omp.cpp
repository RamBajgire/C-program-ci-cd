#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <sys/time.h>
#include <time.h>
#include <omp.h>

int main(int argc, char** argv) {
     size_t n = 10000000; // 10 million intervals
     n = atoi( argv[1]);
     printf (" n : %d \n" , n);
    const double dx = 1.0 / n;
    std::vector<double> results(n, 0.0);

    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    // Parallel computation of results
    #pragma omp parallel for
    for (size_t i = 0; i < n; ++i) {
        double x = (i + 0.5) * dx;
        results[i] = std::sqrt(1.0 - x * x) * dx;
    }

    // Parallel reduction for summation
    double pi = 0.0;
    #pragma omp parallel for reduction(+:pi)
    for (size_t i = 0; i < n; ++i) {
        pi += results[i];
    }
    pi *= 4.0;

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;

    std::cout << std::fixed << std::setprecision(10) << "Approximation of Pi: " << pi << std::endl;
    std::cout << "Time measured: " << elapsed << " sec" << std::endl;

    return 0;
}
