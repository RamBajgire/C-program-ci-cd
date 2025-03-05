#include <iostream>
#include <omp.h>
#include <ctime>
#include <vector>
using namespace std;

int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }

    swap(vec[i + 1], vec[high]);

    return (i + 1);
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        #pragma omp task shared(vec) firstprivate(pi,low)
        {
            quickSort(vec, low, pi - 1);
        }
        #pragma omp task shared(vec) firstprivate(pi,high)
        {
            quickSort(vec, pi + 1, high);
        }
        #pragma omp taskwait
    }
}

int main() {
    int n;
    cout<<"enter the size of array to be sorted "<<endl;
    cin>>n;
    cout<<"Size: "<<n<<endl;
    vector<int> vec(n);
    srand(time(NULL));
    for ( int i = 0; i < n; ++i )
    {
	    vec[i] = rand()%100;
    }

    // cout<<" Before Sorting "<<endl;  
    // for (auto i : vec) {
    //     cout << i << " ";
    // }
    // cout<<endl;
    double time_spent=0.0;
    struct timespec begin, end;
 
    clock_gettime(CLOCK_REALTIME, &begin);
    
    #pragma omp parallel
    {
        #pragma omp single 
        quickSort(vec, 0, n - 1);
    }
    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf sec\n", elapsed);
    // cout <<" After Sorting "<<endl;
    // for (auto i : vec) {
    //     cout << i << " ";
    // }
    // cout<<endl;
    return 0;
}
