#include <stdio.h>
#include <stdlib.h>
#include<sys/time.h>
#include<time.h>
#include "cblas.h"

int main(int argc, char* argv[])
{
    double  *x;
    int  incx,i;
    incx = 1;
    double alpha = 4.0;
    if(argc<=1){
            printf("You did not provide any argument\n");
            exit(1);
    }

    int n=atoi(argv[1]);
    printf(" n = %d\n",n);

    //printf("enter the number of elements in vector: ");
    //scanf("%d",&n);
    double time_spent=0.0;
    struct timespec begin, end;

    x = (double *)malloc(sizeof(double)*n);

    for (i = 0; i < n; i++) {
        x[i] = (double)(2);
        
    }
    clock_gettime(CLOCK_REALTIME, &begin);
    cblas_dscal(n , alpha, x , incx );
    clock_gettime(CLOCK_REALTIME, &end);

    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf msec\n",1000* elapsed);

    // for( i = 0; i < n; i++ )
     // printf("%.2lf\n" ,x[i]);
}
