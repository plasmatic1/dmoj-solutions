// ./cco-20-p6-shopping-plans.yml
#include "bits/stdc++.h"
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
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*
Idea: Can we simplify this to roboherd?

Approach: For each type of item (T), we think of a combination of K items of type T where X_i <= K <= Y_i as a single item.  Thus, if we're able to constantly find the smallest combination of
type T in a good time complexity.  Indeed, we can use another fracturing search to find it in logN using the following state:

Size -> The current number of items taken in the combo
last2 -> The second last "gap".  This acts as a left boundary for how far the last gap can go.
last1 -> The last "gap".  This can only move to the left and always starts at the rightmost point.

Possible transitions
- Start a new gap
- Move the last gap to the left
- Append a new value
*/

const int MN = 2e5 + 1;
int N, M, K,
    X[MN], Y[MN];
ll combCnt[MN];
vector<ll> items[MN];

struct GlobalState {
    int typeNo, itemIdx; // Same as robothieves
    ll sum;
    bool operator<(const GlobalState &o) const {
        return sum > o.sum;
    }
};
struct TypeState {
    int size, last2, last1, lastIdx; // last2 -> second last "gap", last1 -> last "gap"
    ll sum;
    bool operator<(const TypeState &o) const {
        return sum > o.sum;
    }
};

ostream& operator<<(ostream& out, const GlobalState o) {
    out << "(typeNo=" << o.typeNo << ", itemIdx=" << o.itemIdx << ", sum=" << o.sum << ")";
    return out;
}
ostream& operator<<(ostream& out, const TypeState o) {
    out << "(size=" << o.size << ", last2=" << o.last2 << ", last1=" << o.last1 << ", lastIdx=" << o.lastIdx << ", sum=" << o.sum << ")";
    return out;
}

priority_queue<TypeState> typePq[MN];
vector<ll> typeBest[MN];
priority_queue<GlobalState> pq;

bool ensure(int type, int sz) {
    auto &C = items[type];
    auto &vv = typeBest[type];
    auto &pq = typePq[type];
    while (SZ(typeBest[type]) < sz) {
        if (pq.empty()) return false;
        auto c = pq.top(); pq.pop(); 
        vv.pb(c.sum);

        if (c.lastIdx + 1 < SZ(C)) {
            // - Start a new gap
            if (c.size > 0)
                pq.push({c.size, c.last1, c.lastIdx, c.lastIdx + 1, c.sum - C[c.lastIdx] + C[c.lastIdx + 1]});
            // - Append a new value
            // Only when last1 is at the leftmost possible to avoid DAG-ness
            if (c.size < Y[type] && (c.last1 == 0 && c.last2 == 0))
                pq.push({c.size + 1, c.last2, c.last1, c.lastIdx + 1, c.sum + C[c.lastIdx + 1]});
        }
        // - Move the last gap to the left
        if (c.last1 != INF && c.last1 - 1 > c.last2)
            pq.push({c.size, c.last2, c.last1 - 1, c.lastIdx, c.sum + C[c.last1] - C[c.last1 - 1]});
    }
    return true;
}

void die() {
    for (auto i = 0; i < K; i++)
        cout << (-1) << '\n';
    exit(0);
}

vector<int> globTypeOrder;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (M) >> (K);
    for (auto i = 1; i <= M; i++)
        items[i].pb(0);
    for (auto i = 0; i < N; i++) {
        int t, c;
        cin >> t >> c;
        items[t].pb(c);
    }
    for (auto i = 1; i <= M; i++)
        cin >> (X[i]) >> (Y[i]);

    for (auto i = 1; i <= M; i++) {
        sort(all(items[i]));
        int sz = SZ(items[i]) - 1;
        if (sz < X[i]) die();
        mina(Y[i], sz);

        TypeState init{X[i], 0, 0, X[i], 0};
        for (int j = 1; j <= X[i]; j++)
            init.sum += items[i][j];
        typePq[i].push(init);

        ensure(i, 2);
    }

    globTypeOrder.resize(M);
    iota(all(globTypeOrder), 1);
    sort(all(globTypeOrder), [&] (const int a, const int b) {
        bool a1 = SZ(typeBest[a]) == 1, b1 = SZ(typeBest[b]) == 1;
        if (a1 != b1) return a1 < b1;
        return typeBest[a][1] - typeBest[a][0] < typeBest[b][1] - typeBest[b][0];
    });

    GlobalState init{0, 0, 0};
    for (auto i = 1; i <= M; i++)
        init.sum += typeBest[i][0];
    pq.push(init);
    for (auto i = 0; i < K; i++) {
        if (pq.empty())
            cout << (-1) << '\n';
        else {
            auto c = pq.top(); pq.pop();
            int ctype = globTypeOrder[c.typeNo];
            cout << (c.sum) << '\n';


            // Moving to next type
            if (c.typeNo < M - 1) {
                int ntype = globTypeOrder[c.typeNo + 1];
                if (c.itemIdx == 1 && SZ(typeBest[ntype]) > 1)
                    pq.push({c.typeNo + 1, 1, c.sum - (typeBest[ctype][1] - typeBest[ctype][0]) + (typeBest[ntype][1] - typeBest[ntype][0])});
                if (c.itemIdx > 0 && SZ(typeBest[ntype]) > 1)
                    pq.push({c.typeNo + 1, 1, c.sum + (typeBest[ntype][1] - typeBest[ntype][0])});
            }
            if (ensure(ctype, c.itemIdx + 2))
                pq.push({c.typeNo, c.itemIdx + 1, c.sum - typeBest[ctype][c.itemIdx] + typeBest[ctype][c.itemIdx + 1]});
        }
    }

    return 0;
}