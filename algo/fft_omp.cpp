#include <iostream>
#include <complex>
#include <cmath>
#include <iterator>
#include <omp.h>
#include <chrono>
#include <vector>

using namespace std;

unsigned int bitReverse(unsigned int x, int log2n) {
    int n = 0;
    int mask = 0x1;
    for (int i = 0; i < log2n; i++) {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

const double PI = 3.1415926536;

template<class Iter_T>
void fft(Iter_T a, Iter_T b, int log2n) {
    typedef typename iterator_traits<Iter_T>::value_type complex;
    const complex J(0, 1);
    int n = 1 << log2n;

    // Parallelize the bit reversal
    #pragma omp parallel for schedule(dynamic,1)
    for (unsigned int i = 0; i < n; ++i) {
        b[bitReverse(i, log2n)] = a[i];
    }

    for (int s = 1; s <= log2n; ++s) {
        int m = 1 << s;
        int m2 = m >> 1;
        complex w(1, 0);
        complex wm = exp(-J * (PI / m2));

        // Parallelize the inner loops
        #pragma omp parallel for private(w) schedule(dynamic,1)
        for (int j = 0; j < m2; ++j) {
            complex w_temp = w;
            for (int k = j; k < n; k += m) {
                complex t = w_temp * b[k + m2];
                complex u = b[k];
                b[k] = u + t;
                b[k + m2] = u - t;
            }
            w_temp *= wm;
        }
    }
}

int main(int argc, char* argv[]) {
/*    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <log2n>" << endl;
        return 1;
    }

    int log2n = atoi(argv[1]);
    int n = 1 << log2n;
*/
    int log2n, n;
    cin>>log2n;
    n = 1 <<log2n;
    printf(" log2n: %d n: %d \n", log2n, n);
    typedef complex<double> cx;
    vector<cx> a(n);
    vector<cx> b(n);

    // Initialize input array with some values
    // #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        a[i] = cx(i, i); // Example initialization
    }

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    // Perform FFT
    fft(a.begin(), b.begin(), log2n);

    // Stop timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    // Output the timing
    cout << "FFT size: " << n << " (2^" << log2n << ")" << endl;
    cout << "Time taken: " << elapsed.count() << " seconds" << endl;

    return 0;
}
