// ./wesleys-anger-contest-5-problem-3.yml
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

const int MN = 2e5 + 1;
int N,
    val[MN];

int cnt[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++)
        cin >> (val[i]);

    ll ans = 0;
    for (int i = 1; i * i <= N; i++) {
        int len = i * i, goodc = 0;
        fill(cnt, cnt + N + 1, 0);
#define CHECK if (pre != i && cnt[val[j]] == i) goodc++; \
            if (pre == i && cnt[val[j]] != i) goodc--;
        for (auto j = 1; j < len; j++) {
            int pre = cnt[val[j]]++;
            CHECK;
        }
        for (auto j = len; j <= N; j++) {
            int pre = cnt[val[j]]++;
            CHECK;
            if (j > len) {
                int pos = j - len, pre = cnt[val[pos]]--;
                if (pre != i && cnt[val[pos]] == i) goodc++;
                if (pre == i && cnt[val[pos]] != i) goodc--;
            }
            // cout<<"i="<<(i)<<", "; cout<<"j="<<(j)<<", "; cout<<"goodc="<<(goodc)<<", "; cout << endl; // db i,j,goodc
            // cout<<"cnt=["; for(int i=0; i<(N+1); i++)cout<<cnt[i]<<", "; cout<<"], ";cout << endl; // db A:N+1:cnt
            ans += goodc == i;
        }
    }

    cout << (ans) << '\n';

    return 0;
}