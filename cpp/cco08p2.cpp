// ./cco-08-p2-king--weber.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MM = 1e5 + 1, MN = MM*4;
int Q, M;

int dsu[MN*2], A[MM], B[MM], W[MM];
int rt(int x) { return dsu[x] == x ? x : dsu[x] = rt(dsu[x]); }
void unite(int x, int y) { dsu[rt(x)] = rt(y); }
bool con(int x, int y) { return rt(x) == rt(y); }

int N = 0;
int get(string n) {
    static map<string, int> mp;
    if (!mp.count(n)) return mp[n] = N++;
    return mp[n];
}

int QA[MM], QB[MM];

vector<pair<int, bool>> g[MN];
int clr[MN];
bool bad = false;
void dfs(int c, int cclr) {
    if (clr[c] == -1) clr[c] = cclr;
    else {
        bad |= clr[c] != cclr;
        return;
    }
    clr[c] = cclr;
    for (auto to : g[c])
        dfs(to.first, cclr ^ to.second);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> Q;
    for (auto i = 0; i < M; i++) {
        string _a, _b, dir; cin >> _a >> _b >> dir;
        A[i] = get(_a);
        B[i] = get(_b);
        W[i] = dir == "intersect";
    }
    for (auto i = 0; i < Q; i++) {
        string _a, _b; cin >> _a >> _b;
        QA[i] = get(_a); QB[i] = get(_b);
    }
    iota(dsu, dsu+MN*2, 0);
    for (auto i = 0; i < M; i++) {
        g[A[i]].emplace_back(B[i], W[i]);
        g[B[i]].emplace_back(A[i], W[i]);
        if (W[i]) {
            unite(A[i], B[i]+N);
            unite(A[i]+N, B[i]);
        }
        else {
            unite(A[i], B[i]);
            unite(A[i]+N, B[i]+N);
        }
    }
    memset(clr, -1, sizeof clr);
    for (auto i = 0; i < N; i++)
        if (clr[i] == -1)
            dfs(i, 0);
    if (bad) {
        cout << "Waterloo\n";
        return 0;
    }
    for (auto i = 0; i < Q; i++) {
        int a = QA[i], b = QB[i];
        if (con(a, b)) cout << "parallel\n";
        else if (con(a, b+N)) cout << "intersect\n";
        else cout << "unknown\n";
    }

    return 0;
}