#include <chrono>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>
#include <time.h>
vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        int m = mat1.size(), n = mat2[0].size();
        vector<vector<int>> ans(m, vector<int>(n));
        auto g1 = f(mat1), g2 = f(mat2);
        for (int i = 0; i < m; ++i) {
            for (auto& [k, x] : g1[i]) {
                for (auto& [j, y] : g2[k]) {
                    ans[i][j] += x * y;
                }
            }
        }
        return ans;
    }

    vector<vector<pair<int, int>>> f(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<pair<int, int>>> g(m);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j]) {
                    g[i].emplace_back(j, mat[i][j]);
                }
            }
        }
        return g;
    }

int main(int argc,char **argv)
{
	int n = atoi (argv[1]);
	int m = atoi (argv[2]);
	int k = atoi (argv[3]);
	 vector<vector<int>> mat1(m, vector<int>(k));
    vector<vector<int>> mat2(k, vector<int>(n));

    cout << "Enter elements of matrix A (" << m << "x" << k << "):\n";
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> mat1[i][j];
        }
    }

    cout << "Enter elements of matrix B (" << k << "x" << n << "):\n";
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> mat2[i][j];
        }
    }

    auto result = multiply(mat1, mat2);

    cout << "Resultant matrix (" << m << "x" << n << "):\n";
    for (const auto& row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
       



return 0;
}
