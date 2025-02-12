#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main(int argc, char* argv[])
{
   float  *x, *y,c=2.00, s=3.00;
//  float alpha=1.0;
   int incx, incy,i;
//   printf("enter the number of elements in vector: ");
//   scanf("%d",&n);
   incx = 1;
   incy = 1;
   double time_spent=0.0;
   struct timespec begin, end;
  
   if(argc<=1){
            printf("You did not provide any argument\n");
            exit(1);
    }

    int n=atoi(argv[1]);
    printf(" n = %d\n",n);

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
     cblas_srot( n, x, incx, y, incy, c, s );
    clock_gettime(CLOCK_REALTIME, &end);

   // printf("result = %lf\n",result);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;

    printf("Time measured: %lf sec\n",1000* elapsed);
/*    for( int i=0; i < n; ++i)
	    printf("%0.2f ",x[i]);
    printf("\n");
    for( int i=0; i < n; ++i)
            printf("%0.2f ",y[i]);
    printf("\n");
*/


}

