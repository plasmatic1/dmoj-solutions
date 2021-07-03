// ./dmopc-20-contest-6-p5-jennifers-math-mystery.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

// guess: each component must have odd cycle
// also: a+b = 2*(a AND b)+(a XOR b)

const int MN = 1e5 + 1, LG = 30;
int N, M;
vector<int> g[MN];

int OR(int i, int j) {
    cout << ('?') << ' ' << (i) << ' ' << ('|') << ' ' << (j) << '\n'; cout.flush();
    int res; cin >> res; assert(res != -1);
    return res;
}
int AND(int i, int j) {
    cout << ('?') << ' ' << (i) << ' ' << ('&') << ' ' << (j) << '\n'; cout.flush();
    int res; cin >> res; assert(res != -1);
    return res;
}

ll orv[MN], andv[MN], xorv[MN], ans[MN];

int par[MN], clr[MN], init = -1;
void dfs(int c) {
    for (auto to : g[c]) {
        if (clr[to] == -1) {
            par[to] = c;
            clr[to] = clr[c] ^ 1;

            orv[to] = OR(c, to);
            andv[to] = AND(c, to);
            xorv[to] = orv[to] ^ andv[to];

            dfs(to);

        }
        else if (init == -1 && clr[to] == clr[c]) { // back edge?
            if (to == c) { // self-edge
                ans[c] = OR(c, c);
                init = c;
            }
            else { // odd cycle
                vector<int> path;
                for (auto cur = c; ; cur = par[cur]) {
                    path.pb(cur);
                    if (cur == to) break;
                }
                reverse(all(path)); // increasing depth
                ll tot = 0, osums = 0;
                int sz = SZ(path);
                for (auto i = 0; i < sz; i++) {
                    ll sum = 0;
                    if (i < sz-1)
                        sum = 2*andv[path[i+1]] + xorv[path[i+1]];
                    else {
                        ll av = AND(c, to), xv = 0;
                        for (auto cur = c; cur != to; cur = par[cur])
                            xv ^= xorv[cur];
                        sum = 2*av + xv;
                    }

                    tot += sum;
                    if (i % 2 == 1)
                        osums += sum;
                }
                assert(tot % 2 == 0); tot /= 2;

                ans[to] = tot - osums;
                init = to;
            }
        }
    }
}

bool vis[MN];
void compute(int c) { // only if par[to]==c or par[c]==to
    vis[c] = true;
    for (auto to : g[c]) {
        if (!vis[to] && (par[to] == c || par[c] == to)) {
            vis[to] = true;
            if (par[to] == c) ans[to] = ans[c] ^ xorv[to];
            else if (par[c] == to) ans[to] = ans[c] ^ xorv[c];
            compute(to);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (auto i = 0; i < M; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    // get comps and preprocess
    memset(clr, -1, sizeof clr);
    for (auto i = 1; i <= N; i++) {
        if (clr[i] == -1) {
            clr[i] = 0;
            init = -1;
            dfs(i);

            assert(init != -1);
            compute(init);
        }
    }

    cout << "! ";
    for (auto i = 1; i <= N; i++) cout << ans[i] << " \n"[i == N];

    return 0;
}