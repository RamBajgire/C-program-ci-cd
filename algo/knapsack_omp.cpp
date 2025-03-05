#include <iostream>
#include <omp.h>
#include <ctime>
#include <vector>
#include <algorithm> 
using namespace std;

int Knapsack(vector<int>& v, vector<int>& w, int n, int W) {
    vector<vector<int>> V(2, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; i++) {
        int currRow = i % 2;
        int prevRow = (i - 1) % 2;

        #pragma omp parallel for schedule(dynamic, 128)
        for (int j = 1; j <= W; j++) {
            if (w[i - 1] <= j) {
                V[currRow][j] = max(V[prevRow][j], v[i - 1] + V[prevRow][j - w[i - 1]]);
            } else {
                V[currRow][j] = V[prevRow][j];
            }
        }
    }

    return V[n % 2][W];
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    cout << "Enter the maximum weight capacity (W): ";
    cin >> W;
    cout << "Number of items: " << n<<endl;
    cout << "Knapsack capacity: " << W << endl;
    vector<int> v(n), w(n);
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        v[i] = rand() % 100 + 1; 
        w[i] = rand() % 20 + 1;  
    }

    // cout << "Values: ";
    // for (auto val : v) cout << val << " ";
    // cout << endl;

    // cout << "Weights: ";
    // for (auto weight : w) cout << weight << " ";
    // cout << endl;

    double time_spent = 0.0;
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    int maxValue = Knapsack(v, w, n, W);

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;


    cout << "Maximum value in the knapsack: " << maxValue << endl;
    printf("Time measured: %lf sec\n", elapsed);

    return 0;
}
