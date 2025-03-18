#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 26214400
#define EPP 3276800

int sbuffer[EPP], rbuffer[SIZE];

int main(int argc, char *argv[]) {
    int mpi_err, mpi_rank;
    double start_time, end_time;

    mpi_err = MPI_Init(&argc, &argv);
    mpi_err = MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

    srand(time(NULL) + mpi_rank);
    for (int i = 0; i < EPP; i++) {
        sbuffer[i] = (mpi_rank + rand()) % 10;
    }

    MPI_Barrier(MPI_COMM_WORLD); // Synchronize before timing
    start_time = MPI_Wtime();
    mpi_err = MPI_Gather(sbuffer, EPP, MPI_INT, rbuffer, EPP, MPI_INT, 0, MPI_COMM_WORLD);
    end_time = MPI_Wtime();

    if (mpi_rank == 0) {
        printf("Time taken for MPI_Gather: %f seconds\n", end_time - start_time);
    }

    mpi_err = MPI_Finalize();
    return 0;
}

