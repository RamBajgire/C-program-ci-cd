#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <lapacke.h>

/* Auxiliary routines prototypes */
void print_matrix( char* desc, int m, int n, float* a, int lda );

/* Parameters */
//#define N 5
//#define LDA N

/* Main program */
int main(int argc, char **argv) {
        /* Locals */
        int N,LDA;
        //printf("Enter the Value of n : ");
        //scanf("%d",&N);
	//openblas_set_num_threads(1);
        N=atoi(argv[1]);
        LDA=N;
        int n = N, lda = LDA, info;
        int i,j;
        /* Local arrays */
       float w[N];
        float *a;
        	a = (float *)malloc(n*lda*sizeof(float)) ;
		if (a==NULL){ printf("error of memory allocation\n"); exit(0); }
   
   for( i = 0; i < n; i++ ) {
                for( j = 0; j < n; j++ ){
		  //   a[i*N+j] = ((float) rand()) / ((float) RAND_MAX) ;
                     if(j>=i)
                     a[i*N+j]=(float)2;
                     else
                     a[i*N+j]=(float)0;                 
		}
   }
      /*   double a[LDA*N] = {
            1.96, -6.49, -0.47, -7.20, -0.65,
            0.00,  3.80, -6.39,  1.50, -6.34,
            0.00,  0.00, 4.17, -1.51, 2.67,
            0.00,  0.00, 0.00,  5.70, 1.80,
            0.00,  0.00, 0.00,  0.00, -7.10
        };
        */
        /* Executable statements */
        printf( "LAPACKE_ssyev (row-major, high-level) Example Program Results for %d \n",N );
        /* Solve eigenproblem */
        
         double time_spent=0.0;
         struct timespec begin, end;
          clock_gettime(CLOCK_REALTIME, &begin);
        
        info = LAPACKE_ssyev( LAPACK_COL_MAJOR, 'V', 'U', n, a, lda, w );
//	info = LAPACKE_ssyev( LAPACK_COL_MAJOR, 'V', 'U', n, a, lda, w );
        
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
//	free(a);
        /* Print eigenvalues */
      // print_matrix( "Eigenvalues", 1, n, w, 1 );
        /* Print eigenvectors */
    //    print_matrix( "Eigenvectors (stored columnwise)", n, n, a, lda );
        exit( 0 );
} /* End of LAPACKE_dsyev Example */

/* Auxiliary routine: printing a matrix */
void print_matrix( char* desc, int m, int n, float* a, int lda ) {
        int i, j;
        printf( "\n %s\n", desc );
        for( i = 0; i < m; i++ ) {
                for( j = 0; j < n; j++ ) printf( " %6.2f", a[i*lda+j] );
                printf( "\n" );
        }
}
