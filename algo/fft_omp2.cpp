#include <iostream>
#include <complex>
#include <vector>
#include <random>
#include <cmath>
#include <omp.h>

using namespace std;

typedef complex<double> Complex;
typedef vector<Complex> CArray;

void fft(CArray &x, int depth = 0) {
    int N = x.size();
    if (N <= 1) return;

    // Base case: execute serially for small sizes to reduce overhead
    if (N <= 256) {
        for (int k = 0; k < N / 2; k++) {
            Complex t = polar(1.0, -2 * M_PI * k / N) * x[k + N / 2];
            Complex even = x[k];
            x[k] = even + t;
            x[k + N / 2] = even - t;
        }
        return;
    }

    // Divide
    CArray even(N / 2), odd(N / 2);
    #pragma omp parallel for schedule(static, 128)
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
        odd[i] = x[i * 2 + 1];
    }

    // Parallel recursive calls with limited depth
    #pragma omp task if (depth < 3)
    fft(even, depth + 1);
    #pragma omp task if (depth < 3)
    fft(odd, depth + 1);
    #pragma omp taskwait

    // Combine
    #pragma omp parallel for schedule(static, 128)
    for (int k = 0; k < N / 2; k++) {
        Complex t = polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

// Function to benchmark FFT execution
double benchmark_fft(int N) {

    // Initialize random data
    vector<Complex> data(N);
    #pragma omp parallel
    {
        unsigned int seed = omp_get_thread_num();
        mt19937 gen(seed);
        uniform_real_distribution<> dis(-10.0, 10.0);

        #pragma omp for schedule(static, 128)
        for (int i = 0; i < N; i++) {
            data[i] = Complex(dis(gen), dis(gen));
        }
    }

    // Measure execution time
    double start_time = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        fft(data);
    }
    double end_time = omp_get_wtime();

    return end_time - start_time;
}

int main() {
    int N;
//    cout << "Enter the FFT size (must be power of 2): ";
    cin >> N;

  //  if (N <= 0 || (N & (N - 1)) != 0) {
    //    cout << "Error: Number of elements must be a positive power of 2" << endl;
      //  return 1;
   // }

    // Benchmark FFT for 64 and 48 threads
    double time_threads = benchmark_fft(N);

    cout << "========================================\n";
    cout << "FFT Benchmark Results:\n";
    cout << "----------------------------------------\n";
    cout << "Execution Time: " << time_threads << " sec\n";
    cout << "========================================\n";

    return 0;
}
