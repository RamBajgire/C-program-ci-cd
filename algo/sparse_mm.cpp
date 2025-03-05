#include <iostream>
#include <vector>
#include <random>
#include <unordered_map>
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

// Sparse Matrix-Matrix Multiplication (SpMM) using OpenMP
void spmm_csr_omp(const std::vector<int>& A_row_ptr, const std::vector<int>& A_col_idx,
                  const std::vector<double>& A_values, const std::vector<int>& B_row_ptr,
                  const std::vector<int>& B_col_idx, const std::vector<double>& B_values,
                  int N, std::vector<int>& C_row_ptr, std::vector<int>& C_col_idx,
                  std::vector<double>& C_values) {
    
    C_row_ptr.resize(N + 1, 0);
    std::vector<std::unordered_map<int, double>> C_temp(N);

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        std::unordered_map<int, double> row_values;

        for (int j = A_row_ptr[i]; j < A_row_ptr[i + 1]; ++j) {
            int A_col = A_col_idx[j];
            double A_val = A_values[j];

            for (int k = B_row_ptr[A_col]; k < B_row_ptr[A_col + 1]; ++k) {
                int B_col = B_col_idx[k];
                double B_val = B_values[k];
                
                row_values[B_col] += A_val * B_val;
            }
        }
        
        C_temp[i] = std::move(row_values);
    }

    // Convert unordered_map to CSR format
    int nnz = 0;
    for (int i = 0; i < N; ++i) {
        C_row_ptr[i] = nnz;
        for (auto& entry : C_temp[i]) {
            C_col_idx.push_back(entry.first);
            C_values.push_back(entry.second);
            nnz++;
        }
    }
    C_row_ptr[N] = nnz;
}

int main(int argc, char** argv) {
    int N = atoi(argv[1]);   // Matrix size (N x N)
    int nnz = N*10; // Number of nonzero elements for Tridiagonal (banded) Sparsity
     printf("size: %d\n",N);
    // CSR Representation of Matrices A and B
    std::vector<int> A_row_ptr, A_col_idx, B_row_ptr, B_col_idx;
    std::vector<double> A_values, B_values;

    // Generate random sparse matrices A and B
    generateSparseMatrix(N, nnz, A_row_ptr, A_col_idx, A_values);
    generateSparseMatrix(N, nnz, B_row_ptr, B_col_idx, B_values);

    // CSR Representation of Matrix C
    std::vector<int> C_row_ptr, C_col_idx;
    std::vector<double> C_values;

    // Measure execution time of OpenMP SpMM
    auto start = std::chrono::high_resolution_clock::now();
    spmm_csr_omp(A_row_ptr, A_col_idx, A_values, B_row_ptr, B_col_idx, B_values, 
                  N, C_row_ptr, C_col_idx, C_values);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "OpenMP SpMM Execution Time: " << elapsed.count() << " seconds\n";

    return 0;
}
