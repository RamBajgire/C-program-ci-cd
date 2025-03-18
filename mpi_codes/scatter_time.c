#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 26214400
#define EPP 3276800

int sbuffer[SIZE], rbuffer[EPP];

void create_array() {
    for (int i = 0; i < SIZE; i++) {
        sbuffer[i] = rand() % 10;
    }
}

int main(int argc, char *argv[]) {
    int mpi_err, mpi_rank, size_comm;
    double start_time, end_time;

    mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    mpi_err = MPI_Comm_size(MPI_COMM_WORLD, &size_comm);

    srand(time(NULL) + mpi_rank);
    if (mpi_rank == 0) {
        create_array();
    }
    
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize before timing
    start_time = MPI_Wtime();
    mpi_err = MPI_Scatter(sbuffer, EPP, MPI_INT, rbuffer, EPP, MPI_INT, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    
    printf("Rank:%d \t Time taken for MPI_Scatter: %f seconds\n", mpi_rank, end_time - start_time);

    mpi_err = MPI_Finalize();
    return 0;
}

