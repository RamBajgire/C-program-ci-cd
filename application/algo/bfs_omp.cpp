#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Graph {
    int numVertices;
    vector<vector<int>> adjacencyList;
};

// Parallel Breadth-First Search (BFS)
void parallelBFS(const Graph& graph, int startVertex) {
    vector<bool> visited(graph.numVertices, false);
    queue<int> bfsQueue;
    
    visited[startVertex] = true;
    bfsQueue.push(startVertex);

        while (!bfsQueue.empty()) {
            int levelSize = bfsQueue.size();
            #pragma omp parallel for
            for (int i = 0; i < levelSize; ++i) {
                int currentVertex;
                
                #pragma omp critical   
                {
                    if (!bfsQueue.empty()) {
                        currentVertex = bfsQueue.front();
                        bfsQueue.pop();
                        // cout << currentVertex << " ";
                    }
                }

                for (int neighbor : graph.adjacencyList[currentVertex]) {
                    if (!visited[neighbor]) {
                        #pragma omp critical
                        {
                            if (!visited[neighbor]) {  
                                visited[neighbor] = true;
                                bfsQueue.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }

int main() {
    Graph graph;
    int n, edges;
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> edges;
    cout<<"Vertices: "<<n<<" Edges: "<<edges<<endl;
    graph.numVertices = n;
    graph.adjacencyList.resize(n);

    srand(time(NULL));
    // cout << "Generating a random graph...\n";
    for (int i = 0; i < edges; i++) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v) {
            graph.adjacencyList[u].push_back(v);
            graph.adjacencyList[v].push_back(u);
        }
    }

//    cout << "BFS Traversal (starting from node 0):\n";

    double time_spent = 0.0;
    struct timespec begin, end;
    clock_gettime(CLOCK_REALTIME, &begin);

    parallelBFS(graph, 0);

    clock_gettime(CLOCK_REALTIME, &end);
    long seconds = end.tv_sec - begin.tv_sec;
    long nanoseconds = end.tv_nsec - begin.tv_nsec;
    double elapsed = seconds + nanoseconds * 1e-9;
    printf("\nTime measured: %lf sec\n", elapsed);

    return 0;
}
