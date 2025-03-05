#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <omp.h>

using namespace std;

 int N_NODES = 500;     
 int N_ELEMENTS = 1000; 

struct Node {
    double x, y;
};

struct Element {
    int n1, n2, n3; 
};


void generateMesh(vector<Node>& nodes, vector<Element>& elements) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
 
    for (int i = 0; i < N_NODES; ++i) {
        nodes[i] = {dist(gen), dist(gen)};
    }

    for (int i = 0; i < N_ELEMENTS; ++i) {
        elements[i] = {rand() % N_NODES, rand() % N_NODES, rand() % N_NODES};
    }
}

void solveLaplace(const vector<Node>& nodes, const vector<Element>& elements, vector<double>& solution) {
    vector<double> rhs(N_NODES, 1.0); 
    vector<double> new_solution(N_NODES, 0.0);

    int iterations = 100; 

    #pragma omp parallel
    {
        for (int iter = 0; iter < iterations; ++iter) {
            #pragma omp for
            for (size_t i = 0; i < N_NODES; ++i) {
                double sum = 0.0;
                int count = 0;
                for (const auto& elem : elements) {
                    if (elem.n1 == i || elem.n2 == i || elem.n3 == i) {
                        sum += rhs[i];
                        count++;
                    }
                }
                if (count > 0) new_solution[i] = sum / count;
            }
            #pragma omp single
            solution.swap(new_solution);
        }
    }
}

int main(int argc, char** argv) {

    // int N_NODES = 500;
        N_NODES = atoi(argv[1]);
    // int N_ELEMENTS = 1000;
        N_ELEMENTS = atoi(argv[2]);
    cout << "Generating unstructured mesh...for N_NODES = "<<N_NODES<<" ELEMENTS = "<<N_ELEMENTS << endl;

    vector<Node> nodes(N_NODES);
    vector<Element> elements(N_ELEMENTS);
    generateMesh(nodes, elements);

    cout << "Solving Laplace equation on unstructured grid..." << endl;
    vector<double> solution(N_NODES, 0.0);

    double time_spent=0.0;
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);

    solveLaplace(nodes, elements, solution);

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds*1e-9;
    printf("Time measured: %lf sec\n", elapsed);

    return 0;
}
