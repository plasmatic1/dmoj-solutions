#include <bits/stdc++.h>
using namespace std;

const int MN = 1501;
int N, 
    req[MN];

void initialize(int n) {
    N = n;
    iota(req, req + N, 0);
}
int hasEdge(int u, int v) {
    // hi to low
    if (u < v) swap(u, v);
    req[u]--;
    return !req[u];
}