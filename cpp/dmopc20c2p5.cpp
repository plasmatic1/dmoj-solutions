// ./dmopc-20-contest-2-p5-majority-subarrays.yml
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
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

const int MN = 2e6 + 10;
int N,
    val[MN], cnt[MN];
int start[MN], I[MN];

const int BITM = MN;
struct E {
    int v, a, q;
} bit[BITM];
int cqid = -1, D;
inline void verify(int x) {
    if (bit[x].q != cqid) {
        bit[x].q = cqid;
        bit[x].v = bit[x].a = 0;
    }
}
void add(int x, int v, int a) {
    for (x += D; x < BITM; x += x & -x) {
        verify(x);
        bit[x].v += v;
        bit[x].a += a;
    }
}
int query(int ox) {
    int sum = 0;
    for (int x = ox+D; x; x -= x & -x) {
        verify(x);
        sum += bit[x].v + ox * bit[x].a;
    }
    return sum;
}
inline void rinc(int l, int r) { 
    add(l, 1-l, 1);
    add(r+1, r, -1);
}
inline void reset() { cqid++; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N);
    for (auto i = 1; i <= N; i++) {
        cin >> (val[i]);
        cnt[val[i]]++;
    }
    partial_sum(cnt, cnt+N+1, cnt);
    copy(cnt, cnt+N, start+1);
    for (auto i = 1; i <= N; i++) {
        I[++cnt[val[i]-1]] = i;
        start[i]++;
    }
    start[N+1] = N+1;

    ll ans = 0;
    for (auto i = 1; i <= N; i++) {
        if (start[i] != start[i+1]) {
            int sz = start[i+1]-start[i];
            D = N-sz+1;
            reset();

            int preval = 0, cmin = 0;
            for (auto j = 0; j < sz; j++) {
                int curIdx = I[start[i]+j], cur = 2*(j+1) - curIdx, ocur = cur, nxtIdx = j < sz-1 ? I[start[i]+j+1] : N+1;
                rinc(cur-1, preval);
                ans += query(cur-1);
                for (auto k = curIdx+1; k < nxtIdx; k++) {
                    cur--;
                    if (cur < cmin) break;
                    ans += query(cur-1);
                }

                preval = ocur;
                cmin = min(cmin, ocur - (nxtIdx - curIdx - 1));
            }
        }
    }

    cout << (ans) << '\n';

    return 0;
}