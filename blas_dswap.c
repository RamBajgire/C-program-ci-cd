#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main(int argc, char* argv[])
{
   double  *x, *y;
   int incx, incy,i;
//   printf("enter the number of elements in vector: ");
 //  scanf("%d",&n);
   incx = 1;
   incy = 1;
   double time_spent=0.0;
   struct timespec begin, end;
  
   if(argc<1){
            printf("You did not provide any argument\n");
            exit(1);
    }

    int n=atoi(argv[1]);
    printf(" n = %d\n",n);

   x = (double *)malloc(sizeof(double)*n);
   y = (double *)malloc(sizeof(double)*n);
   
   for (i = 0; i < n; i++) {
        x[i] = (double)(1);
        y[i] = (double)(2);
    }
  /*  printf("before swaping:\n");
    for( i = 0; i < n; i++ )
      printf("%.2lf\t %.2lf\n",x[i],y[i]);
*/
    clock_gettime(CLOCK_REALTIME, &begin);
    cblas_dswap(n , x , incx , y , incy);
    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    
  /*  printf("after  swaping:\n");
    for( i = 0; i < n; i++ )
      printf("%.2lf\t %.2lf\n",x[i],y[i]);
*/
    printf("Time measured: %lf msec\n", elapsed*1000);
}
