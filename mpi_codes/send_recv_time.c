#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 26214400

int sbuffer[SIZE], rbuffer[SIZE];

void create_array() {
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        sbuffer[i] = rand() % 10;
    }
}

int main(int argc, char *argv[]) {
    int mpi_err, mpi_rank;
    MPI_Status mpi_status;
    double start_time, end_time;

    mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize before measurement
    start_time = MPI_Wtime(); // Start timing

    if (mpi_rank == 1) {
        create_array();
        mpi_err = MPI_Send(sbuffer, SIZE, MPI_INT, 0, 123, MPI_COMM_WORLD);
    } else if (mpi_rank == 0) {
        mpi_err = MPI_Recv(rbuffer, SIZE, MPI_INT, 1, 123, MPI_COMM_WORLD, &mpi_status);
    }
    
    MPI_Barrier(MPI_COMM_WORLD); // Synchronize after communication
    end_time = MPI_Wtime(); // End timing
    
    if (mpi_rank == 0) {
        printf("Total time for Send and Receive: %f seconds\n", end_time - start_time);
    }
    
    mpi_err = MPI_Finalize();
    return 0;
}

