#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main(int argc, char* argv[])
{
   double  *x ;
   int  incx,i;
  // printf("enter the number of elements in vector: ");
  // scanf("%d",&n);
   incx = 1;
   double time_spent=0.0;
   struct timespec begin, end;
  if(argc<=1){
            printf("You did not provide any argument\n");
            exit(1);
    }
    int n=atoi(argv[1]);
    printf("n: %d\n",n);


   x = (double *)malloc(sizeof(double)*n);

   for (i = 0; i < n; i++) {
        x[i] = (double)(i+1);     
    }

    clock_gettime(CLOCK_REALTIME, &begin);
    double length = cblas_dnrm2(n , x , incx );
    clock_gettime(CLOCK_REALTIME, &end);

   // printf(" euclidian length = %lf\n",length);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf sec\n", elapsed);
}
