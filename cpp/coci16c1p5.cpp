// ./coci-16-contest-1-5-kralj.yml
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

const int MN = 5e5 + 1;
int N,
    A[MN], E[MN], D[MN], psum[MN*2];
vector<int> at[MN*2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> A[i];
        psum[A[i]]++; psum[A[i]+N]++;
    }
    for (auto i = 1; i <= N; i++) cin >> D[i];
    for (auto i = 1; i <= N; i++) {
        cin >> E[i];
        at[A[i]].pb(E[i]); at[A[i]+N].pb(E[i]);
    }
    for (auto i = 1; i <= 2*N; i++) psum[i]--;
    partial_sum(psum, psum + 2*N+1, psum);

    // find suitable starting position
    deque<pii> dq;
    for (auto i = 1; i < N; i++) {
        while (!dq.empty() && dq.back().sn >= psum[i])
            dq.pop_back();
        dq.eb(i, psum[i]);
    }
    for (auto i = N; i < 2*N; i++) {
        while (!dq.empty() && dq.front().fs < i-N)
            dq.pop_front();
        while (!dq.empty() && dq.front().sn >= psum[i])
            dq.pop_back();
        dq.eb(i, psum[i]);
        if (dq.front().sn >= psum[i]) {
            // run greedy idea
            int ans = 0;
            set<int> elf;
            for (auto j = 0; j < N; j++) {
                int p = i - N + 1 + j;
                if (p > N) p -= N;

                elf.insert(all(at[p]));
                auto ptr = elf.upper_bound(D[p]);
                if (ptr != elf.end()) {
                    elf.erase(ptr);
                    ans++;
                }
                else
                    elf.erase(elf.begin());
            }

            cout << (ans) << '\n';

            return 0;
        }
    }

    return 0;
}