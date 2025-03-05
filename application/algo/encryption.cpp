#include <bits/stdc++.h>
#include <omp.h>
#define MAX 26
using namespace std;

// Function to encrypt the string using OpenMP
void encryptStr(string &str, int n, int x)
{
    x = x % MAX; // Reduce unnecessary rotations
    vector<int> freq(MAX, 0);

    // Calculate character frequency in parallel
    #pragma omp parallel for shared(freq)
    for (int i = 0; i < n; i++) {
        #pragma omp atomic
        freq[str[i] - 'a']++;
    }

    // Encrypt the string in parallel
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        int charIndex = str[i] - 'a';
        if (freq[charIndex] % 2 == 0) {
            str[i] = (char)(((charIndex + x) % MAX) + 'a');
        } else {
            int pos = (charIndex - x + MAX) % MAX;
            str[i] = (char)(pos + 'a');
        }
    }
}

// Function to generate a large random string
string generateLargeString(int size) {
    string str(size, ' ');
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        str[i] = 'a' + rand() % MAX;
    }
    return str;
}

// Benchmarking function
void benchmark(int size, int x) {
    string str = generateLargeString(size);
    double start_time = omp_get_wtime();
    encryptStr(str, size, x);
    double end_time = omp_get_wtime();
    cout << "Encryption Time: " << (end_time - start_time) << " seconds" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <number_of_elements>" << endl;
        cout << "Number of elements must be a power of 2" << endl;
        return 1;
    }

    // Get size from command line
    int size = atoi(argv[1]); // Large string size for benchmarking
   // omp_set_num_threads(64); // Set OpenMP to use 64 threads
    int x = 20; // Encryption shift value
   cout<<"size: "<<size<<endl;
    cout << "\n Number of threads= "<<omp_get_max_threads()<<" threads "<< endl;
    benchmark(size, x);
    return 0;
}


