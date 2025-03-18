#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 26214400

int buffer[SIZE], sum[SIZE];

int main(int argc, char *argv[]) {
    int mpi_err, mpi_rank;
    double start_time, end_time;
    
    mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    
    srand(time(NULL) + mpi_rank); // Seed the random number generator with rank-specific value
    
    for (int i = 0; i < SIZE; i++) {
        buffer[i] = (mpi_rank + rand()) % 10;
    }
    
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize before timing
    start_time = MPI_Wtime();
    mpi_err = MPI_Reduce(buffer, sum, SIZE, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    
    if (mpi_rank == 0) {
        printf("\nTime taken for MPI_Reduce: %f seconds\n", end_time - start_time);
    }
    
    mpi_err = MPI_Finalize();
    return 0;
}

