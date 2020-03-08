#include "algo.h"
#include <bits/stdc++.h>

#define INF 0x3f3f3f3f

using namespace std;

// A utility function to find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int minDistance(int dist[], bool sptSet[], int size) {
    int min = INF;
    int min_index = 0;

    for (int v = 0; v < size; ++v) {
        if (sptSet[v] == false && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

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

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (final_matrix[i][j] < 0) {
                return vector<vector<int>>(size, vector<int>(size, -1));
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        // The output array.  dist[i] will hold the shortest 
        // distance from src to i 
        int dist[size];

        // sptSet[i] will be true if vertex i is included in shortest 
        // path tree or shortest distance from src to i is finalized 
        bool sptSet[size];

        // Initialize all distances as INFINITE and stpSet[] as false 
        for (int j = 0; j < size; ++j) {
            dist[j] = INF;
            sptSet[j] = false;
        }

         // Distance of source vertex from itself is always 0 
        dist[i] = 0;

        // Find shortest path for all vertices 
        for (int count = 0; count < size - 1; ++ count) {
            // Pick the minimum distance vertex from the set of vertices not 
            // yet processed. u is always equal to src in the first iteration. 
            int u = minDistance(dist, sptSet, size);

            // Mark the picked vertex as processed
            sptSet[u] = true;

            // Update dist value of the adjacent vertices of the picked vertex.
            for (int v = 0; v < size; ++v) {
                // Update dist[v] only if is not in sptSet, there is an edge from 
                // u to v, and total weight of path from src to  v through u is 
                // smaller than current value of dist[v] 
                if (!sptSet[v] && final_matrix[u][v] && dist[u] != INF
                && dist[u] + final_matrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + final_matrix[u][v];
                }
            }
        }
        for (int h = 0; h < size; ++h) {
            final_matrix[i][h] = dist[h];
        }
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (final_matrix[i][j] == INF) {
                final_matrix[i][j] = -1;
            }
        }
    }
    return final_matrix;
}