// ./mock-ccc-21-s4-infinite-molecule.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*
 * 0..4*N-1 -> regular nodes (4 orientations)
 * pos in, neg in
 */

const int MN = 4e4 + 1, MG = MN*4 + 26*2 + 10;
int N,
    A[MN][4];

int getid(int q) {
    int add = (q < 0) * 26; q = abs(q) - 1;
    return 4*N + q + add;
}

vector<int> g[MG];
int indeg[MG];
queue<int> q;

void addedge(int a, int b) {
    g[a].push_back(b);
    indeg[b]++;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int nc = 4*N + 2*26;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 4; j++)
            cin >> A[i][j];
        for (int j = 0; j < 4; j++) {
            if (A[i][j] == 0) continue;
            int n = j*N + i;
            // incoming
            addedge(getid(-A[i][j]), n);
            // outgoing
            for (int k = 0; k < 4; k++) {
                if (A[i][k] == 0) continue;
                if (j != k)
                    addedge(n, getid(A[i][k]));
            }
        }
    }

    // check if a cycle exists owo
    for (int i = 0; i < nc; i++)
        if (indeg[i] == 0)
            q.push(i);
    int found = 0;
    while (!q.empty()) {
        int c = q.front(); q.pop(); 
        found++;
        for (auto to : g[c])
            if (--indeg[to] == 0)
                q.push(to);
    }
    
    cout << (found < nc) << '\n';

    return 0;
}