#include "algo.h"
#include<bits/stdc++.h>
using namespace std;

#define INF 0x3f3f3f3f

inline void scanning(int &number) {
    int character;
    bool negFlag;
    negFlag = 0;

    character = getchar_unlocked();

    if (character == '-') {
        negFlag = 1;
        character = getchar_unlocked();
    }

    number = 0;

    for (; (character > 47 && character < 58); character = getchar_unlocked()) {
        number = number * 10 + character - 48;
    }

    if (negFlag == 1) {
        number *= -1;
    }
}

inline void printing(int n) {
    char number[70];
    int contor = 0;

	do {
		number[contor++] = n % 10 + '0';
		n = n / 10;
	} while (n != 0);

    --contor;

    while (contor >= 0) {
        putchar(number[contor--]);
    }

    putchar(' ');
}

// A utility function to find the vertex with minimum distance value, from 
// the set of vertices not yet included in shortest path tree 
int minDistance(int dist[], bool sptSet[], int size) {
    int min = INF;
    int min_index;

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
    return final_matrix;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    FILE *fout = freopen("test0.out", "w", stdout);
    FILE *fin = freopen("test0.in", "r", stdin);

    if (fout == nullptr || fin == nullptr) {
       return -1;
    }

    int n, m;
    bool neg_edge = 0;

    scanning(n);
    scanning(m);

    vector< vector<edge> > neig_list(n);
    vector< vector<int> > result_matrix(n, vector<int>(n, -1));

    for (int i = 1; i <= m; ++i) {
        int source, destination, cost;
        scanning(source);
        scanning(destination);
        scanning(cost);

        if (cost < 0) {
            neg_edge = 1;
        }

        neig_list[source - 1].push_back(make_pair(destination - 1, cost));
    }

    if (neg_edge == 1) {
        cout << "The graph contains a negative cost.";
    } else {

        result_matrix = shortest_path_all(neig_list);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (result_matrix[i][j] == INF) {
                    result_matrix[i][j] = -1;
                }
            }
        }

        for (int i = 0; i < n; ++i, putchar('\n')) {
            for (int j = 0; j < n; ++j) {
                if (result_matrix[i][j] == -1) {
                    putchar('i'), putchar('n'), putchar('f'), putchar(' ');
                } else {
                    printing(result_matrix[i][j]);
                }
            }
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}