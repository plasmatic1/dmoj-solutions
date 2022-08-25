// ./j5-arithmetic-sequence.yml
#include <bits/stdc++.h>
#define DEBUG 0
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

const int MN = 2e5 + 1;
int N,
    A[MN];

int D = 1;

bool check(ll st, int d) {
    ll end = st + ll(d) * (N - 1);
    int cnt = 0;
    for (auto i = 0; i < N; i++) {
        while (st < A[i] && st < end) st += d;
        if (st > end) st = end;
        
        if (A[i] == st) {
            st += d;
            cnt++;
        }
    }
    return cnt >= N-1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (auto i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    // can have non integer diff
    if (N <= 3) {
        cout << ("YES") << '\n';
        return 0;
    }

    sort(A, A+N);
    map<int, int> dcnt;
    for (auto i = 0; i < N-1; i++) {
        dcnt[A[i+1] - A[i]]++;
    }

    vector<pii> freqs;
    if (N <= 4) {
        for (auto i = 0; i < N; i++) {
            for (auto j = 0; j < i; j++) {
                freqs.eb(-1, A[i]-A[j]);
            }
        }
        D = INF;
    }
    for (auto [k, v] : dcnt)
        freqs.eb(-v, k);
    sort(all(freqs));

    int minv = *min_element(A, A+N), minv2 = INF;
    for (auto i = 0; i < N; i++)
        if (A[i] > minv && A[i] < minv2)
            minv2 = A[i];

    for (auto i = 0; i < min(D, SZ(freqs)); i++) {
        auto [_, d] = freqs[i];

        if (check(minv, d) || check(minv2, d)) {
            cout << ("YES") << '\n';
            return 0;
        }
    }

    cout << ("NO") << '\n';

    return 0;
}