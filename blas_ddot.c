#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main(void)
{
   double  *x, *y;
   int n ,  incx, incy,i;
   printf("enter the number of elements in vector: ");
   scanf("%d",&n);
   incx = 1;
   incy = 1;
   double time_spent=0.0;
   struct timespec begin, end;

   x = (double *)malloc(sizeof(double)*n);
   y = (double *)malloc(sizeof(double)*n);
   
   for (i = 0; i < n; i++) {
        x[i] = (double)(1);
        y[i] = (double)(2);
    }
/*
    for( i = 0; i < n; i++ )
      printf("%.2lf\t %.2lf",x[i],y[i]);
*/
    clock_gettime(CLOCK_REALTIME, &begin);
    double result = cblas_ddot(n , x , incx , y , incy);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("result = %lf\n",result);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf sec\n", elapsed);

}
