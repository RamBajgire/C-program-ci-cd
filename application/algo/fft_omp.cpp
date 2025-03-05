#include <iostream>
#include <complex>
#include <vector>
#include <chrono>
#include <random>
#include <cmath>
#include <omp.h>

using namespace std;
using namespace std::chrono;

typedef complex<double> Complex;
typedef vector<Complex> CArray;

void fft(CArray &x) {
    int N = x.size();
    if (N <= 1) return;

    // Divide
    CArray even(N / 2), odd(N / 2);
    #pragma omp parallel for
    for (int i = 0; i < N / 2; i++) {
        even[i] = x[i * 2];
         odd[i] = x[i * 2 + 1];
    }

    // Conquer
    #pragma omp task
    fft(even);
    #pragma omp task
    fft(odd);
    #pragma omp taskwait

    // Combine
    #pragma omp parallel for
    for (int k = 0; k < N / 2; k++) {
        Complex t = polar(1.0, -2 * M_PI * k / N) * odd[k];
        x[k] = even[k] + t;
        x[k + N / 2] = even[k] - t;
    }
}

int main() {//int argc, char* argv[]) {
    // if (argc != 2) {
    //     cout << "Usage: " << argv[0] << " <number_of_elements>" << endl;
    //     cout << "Number of elements must be a power of 2" << endl;
    //     return 1;
    // }

    // Get size from command line
    int N;
    cout <<" Enter the size "<<endl;
    cin>>N;
    
    // Check if N is a power of 2
    if (N <= 0 || (N & (N - 1)) != 0) {
        cout << "Error: Number of elements must be a positive power of 2" << endl;
        return 1;
    }

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(-10.0, 10.0);

    // Create and fill array with random data
    CArray data(N);
    cout << "Generating " << N << " random elements..." << endl;
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        data[i] = Complex(dis(gen), dis(gen));
    }

    // Print first few elements of input
    // cout << "\nFirst 5 elements of input (or all if size < 5):" << endl;
    // for (int i = 0; i < min(5, N); i++) {
    //     cout << data[i] << endl;
    // }

    // Measure FFT time
    double time_spent = 0.0;
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);
    #pragma omp parallel
    {
        #pragma omp single
        fft(data);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;
    printf("Time measured: %lf sec\n", elapsed);

    // Print first few elements of output
    // cout << "\nFirst 5 elements of output (or all if size < 5):" << endl;
    // for (int i = 0; i < min(5, N); i++) {
    //     cout << data[i] << endl;
    // }

cout << "\nNumber of threads= "<<omp_get_max_threads()<<" threads "<< endl;
    return 0;
}
