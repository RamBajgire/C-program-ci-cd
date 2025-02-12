
#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main(void)
{
   float  *x, *y;
   int n ,  incx, incy,i;
   printf("enter the number of elements in vector: ");
   scanf("%d",&n);
   incx = 1;
   incy = 1;
   double time_spent=0.0;
   struct timespec begin, end;

   x = (float *)malloc(sizeof(float)*n);
   y = (float *)malloc(sizeof(float)*n);
   
   for (i = 0; i < n; i++) {
        x[i] = (float)(1);
        y[i] = (float)(2);
    }
/*
    for( i = 0; i < n; i++ )
      printf("%.2lf\t %.2lf",x[i],y[i]);
*/
    clock_gettime(CLOCK_REALTIME, &begin);
    double result = cblas_sdot(n , x , incx , y , incy);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("result = %lf\n",result);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf sec\n", elapsed);

}

