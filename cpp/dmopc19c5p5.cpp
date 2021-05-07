// ./dmopc-19-contest-5-p5-crazy-cyclic-coincidences.yml
#include "bits/stdc++.h"
using namespace std;
using ll = long long;
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;
using pii = pair<int, int>;
using T = tuple<int, int, int>;

/*
 * take random spanning tree for each comp.
 *
 * consider non tree edge (a,b,w)
 * Consider cycle r->a->b->r for some root r
 * Cycle XORsum is dep[a]^w^dep[b]
 *
 * Now consider cycle that w/ some start node S, and then takes non-tree edges
 * (a, b, w1)
 * (c, d, w2)
 * (e, f, w3)
 * ... (we'll just consider the first 3 edges for now)
 * with the other paths being connected by tree paths up or down the tree (note that we consider the edges (a,a,0) to exist for all 1<=a<=N)
 *
 * We get cyc length of:
 * S->a->b->c->d->e->f->S
 *
 * (dis[S]^dis[a]) ^ w1 ^ (dis[b]^dis[c]) ^ w2 ^ (dis[d]^dis[e]) ^ w3 ^ (dis[f]^dis[S])
 * We can break it up into:
 * - dis[a] ^ w1 ^ dis[b]
 *   dis[c] ^ w2 ^ dis[d]
 *   dis[e] ^ w3 ^ dis[f]
 *   dis[S] ^ dis[S] (= 0)
 *
 * Which is XORsum combination of single edge cycles for some root R.  Solve using XOR basis
 */

const int MN = 5e5 + 1, LG = 20;
int N, M, V;
vector<pii> g[MN];

bool vis[MN];
int dep[MN];
vector<T> cycEdges;
vector<int> comp;
void dfs(int c, int p) {
    comp.push_back(c);
    vis[c] = true;
    for (auto [to, w] : g[c]) {
        if (to != p) {
            if (!vis[to]) {
                dep[to] = dep[c]^w;
                dfs(to, c);
            }
            else
                cycEdges.emplace_back(c, to, w);
        }
    }
}

int basis[LG];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> V;
    for (auto i = 0; i < M; i++) {
        int a, b, w; cin >> a >> b >> w;
        g[a].emplace_back(b, w);
        g[b].emplace_back(a, w);
    }
    for (auto i = 1; i <= N; i++) {
        if (!vis[i]) {
            comp.clear();
            cycEdges.clear();
            dfs(i, -1);

            // make XORbasis
            fill(basis, basis+LG, 0);
            for (auto [a, b, w] : cycEdges) {
                int len = dep[a]^dep[b]^w;
                
                for (auto j = LG-1; j >= 0; j--) {
                    if ((len >> j) & 1) {
                        if (!basis[j]) {
                            basis[j] = len;
                            break;
                        }
                        else
                            len ^= basis[j];
                    }
                }
            }

            // try to make S
            int cur = 0;
            for (auto j = LG-1; j >= 0; j--) {
                if (((V >> j) & 1) != ((cur >> j) & 1))
                    cur ^= basis[j];
            }
            if (cur == V)
                return cout << "yes\n", 0;
        }
    }

    cout << "no\n";

    return 0;
}