#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int value;
    int weight;
};

// Global variables to store the best solution
int best_value = 0;
vector<bool> best_solution;

// Function to solve the 0/1 Knapsack problem using Backtracking and Branch and Bound
void knapsack(int index, int current_value, int current_weight, const vector<Item>& items, int capacity, vector<bool>& solution) {
    if (index == items.size() || current_weight >= capacity) {
        if (current_value > best_value) {
            #pragma omp critical
            {
                if (current_value > best_value) {
                    best_value = current_value;
                    best_solution = solution;
                }
            }
        }
        return;
    }

    int remaining_value = 0;
    for (int i = index; i < items.size(); ++i) {
        remaining_value += items[i].value;
    }
    if (current_value + remaining_value <= best_value) {
        return;
    }

    if (current_weight + items[index].weight <= capacity) {
        solution[index] = true;
        knapsack(index + 1, current_value + items[index].value, current_weight + items[index].weight, items, capacity, solution);
    }

    solution[index] = false;
    knapsack(index + 1, current_value, current_weight, items, capacity, solution);
}

int main() {
    srand(time(NULL));
    int num_items, capacity;
    cout << "Enter the number of items: ";
    cin >> num_items;
    cout << "Enter the maximum weight capacity (W): ";
    cin >> capacity;
    cout << "Number of items: " << num_items << endl;
    cout << "Knapsack capacity: " << capacity << endl;

    vector<Item> items(num_items);
    // cout << "Generated items (value, weight):\n";
     
    for (int i = 0; i < num_items; ++i) {
        items[i].value = rand() % 100 + 1;   
        items[i].weight = rand() % 20 + 1;   
        // cout << "Item " << i + 1 << ": " << items[i].value << " " << items[i].weight << endl;
    }

    sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
        return (double)a.value / a.weight > (double)b.value / b.weight;
    });

    vector<bool> solution(num_items, false);

    double time_spent = 0.0;
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    #pragma omp parallel
    {
        #pragma omp single
        knapsack(0, 0, 0, items, capacity, solution);
    }

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;

    cout << "Best value: " << best_value << endl;
    // cout << "Selected items: ";
    // for (int i = 0; i < num_items; ++i) {
    //     if (best_solution[i]) {
    //         cout << i + 1 << " ";
    //     }
    // }
    // cout << endl;

    printf("Time measured: %lf sec\n", elapsed);
    return 0;
}
