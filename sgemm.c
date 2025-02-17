#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main()
{
    float *A, *B, *C;
    int m, n, k, i, j;
    float alpha, beta;
    printf("enter the value of m ,k,n : ");
    scanf ("%d %d %d",&m,&k,&n);
    alpha = 1.0; beta = 0.0;
    double time_spent=0.0;
    struct timespec begin, end;


    A = (float *)malloc( m*k*sizeof( float ));
    B = (float *)malloc( k*n*sizeof( float ) );
    C = (float *)malloc( m*n*sizeof( float ) );


    for (i = 0; i < (m*k); i++) {
        A[i] = (float)(1);
    }

    for (i = 0; i < (k*n); i++) {
        B[i] = (float)(2);
    }

    for (i = 0; i < (m*n); i++) {
        C[i] = 0.0;
    }

    clock_gettime(CLOCK_REALTIME, &begin);
    cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
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

