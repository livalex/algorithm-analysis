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

std::vector<std::vector<int>> shortest_path_all(const std::vector<std::vector<edge>>& graph) {
    int V = graph.size(); // Number of vertices in graph
    int E = 0;

    for (int i = 0; i < V; ++i) {
        for (auto& it : graph[i]) {
            ++E;
        }
    }

    vector< vector<int> > final_matrix(V + 1, vector<int>(V + 1, INF));

    for (int k = 0; k < V; ++k) {
        // Initialize distance of all vertices as 0.
        int dist[V];
        for (int i = 0; i < V; ++i) {
            dist[i] = INF;
        }

        // initialize distance of source as 0 
        dist[k] = 0;

        // Relax all edges |V| - 1 times. A simple 
        // shortest path from src to any other 
        // vertex can have at-most |V| - 1 edges 
        for (int i = 0; i < V - 1; ++i) {
            for (int j = 0; j < V; ++j) {
                for (auto& it : graph[j]) {
                    if (dist[j] + it.second < dist[it.first]) {
                        dist[it.first] = dist[j] + it.second;
                    }
                }   
            }
        }

        // check for negative-weight cycles. 
        // The above step guarantees shortest 
        // distances if graph doesn't contain 
        // negative weight cycle.  If we get a 
        // shorter path, then there is a cycle.
        for (int i = 0; i < V; ++i) {
            for (auto& it : graph[i]) {
                int x = i;
                int y = it.first;
                int weight = it.second;

                if (dist[x] != INF && dist[x] + weight < dist[y]) {
                    cout << "Graph contains negative weight cycle" << "\n";
                }
            }
        }

        for (int i = 0; i < V; ++i) {
            final_matrix[k][i] = dist[i];
        }

    }

    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (final_matrix[i][j] == INF) {
                final_matrix[i][j] = -1;
            }
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

    scanning(n);
    scanning(m);

    vector< vector<edge> > neig_list(n);
    vector< vector<int> > result_matrix(n, vector<int>(n, -1));

    for (int i = 1; i <= m; ++i) {
        int source, destination, cost;
        scanning(source);
        scanning(destination);
        scanning(cost);

        neig_list[source - 1].push_back(make_pair(destination - 1, cost));
    }

    result_matrix = shortest_path_all(neig_list);

    for (int i = 0; i < n; ++i, putchar('\n')) {
        for (int j = 0; j < n; ++j) {
            if (result_matrix[i][j] == -1) {
                putchar('i'), putchar('n'), putchar('f'), putchar(' ');
            } else {
                printing(result_matrix[i][j]);
            }
        }
    }
    

    fclose(fin);
    fclose(fout);

    return 0;
}