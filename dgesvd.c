#include <stdlib.h>
#include <stdio.h>
#include <lapacke.h>
#include <time.h>

#define min(a,b) ((a)>(b)?(b):(a))

/* Auxiliary routines prototypes */
extern void print_matrix( char* desc, int m, int n, double* a, int lda );


/* Main program */
int main(int argc, char **argv) {
        /* Locals */
        
        int N,M;
   //     printf("Enter the Size of Matrix : ");
    //    scanf("%d",&M);
        M=atoi(argv[1]);
        N=M;
        
        int LDA=N,LDU=M,LDVT=N;
        int m = M, n = N, lda = LDA, ldu = LDU, ldvt = LDVT, info;
        double superb[min(M,N)-1];
        /* Local arrays */
        double s[N], u[LDU*M], vt[LDVT*N];
        double *a;
        	a = (double *)malloc(m*lda*sizeof(double)) ;
		if (a==NULL){ printf("error of memory allocation\n"); exit(0); }
   int i,j;
   for( i = 0; i < n; i++ ) {
                for( j = 0; j < n; j++ ) a[i*N+j] = ((double) rand()) / ((double) RAND_MAX) ;
		}
        
       /* double a[LDA*M] = {
            8.79,  9.93,  9.83, 5.45,  3.16,
            6.11,  6.91,  5.04, -0.27,  7.98,
           -9.15, -7.93,  4.86, 4.85,  3.01,
            9.57,  1.64,  8.83, 0.74,  5.80,
           -3.49,  4.02,  9.80, 10.00,  4.27,
            9.84,  0.15, -8.99, -6.02, -5.31
        };*/
        
        
        /* Executable statements */
        printf( "LAPACKE_dgesvd (row-major, high-level) Example Program Results for %d\n",M );
        /* Compute SVD */
        
        double time_spent=0.0;
         struct timespec begin, end;

        clock_gettime(CLOCK_REALTIME, &begin);
        
        info = LAPACKE_dgesvd( LAPACK_ROW_MAJOR, 'A', 'A', m, n, a, lda,
                        s, u, ldu, vt, ldvt, superb );
                        
        clock_gettime(CLOCK_REALTIME, &end);
        long seconds = end.tv_sec - begin.tv_sec;
        long nanoseconds = end.tv_nsec - begin.tv_nsec;
        double elapsed = seconds + nanoseconds*1e-9;
        printf("\nTime measured: %.3f seconds.\n", elapsed);
                        
        /* Check for convergence */
        if( info > 0 ) {
                printf( "The algorithm computing SVD failed to converge.\n" );
                exit( 1 );
        }
        /* Print singular values */
    //    print_matrix( "Singular values", 1, n, s, 1 );
        /* Print left singular vectors */
    //    print_matrix( "Left singular vectors (stored columnwise)", m, n, u, ldu );
        /* Print right singular vectors */
    //    print_matrix( "Right singular vectors (stored rowwise)", n, n, vt, ldvt );
        exit( 0 );
} /* End of LAPACKE_dgesvd Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, int m, int n, double* a, int lda ) {
        int i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( " %6.2f", a[i*lda+j] );
                printf( "\n" );
        }
}
