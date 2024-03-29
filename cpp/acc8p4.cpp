// ./problem-4-up-and-down.yml
#include <bits/stdc++.h>
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 1e4+1, MQ = 1e5+1;
int N, Q,
    dep[MN], cnt[MN][MN];
vector<int> g[MN];

struct E {
    int u, d, p;
};

vector<int> p;
vector<E> seq;
void pushSeq(int k) {
    seq.pb({k, dep[k], p[k]});
    p[k] = seq.size()-1;
}

void dfs(int c, int p, int cdep) {
    dep[c] = cdep;
    pushSeq(c);
    for (auto to : g[c]) {
        if (to != p) {
            dfs(to, c, cdep+1);
            pushSeq(c);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (auto i = 1; i < N; i++) {
        int a, b; cin >> a >> b;
        g[a].pb(b);
        g[b].pb(a);
    }

    p.assign(N+1, -1);
    dfs(1, -1, 0);

    for (auto i = 0; i < 2*N-1; i++) {
        auto &c = seq[i];
        if (c.p == -1) {
            int mindep = seq[i].d, a = 0;
            for (auto j = i; j < 2*N-1; j++) {
                if (seq[j].d < mindep) {
                    a += mindep-seq[j].d;
                    mindep = seq[j].d;
                }
                if (seq[j].p < i)
                    cnt[a][seq[j].d-mindep]++;
            }
        }
    }

    cin >> Q;
    while (Q--) {
        int a, b; cin >> a >> b;
        cout << (cnt[a][b]+cnt[b][a]) << '\n';
    }

    return 0;
}