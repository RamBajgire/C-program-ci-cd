#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 26214400

int buffer[SIZE];

int main(int argc, char *argv[]) {
    int mpi_err, mpi_rank;
    double start_time, end_time;
    
    mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    
    srand(time(NULL) + mpi_rank); // Seed the random number generator
    
    if (mpi_rank == 0) {
        printf("Message to be broadcasted: \n");
        for (int i = 0; i < SIZE; i++) {
            buffer[i] = rand() % 10;
        }
        printf("\n");
    }
    
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize before timing
    start_time = MPI_Wtime();
    mpi_err = MPI_Bcast(buffer, SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    
    if (mpi_rank == 0) {
        printf("Time taken for MPI_Bcast: %f seconds\n", end_time - start_time);
    }
    
    mpi_err = MPI_Finalize();
    return 0;
}

