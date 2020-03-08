#include "algo.h"
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

std::vector<std::vector<int>> shortest_path_all(const std::vector<std::vector<edge>>& graph) {
    int size = graph.size();

    vector< vector<int> > final_matrix(size, vector<int>(size, INF));

    for (int i = 0; i < size; ++i) {
        for (auto& it : graph[i]) {
            final_matrix[i][it.first] = it.second;
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                final_matrix[i][j] = 0;
            }
        }
    }

    for (int k = 0; k < size; ++k) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (final_matrix[i][j] > final_matrix[i][k] + final_matrix[k][j]) {
                    final_matrix[i][j] = final_matrix[i][k] + final_matrix[k][j];
                }
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (final_matrix[i][j] == INF) {
                final_matrix[i][j] = -1;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        if (final_matrix[i][i] < 0) {
            return vector<vector<int>>(size, vector<int>(size, -1));
        }
    }

    return final_matrix;
}
