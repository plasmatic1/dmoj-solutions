// baltic-oi-19-p6-olympiads.yml
#include "bits/stdc++.h"
using namespace std;

// Defines
#define pb push_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds; 
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
// More utilities
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2001, MK = 6;
int N, K, C,
    val[MN][MK];
unordered_set<ll> vis;

const ll FMSK = (1LL << 54) - 1;
int tmp[MK];
struct State {
    int sum;
    ll ids;
    bool operator<(const State &o) const {
        return sum < o.sum;
    }
    int kth(int x) {
        return (ids >> (x * 9)) & 511;
    }
    void setkth(int x, ll v) {
        ids &= FMSK ^ (511LL << (x * 9));
        ids |= v << (x * 9);
    }
    void init() {
        for (auto i = 0; i < K; i++)
            tmp[i] = kth(i);
        sort(tmp, tmp + K);
        ids = 0;
        for (auto i = K-1; i >= 0; i--)
            ids = (ids << 9) | tmp[i];

        sum = 0;
        for (auto i = 0; i < K; i++) {
            int csum = 0;
            for (auto j = 0; j < K; j++)
                maxa(csum, val[kth(j)][i]);
            sum += csum;
        }
    }
};
priority_queue<State> pq;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K) >> (C);
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < K; j++)
            cin >> (val[i][j]);

    // Prepare initial state
    vector<bool> use(N);
    State init{0, 0LL};
    for (auto i = K-1; i >= 0; i--) {
        int best = -INF, bid = -1;
        for (auto j = 0; j < N; j++) {
            if (!use[j] && val[j][i] > best) {
                best = val[j][i];
                bid = j;
            }
        }
        use[bid] = true;
        init.ids = (init.ids << 9) | bid;
    }
    init.init();
    use.assign(N, false);
    
    // Fracturing search
    pq.push(init);
    vis.insert(init.ids);
    for (auto i = 0; i < C; i++) {
        auto c = pq.top(); pq.pop();
        if (i == C - 1) {
            cout << (c.sum) << '\n';
            break;
        }

        for (auto j = 0; j < K; j++)
            use[c.kth(j)] = true;
        for (auto j = 0; j < K; j++) {
            for (auto k = 0; k < N; k++) {
                if (use[k]) continue;
                State alt{c.sum, c.ids};
                alt.setkth(j, k);
                alt.init();
                if (!vis.count(alt.ids)) {
                    vis.insert(alt.ids);
                    pq.push(alt);
                }
            }
        }
        for (auto j = 0; j < K; j++)
            use[c.kth(j)] = false;
    }

    return 0;
}