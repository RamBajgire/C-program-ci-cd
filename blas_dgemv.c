#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<sys/time.h>
#include "cblas.h"

int main(int argc, char* argv[])
{
   enum CBLAS_ORDER order;
   enum CBLAS_TRANSPOSE transa;

   double *a, *x, *y;
   double alpha, beta;
   int lda, incx, incy, i;
    if(argc<1){
            printf("You did not provide any argument\n");
            exit(1);
    }

    int m=atoi(argv[1]);
    int n=atoi(argv[2]);
    printf("m: %d n: %d\n",m,n);


//	 openblas_set_num_threads(12);

   order = CblasColMajor;
   transa = CblasNoTrans;
   //printf("enter the value of m ,n : ");
   //scanf ("%d%d",&m,&n);

   double time_spent=0.0;
   struct timespec begin, end;
 //  openblas_set_num_threads(12);

   lda = m; 
   incx = 1;
   incy = 1;
   alpha = 1;
   beta = 0;

   a = (double *)malloc(sizeof(double)*m*n);
   x = (double *)malloc(sizeof(double)*n);
   y = (double *)malloc(sizeof(double)*n);



   for (i = 0; i < (m*n); i++) {
        a[i] = (double)(1);
    }

    for (i = 0; i < n; i++) {
        x[i] = (double)(2);
    }

    clock_gettime(CLOCK_REALTIME, &begin);
    cblas_dgemv( order, transa, m, n, alpha, a, lda, x, incx, beta,
                y, incy );
    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf msec\n", 1000*elapsed);
    /*for(int i=0; i<m; ++i){
	    printf("%.2f ",y[i]);
    }
    printf("\n");*/
/* 
   for( i = 0; i < n; i++ )
      printf(" y = %f\n", i, y[i]);*/
//   printf("m: %d n: %d\n",m,n);

   free(a);
   free(x);
   free(y);
   return 1;
}
  
