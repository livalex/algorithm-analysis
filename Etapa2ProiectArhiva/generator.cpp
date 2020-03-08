#include <bits/stdc++.h>
using namespace std;

#define MAX_N 15
#define MAX_E 15
#define MAX_COST 100

void graphCreator(string pathFileInput) {
    ofstream outFile(pathFileInput);
    srand(time(NULL));
    int n;
    int m;

    n = 2 + rand() % MAX_N;
    m = 3 + rand() % MAX_E;

    outFile << n << ' ' << m << "\n";

    int j;
    for (j = 1; j <= m; ++j) {
        int start;
        int finish;
        int cost;

        start = rand() % n + 1;
        finish = rand() % m + 1;
        cost = rand() % MAX_COST;
        outFile << start << ' ' << finish << ' ' << cost << "\n";
    }
    outFile.close();
}

int main() {
    for (int j = 0; j < 10; ++j) {
        string inFile;
        inFile = "in/test" + to_string(j) + ".in";
        graphCreator(inFile);
    }

    return 0;
}