#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<sys/time.h>
#include "cblas.h"

int main(int argc, char * argv[])
{
   enum CBLAS_ORDER order;
   enum CBLAS_TRANSPOSE transa;

   float *a, *x, *y;
   float alpha, beta;
   int  lda, incx, incy, i;
  
 //  order = CblasRowMajor;
   order = CblasColMajor;
   transa = CblasNoTrans;
  int n=atoi(argv[1]);
  int m=atoi(argv[2]);
  printf("m: %d n: %d \n",m,n);
  // printf("enter the value of m ,n : ");
  // scanf ("%d%d",&m,&n);

   double time_spent=0.0;
   struct timespec begin, end;


   lda = m; 
   incx = 1;
   incy = 1;
   alpha = 1;
   beta = 0;

   a = (float *)malloc(sizeof(float)*m*n);
   x = (float *)malloc(sizeof(float)*n);
   y = (float *)malloc(sizeof(float)*n);



   for (i = 0; i < (m*n); i++) {
        a[i] = (float)(2);
    }

    for (i = 0; i < n; i++) {
        x[i] = (float)(1);
    }

    clock_gettime(CLOCK_REALTIME, &begin);
    cblas_sgemv( order, transa, m, n, alpha, a, lda, x, incx, beta,
                y, incy );
    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf msec\n", 1000*elapsed);
 
/*   for( i = 0; i < m; i++ )
      printf(" %.2f ", y[i]);
   printf("\n");
*/
   free(a);
   free(x);
   free(y);
   return 0;
}
  
