// ./dmopc-14-contest-5-p5-aircraft-carrier-akagi.yml
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

const int MV = 6e5, D = 2e5;
// Default: Point increment and prefix sum query
struct Comp {
    using Data = ll;
    const Data vdef = 0;
    void applyUpdate(Data &to, Data &v) { to += v; }
    int transformInd(int idx, int N) { return idx + D; }
};
template <typename Comp> struct BIT {
    using Data = typename Comp::Data; Comp C;
    int N; vector<Data> bit;
    void init(int n0) {
        N = n0;
        bit.assign(N + 1, C.vdef);
    }
    void upd(int x, Data v) {
        // cout<<"x="<<(x)<<", "; cout << endl; // db x
        x = C.transformInd(x, N);
        if (x < 0) return;
        for (; x <= N; x += x & -x)
            C.applyUpdate(bit[x], v);
    }
    Data query(int x) {
        x = C.transformInd(x, N);
        if (x < 0) return C.vdef;
        // cout<<"[q]: "; cout<<"x="<<(x)<<", "; cout << endl; // db l:q,x
        Data res = C.vdef;
        for (; x; x -= x & -x)
            C.applyUpdate(res, bit[x]);
        return res;
    }
};

const int MN = 2e5 + 1; // what what what
int N, K,
    H[MN];

struct Median {
    BIT<Comp> cnt, sum;
    ll sh, totCnt = 0, totSum = 0;

    Median() {
        cnt.init(MV);
        sum.init(MV);
        sh = 0;
    }

    void upd(int v, int mul) {
        v -= sh;
        cnt.upd(v, mul);
        sum.upd(v, v * mul);
        totCnt += mul;
        totSum += v * mul;
    }
    void shift(int x) { sh += x; }
    int cntUnder(int x) { return cnt.query(x - sh); }
    ll sumUnder(int x) { return sum.query(x - sh) + sh * cnt.query(x - sh); }
    int getCnt() { return totCnt; }
    ll getSum() { return totSum + sh * totCnt; }
};
Median stay, inc;

int cntUnder(int x) { return stay.cntUnder(x) + inc.cntUnder(x); }
ll sumUnder(int x) { return stay.sumUnder(x) + inc.sumUnder(x); }
int cnt() { return stay.getCnt() + inc.getCnt(); }
ll sum() { return stay.getSum() + inc.getSum(); }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> (N) >> (K);
    for (auto i = 1; i <= N; i++) {
        cin >> (H[i]);
        H[i] += i - 1;
    }

    if (K % 2 == 0) K++;
    if (K > N) { // Impossible case
        cout << (-1) << '\n';
        return 0;
    }

    ll ans = LLINF;
    for (auto i = 1; i <= N; i += 2) {
        int stayAdd = (i + 1) / 2, incRem = -1, incAddL = -1, incAddR = -2;
        if (i > 3) {
            incRem = stayAdd;
            incAddL = i - 1;
            incAddR = i;
        }
        else if (i > 1)
            incAddL = incAddR = 3;

        // Update BITs
        int globSh = i - 1, changeVal = H[stayAdd] - globSh;
        stay.upd(changeVal, 1);
        inc.shift(-2);
        if (incRem != -1) inc.upd(changeVal, -1);
        for (auto j = incAddL; j <= incAddR; j++)
            inc.upd(H[j] - globSh, 1);

        // Get ans 
        if (i >= K) {
            // Bsearch for median
            int l = -2e5 - 1, r = 4e5;
            while (l + 1 < r) {
                int mid = (l + r) / 2;
                if (cntUnder(mid) >= (i + 1) / 2)
                    r = mid;
                else
                    l = mid;
            }

            // Get cur ans
            ll mid = r, csum = sumUnder(mid), ccnt = cntUnder(mid), 
               under = mid * ccnt - csum, over = (sum() - csum) - mid * (cnt() - ccnt);

            mina(ans, under + over);
        }
    }

    cout << (ans) << '\n';

    return 0;
}