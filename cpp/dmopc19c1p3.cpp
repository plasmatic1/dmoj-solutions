#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printDebug(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
inline void println(){cout<<"\n";}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

struct ed {
    ll v, w;
};

const int MN = 3e5 + 1;
const ll MOD = 1e9 + 7;
int n, m;
ll k, ba, bb, bc,
    tot = 1;
vec<ed> g[MN];
bool vis[MN];
vl up, down;

// dfs util
void dfs(int cur, ll cval, bool isup) {
    if (vis[cur]) {
        return;
    }
    // debug(cur, cval);
    vis[cur] = true;

    // Increases with A or increases against A
    if (isup) up.pb(cval);
    else down.pb(cval);

    // Try a single value
    for (ed adj : g[cur]) {
        dfs(adj.v, adj.w - cval, !isup);
    }
}

// fail
bool vis2[MN], fail = false, ultrafail = false;
int clr[MN];
ll val[MN];
ll failstart = -1, failstartval = -1;
void checkFail(int cur, ll cval, int cclr) {
    if (vis2[cur]) {
        if (clr[cur] != cclr) {
            fail = true; // odd length cycle
            ll delta = abs(val[cur] - cval);
            if (delta % 2LL) {
                ultrafail = true;
            }
            else {
                // if (val[cur] != cval && ((val[cur] < ))) {

                // }

                if (failstart == -1 && failstartval == -1) {
                    failstart = cur;
                    failstartval = (val[cur] + cval) >> 1; // find middle
                }
            }
        }
        else { // direction has to be same
            if (val[cur] != cval)
                ultrafail = true;
        }
        return;
    }
    vis2[cur] = true;
    clr[cur] = cclr;
    val[cur] = cval;
    // Try a single value
    for (ed adj : g[cur]) {
        checkFail(adj.v, adj.w - cval, !cclr);
    }
}

// fail2
bool vis3[MN];
void setVals(int cur, ll cval) {
    if (vis3[cur]) {
        if (val[cur] != cval) {
            ultrafail = true;
        }
        return;
    }
    vis3[cur] = true;
    val[cur] = cval;
    if (val[cur] < 1LL || val[cur] > k) {
        ultrafail = true;
    }
    for (ed adj : g[cur]) {
        setVals(adj.v, adj.w - cval);
    }
}

// fail 3
void setVis(int cur) {
    if (vis[cur]) return;
    vis[cur] = true;
    for (auto adj : g[cur])
        setVis(adj.v);
}

ll minFound(ll fVal) {
    // if (fVal >= k || fVal < )
    ll minv = LLONG_MAX;
    for (ll x : up) mina(minv, x + fVal);
    for (ll x : down) mina(minv, x - fVal);
    return minv;
}

ll maxFound(ll fVal) {
    ll maxv = LLONG_MIN;
    for (ll x : up) maxa(maxv, x + fVal);
    for (ll x : down) maxa(maxv, x - fVal);
    return maxv;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m, k);

    for (int i = 0; i < m; i++) {
        scan(ba, bb, bc);
        g[ba].pb({bb, bc});
        g[bb].pb({ba, bc});
    }

    // n = 300000;
    // m = 300000 - 1;
    // k = 1e9;
    // for (int i = 1; i < n; i++) {
    //     g[i].pb({i + 1, k});
    //     g[i + 1].pb({i, k});
    // }

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            // debug(i);
            checkFail(i, 0LL, 0);
            if (ultrafail) {
                println(0);
                return 0;
            }
            else if (fail) {
                setVals(failstart, failstartval);
                // debug(i, fail, failstart, failstartval, ultrafail);

                if (ultrafail) {
                    println(0);
                    return 0;
                }

                fail = false;
                failstart = -1;
                failstartval = -1;
                setVis(i);
                continue;
            }

            up.clear();
            down.clear();
            dfs(i, 0, true);
            // for (int j = 1; j <= k; j++)
            //     debug(i, j, minFound(j), maxFound(j));
            // debug("st", i);
            // Get lower
            ll l = 0, r = k;
            while (l + 1 < r) {
                ll mid = (l + r) >> 1, r1 = minFound(mid - 1), r2 = minFound(mid), s1 = maxFound(mid - 1), s2 = maxFound(mid);
                // debug("lo", i, l, r, mid, r1);
                // Go right as long as it's increasing and the max of min is <1
                if ((r1 < r2 && r2 < 1) || (s1 > s2 && s2 > k))
                    l = mid;
                else
                    r = mid;
            }
            ll lo = r;
            // debug("low", l, r);

            // Get upper
            l = 1, r = k + 1;
            while (l + 1 < r) {
                ll mid = (l + r) >> 1, r1 = minFound(mid), r2 = minFound(mid + 1), s1 = maxFound(mid), s2 = maxFound(mid + 1);
                // debug("hi", i, l, r, mid, r1, r2);
                // Go left as long as it's decreasing and the max of min is <1
                if ((r1 >= r2 && r1 < 1) || (s1 <= s2 && s1 > k))
                    r = mid;
                else
                    l = mid;
            }
            ll hi = l;
            // debug("hi", l, r);

            // debug(i, lo, hi);

            // Mult to tot
            tot = (tot * (hi - lo + 1)) % MOD;
        }
    }

    println(tot);

    return 0;
}
