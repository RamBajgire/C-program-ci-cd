#include <iostream>
#include <limits>
#include <cmath>
#include <omp.h>
#include <chrono> // For timing

// Matrix size constants.
constexpr int N = 20; // Number of hidden states
constexpr int M = 20; // Number of possible observations
constexpr int T = 20; // Length of the hidden states sequence
constexpr int seed = 0; // Seed for generating the sequence
constexpr float MIN_FLOAT = -1.0 * std::numeric_limits<float>::max(); // Minimal float value

bool ViterbiCondition(float x, float y, float z, float compare);

int main() {
    auto start_time = std::chrono::high_resolution_clock::now(); // Start timing

    try {
        // Initializing and generating initial probabilities for the hidden states.
        float* pi = new float[N];
        for (int i = 0; i < N; ++i) {
            pi[i] = std::log10(1.0f / N);
        }

        // Generating transition matrix A for the Markov process.
        float** a = new float*[N];
        for (int i = 0; i < N; ++i) {
            a[i] = new float[N];
        }

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                float prob = 1.0f / N;
                a[i][j] = std::log10(prob);
            }
        }

        // Generating emission matrix B for the Markov process.
        float** b = new float*[N];
        for (int i = 0; i < N; ++i) {
            b[i] = new float[M];
        }

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                float prob = ((i + j) % M) * 2.0f / M / (M - 1);
                b[i][j] = (prob == 0.0f) ? MIN_FLOAT : std::log10(prob);
            }
        }

        // Generating the sequence of the observations produced by the hidden Markov chain.
        int* seq = new int[T];
        for (int i = 0; i < T; ++i) {
            seq[i] = (i * i + seed) % M;
        }

        // Initialization of the Viterbi matrix and the matrix of back pointers.
        float** viterbi = new float*[N];
        int** back_pointer = new int*[N];
        for (int i = 0; i < N; ++i) {
            viterbi[i] = new float[T];
            back_pointer[i] = new int[T];
        }

        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < T; ++j) {
                viterbi[i][j] = (j != 0) ? MIN_FLOAT : pi[i] + b[i][seq[0]];
                back_pointer[i][j] = -1;
            }
        }

        // The sequential steps of the Viterbi algorithm.
        for (int j = 0; j < T - 1; ++j) {
            #pragma omp parallel for collapse(2)
            for (int i = 0; i < N; ++i) {
                for (int k = 0; k < N; ++k) {
                    if (ViterbiCondition(viterbi[k][j], b[i][seq[j + 1]], a[k][i], viterbi[i][j + 1])) {
                        viterbi[i][j + 1] = viterbi[k][j] + a[k][i] + b[i][seq[j + 1]];
                        back_pointer[i][j + 1] = k;
                    }
                }
            }
        }

        // Getting the Viterbi path based on the matrix of back pointers.
        int* vit_path = new int[T];
        float v_max = MIN_FLOAT;

        #pragma omp parallel for
        for (int i = 0; i < N; ++i) {
            if (viterbi[i][T - 1] > v_max) {
                #pragma omp critical
                {
                    if (viterbi[i][T - 1] > v_max) {
                        v_max = viterbi[i][T - 1];
                        vit_path[T - 1] = i;
                    }
                }
            }
        }

        for (int i = T - 2; i >= 0; --i) {
            vit_path[i] = back_pointer[vit_path[i + 1]][i + 1];
        }

        std::cout << "The Viterbi path is: " << std::endl;
        for (int k = 0; k < T; ++k) {
            std::cout << vit_path[k] << " ";
        }
        std::cout << std::endl;

        // Clean up dynamically allocated memory.
        delete[] pi;
        for (int i = 0; i < N; ++i) {
            delete[] a[i];
            delete[] b[i];
            delete[] viterbi[i];
            delete[] back_pointer[i];
        }
        delete[] a;
        delete[] b;
        delete[] viterbi;
        delete[] back_pointer;
        delete[] seq;
        delete[] vit_path;

    } catch (std::exception const& e) {
        std::cout << "An exception is caught!\n";
        std::cout << "Error message: " << e.what() << std::endl;
        std::terminate();
    }

    auto end_time = std::chrono::high_resolution_clock::now(); // End timing
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Execution time: " << duration << " milliseconds" << std::endl;

    std::cout << "The sample completed successfully!" << std::endl;
    return 0;
}

// The method checks if all three components of the sum are not equivalent to logarithm of zero 
// (that is incorrect value and is substituted with minimal possible value of float) and that 
// the Viterbi value on the new step exceeds the current one.
bool ViterbiCondition(float x, float y, float z, float compare) {
    return (x > MIN_FLOAT) && (y > MIN_FLOAT) && (z > MIN_FLOAT) && (x + y + z > compare);
}
