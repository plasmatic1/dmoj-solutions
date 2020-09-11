// baltic-oi-18-p1-love-polygon.yml
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

const int MN = 1e5 + 1;
int N,
    to[MN];

map<string, int> mp;
int ctr = -1;
int get(string &n) {
    if (!mp.count(n))
        return mp[n] = ++ctr;
    return mp[n];
}

int indeg[MN];
vector<int> from[MN];
bool done[MN];

ostream& operator<<(ostream& out, const pii o) {
    out << "(fs=" << o.fs << ", sn=" << o.sn << ")";
    return out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    if (N % 2) {
        cout << (-1) << '\n';
        return 0;
    }
    for (auto i = 0; i < N; i++) {
        string x, y;
        cin >> x >> y;
        to[get(x)] = get(y);
    }
    // for (auto i = 0; i < N; i++) {
    //     cout<<"i="<<(i)<<", "; cout<<"to[i]="<<(to[i])<<", "; cout << endl; // db i,to[i]
    // }
    for (auto i = 0; i < N; i++)
        indeg[to[i]]++;
    for (auto i = 0; i < N; i++)
        if (i == to[to[i]] && i != to[i])
            done[i] = done[to[i]] = true;
    set<pii> q;
    for (auto i = 0; i < N; i++)
        if (!done[i])
            q.emplace(indeg[i], i);
    int ans = 0;
    while (!q.empty()) {
        int c = q.begin()->sn; q.erase(q.begin());
        // cout<<"c="<<(c)<<", "; cout << "q=["; for (auto x:q)cout<<x<<", "; cout<<"], "; cout << endl; // db c,I:q
        if (!done[to[c]] && to[c] != c) {
            done[c] = done[to[c]] = true;
            q.erase(q.find(mpr(indeg[to[c]], to[c])));
            ans++;
            if (!done[to[to[c]]]) {
                int tto = to[to[c]], odeg = indeg[tto]--;
                q.erase(q.find(mpr(odeg, tto)));
                q.emplace(indeg[tto], tto);
            }
        }
        else
            ans++;
    }

    cout << (ans) << '\n';

    return 0;
}