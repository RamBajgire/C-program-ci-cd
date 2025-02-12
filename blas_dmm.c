#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main()
{
    double *A, *B, *C;
    int m, n, k, i, j;
    double alpha, beta;
    printf("enter the value of m ,k,n : ");
    scanf ("%d %d %d",&m,&k,&n);
    alpha = 1.0; beta = 0.0;
    double time_spent=0.0;
    struct timespec begin, end;

//	openblas_set_num_threads(48);    


    A = (double *)malloc( m*k*sizeof( double ));
    B = (double *)malloc( k*n*sizeof( double ) );
    C = (double *)malloc( m*n*sizeof( double ) );


    for (i = 0; i < (m*k); i++) {
        A[i] = (double)(1);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (double)(2);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    clock_gettime(CLOCK_REALTIME, &begin);
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                m, n, k, alpha, A, k, B, n, beta, C, n);
    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf sec\n", elapsed);
/*
    for (i= 0; i< m; i++)
    {
        for (j= 0; j< n; j++)
        {
            printf("%lf\t",C[j+i*n]);
        }
        printf("\n");
    }
*/
}
