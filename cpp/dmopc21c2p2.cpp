// ./p2-scrambling-swaps.yml
#define DEBUG 0
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

const int MN = 301;
int N, Q,
    P1[MN], id1[MN], P2[MN], id2[MN];

template <typename It> vector<int> app(vector<int> p, It q) {
    vector<int> res(N+1);
    for (auto i = 1; i <= N; i++)
        res[i] = q[p[i]];
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;

    iota(P1, P1+N+1, 0);
    iota(P2, P2+N+1, 0);
    iota(id1, id1+N+1, 0);
    iota(id2, id2+N+1, 0);

    while (Q--) {
        char T; cin >> T;
        if (T == 'B') {
            int a, b; cin >> a >> b;

            swap(P1[id1[a]], P1[id1[b]]);
            swap(id1[a], id1[b]);
        }
        else if (T == 'E') {
            int a, b; cin >> a >> b;

            swap(id2[P2[a]], id2[P2[b]]);
            swap(P2[a], P2[b]);
        }
        else {
            vector<int> PQ(N+1);
            for (auto i = 1; i <= N; i++)
                cin >> PQ[i];

            // vector<int> tmp = app(vector<int>(P1, P1+N+1), P2);
            // PQ = app(PQ, tmp.begin());
            PQ = app(vector<int>(id2, id2+N+1), PQ.begin());
            if (DEBUG) { cout << "PQ=["; for (auto __x:PQ)cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db I:PQ
            PQ = app(vector<int>(id1, id1+N+1), PQ.begin());
            if (DEBUG) { cout << "PQ=["; for (auto __x:PQ)cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db I:PQ
            
            if (DEBUG) { cout<<"(P1+1)=["; for(int __i=0; __i<(N); __i++)cout<<((P1+1))[__i]<<", "; cout<<"], ";cout << endl; } //__RAW_DEBUG_LINE__:db A:N:(P1+1)
            if (DEBUG) { cout<<"(P2+1)=["; for(int __i=0; __i<(N); __i++)cout<<((P2+1))[__i]<<", "; cout<<"], ";cout << endl; } //__RAW_DEBUG_LINE__:db A:N:(P2+1)
            // if (DEBUG) { cout << "tmp=["; for (auto __x:tmp)cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db I:tmp

            for (auto i = 1; i <= N; i++)
                cout << PQ[i] << " \n"[i == N];
        }
    }

    return 0;
}