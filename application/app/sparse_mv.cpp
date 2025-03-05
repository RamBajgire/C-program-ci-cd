#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <omp.h>

// Function to generate a random sparse matrix in CSR format
void generateSparseMatrix(int N, int nnz, std::vector<int>& row_ptr, 
                          std::vector<int>& col_idx, std::vector<double>& values) {
    row_ptr.resize(N + 1, 0);
    col_idx.resize(nnz);
    values.resize(nnz);

    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist_val(0.1, 10.0);
    std::uniform_int_distribution<int> dist_col(0, N - 1);

    int nnz_count = 0;
    for (int i = 0; i < N; ++i) {
        int row_nnz = std::min(nnz / N + 1, N);
        row_ptr[i] = nnz_count;
        
        for (int j = 0; j < row_nnz && nnz_count < nnz; ++j) {
            col_idx[nnz_count] = dist_col(rng);
            values[nnz_count] = dist_val(rng);
            ++nnz_count;
        }
    }
    row_ptr[N] = nnz_count;
}

// Parallelized Sparse Matrix-Vector Multiplication (SpMV) using OpenMP
void spmv_csr_omp(const std::vector<int>& row_ptr, const std::vector<int>& col_idx,
                   const std::vector<double>& values, const std::vector<double>& x,
                   std::vector<double>& y) {
    int N = y.size();

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int j = row_ptr[i]; j < row_ptr[i + 1]; ++j) {
            sum += values[j] * x[col_idx[j]];
        }
        y[i] = sum;
    }
}

int main() {
    int N = 10000;  // Matrix size (N x N)
    int nnz = 50000;  // Number of nonzero elements

    // CSR Matrix representation
    std::vector<int> row_ptr, col_idx;
    std::vector<double> values;

    // Generate a random sparse matrix
    generateSparseMatrix(N, nnz, row_ptr, col_idx, values);

    // Input vector x and output vector y
    std::vector<double> x(N, 1.0), y(N, 0.0);

    // Measure execution time of OpenMP SpMV
    auto start = std::chrono::high_resolution_clock::now();
    spmv_csr_omp(row_ptr, col_idx, values, x, y);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "OpenMP SpMV Execution Time: " << elapsed.count() << " seconds\n";

    return 0;
}

