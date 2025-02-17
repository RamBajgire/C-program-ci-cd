#include <stdlib.h>
#include <stdio.h>
#include <lapacke.h>
#include <time.h>

#define min(a,b) ((a)>(b)?(b):(a))

/* Auxiliary routines prototypes */
extern void print_matrix( char* desc, int m, int n, float* a, int lda );

/* Parameters 
#define M 6
#define N 5
#define LDA N
#define LDU M
#define LDVT N*/

/* Main program */
int main(int argc, char** argv) {
        /* Locals */
        int N,M;
//        printf("Enter the Value of m (rows) : ");
  //      scanf("%d",&M);
      /*  printf("Enter the Value of n (columns) : ");
        scanf("%d",&N);*/
       // printf("Enter the Size of Matrix : ");
       // scanf("%d",&M);
       M=atoi(argv[1]);
        N=M;
        int LDA=N,LDU=M,LDVT=N;
        
        int m = M, n = N, lda = LDA, ldu = LDU, ldvt = LDVT, info;
        float superb[min(M,N)-1];
        /* Local arrays */
        float s[N], u[LDU*M], vt[LDVT*N];
         float *a;
        	a = (float *)malloc(m*lda*sizeof(float)) ;
		    if (a==NULL){ printf("error of memory allocation\n"); exit(0); }
         int i,j;
         for( i = 0; i < n; i++ ) {
                for( j = 0; j < n; j++ ) a[i*N+j] = ((float) rand()) / ((float) RAND_MAX) ;}       
       /* float a[LDA*M] = {
            8.79f,  9.93f,  9.83f, 5.45f,  3.16f,
            6.11f,  6.91f,  5.04f, -0.27f,  7.98f,
           -9.15f, -7.93f,  4.86f, 4.85f,  3.01f,
            9.57f,  1.64f,  8.83f, 0.74f,  5.80f,
           -3.49f,  4.02f,  9.80f, 10.00f,  4.27f,
            9.84f,  0.15f, -8.99f, -6.02f, -5.31f
        };*/
        /* Executable statements */
        printf( "LAPACKE_sgesvd (row-major, high-level) Example Program Results for %d\n",M );
        /* Compute SVD */
        double time_spent=0.0;
         struct timespec begin, end;

        clock_gettime(CLOCK_REALTIME, &begin);
        
        info = LAPACKE_sgesvd( LAPACK_ROW_MAJOR, 'A', 'A', m, n, a, lda,
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
} /* End of LAPACKE_sgesvd Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, int m, int n, float* a, int lda ) {
        int i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( " %6.2f", a[i*lda+j] );
                printf( "\n" );
        }
}
