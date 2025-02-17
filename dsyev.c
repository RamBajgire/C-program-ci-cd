#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <lapacke.h>

/* Auxiliary routines prototypes */
extern void print_matrix( char* desc, int m, int n, double* a, int lda );


/* Main program */
int main(int argc, char** argv) {
        /* Locals */
        int N,LDA;
    //    printf("Enter the Value of n : ");
      //  scanf("%d",&N);
       N=atoi(argv[1]);
        LDA=N;
        int n = N, lda = LDA, info;
        int i,j;
        /* Local arrays */
       double w[N];
        double *a;
        	a = (double *)malloc(n*lda*sizeof(double)) ;
		if (a==NULL){ printf("error of memory allocation\n"); exit(0); }
   
   for( i = 0; i < n; i++ ) {
                for( j = 0; j < n; j++ ) a[i*N+j] = ((double) rand()) / ((double) RAND_MAX) ;
		}
        /* Executable statements */
        printf( "LAPACKE_dsyev (row-major, high-level) Example Program Results for %d \n",N );
        /* Solve eigenproblem */
        
         double time_spent=0.0;
         struct timespec begin, end;
          clock_gettime(CLOCK_REALTIME, &begin);
        
        info = LAPACKE_dsyev( LAPACK_COL_MAJOR, 'V', 'U', n, a, lda, w );
        
        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        printf("\nTime measured: %.3f seconds.\n", elapsed);
        /* Check for convergence */
        if( info > 0 ) {
                printf( "The algorithm failed to compute eigenvalues.\n" );
                exit( 1 );
        }
        /* Print eigenvalues */
    //    print_matrix( "Eigenvalues", 1, n, w, 1 );
        /* Print eigenvectors */
    //    print_matrix( "Eigenvectors (stored columnwise)", n, n, a, lda );
        exit( 0 );
} /* End of LAPACKE_dsyev Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, int m, int n, double* a, int lda ) {
        int i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( " %6.2f", a[i*lda+j] );
                printf( "\n" );
        }
}
