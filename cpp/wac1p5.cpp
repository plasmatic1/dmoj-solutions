// ./wesleys-anger-contest-1-problem-5-rule-of-four.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 25001;
int N, M, K;

// 2SAT
int ord[MN*2], low[MN*2], comp[MN*2], ccomp = 0, cord = 0;
bool instk[MN*2];
vector<int> g[MN*2], g2[MN*2], stk;

void addEdge(int a, int b) {
    if (a < 0) a = N-a;
    if (b < 0) b = N-b;
    g[a].push_back(b);
}
void tarjan(int c) {
    ord[c] = low[c] = ++cord;
    instk[c] = true; stk.push_back(c);
    for (auto to : g[c]) {
        if (!ord[to]) {
            tarjan(to);
            low[c] = min(low[c], low[to]);
        }
        else if (instk[to])
            low[c] = min(low[c], ord[to]);
    }

    if (low[c] == ord[c]) {
        int u, cno = ++ccomp;
        do {
            u = stk.back(); stk.pop_back(); instk[u] = false;
            comp[u] = cno;
        } while (u != c);
    }
}

bitset<MN*2> dp[MN*2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    for (auto i = 0; i < K; i++) {
        int x; cin >> x;
        addEdge(-x, x); // contrapositive is the same
    }
    for (auto i = 0; i < M; i++) {
        string t; int a, b; cin >> t >> a >> b;
        if (t == "FRIENDS") {
            addEdge(a, b); // a <=> b
            addEdge(b, a);
            addEdge(-a, -b); // !a <=> !b
            addEdge(-b, -a);
        }
        else if (t == "ENEMIES") {
            addEdge(a, -b); // not both
            addEdge(b, -a);
        }
        else if (t == "PARTNERS") {
            addEdge(-a, b); // at least one
            addEdge(-b, a);
            addEdge(a, -b); // at most one
            addEdge(b, -a);
        }
        else if (t == "GROUP") {
            addEdge(-a, b); // at least one
            addEdge(-b, a);
        }
    }

    // run 2SAT
    for (auto i = 1; i <= 2*N; i++)
        if (!ord[i])
            tarjan(i);
    for (auto i = 1; i <= N; i++) {
        if (comp[i] == comp[i+N]) {
            cout << "NO\n";
            return 0;
        }
    }
    // build ADJ
    unordered_map<int, vector<int>> comps;
    for (auto i = 1; i <= 2*N; i++) {
        comps[comp[i]].push_back(i);
        for (auto to : g[i]) {
            if (comp[i] != comp[to]) {
                g2[comp[i]].push_back(comp[to]);
            }
        }
    }
    for (auto i = 1; i <= ccomp; i++) {
        sort(g2[i].begin(), g2[i].end());
        g2[i].resize(unique(g2[i].begin(), g2[i].end()) - g2[i].begin());
    }
    // reverse topo order (remember tarjan gives in rev. topological order)
    // run DP
    for (auto i = 1; i <= ccomp; i++) {
        for (auto x : comps[i])
            dp[i][x] = true;
        for (auto to : g2[i])
            dp[i] |= dp[to];
    }

    // oh no !!!
    cout << "YES\n";
    for (auto i = 1; i <= N; i++) {
        // a OR a -> !a => a
        // !a or !a -> a => !a
        bool ok1 = !dp[comp[i]][i+N], ok0 = !dp[comp[i+N]][i];

        if (ok1 && ok0) cout << "?";
        else if (ok1) cout << "1";
        else cout << "0";
    }
    cout << '\n';

    return 0;
}