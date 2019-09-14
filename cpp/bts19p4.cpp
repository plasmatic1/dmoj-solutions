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

const int MN = 1e5 + 1;
int n, m,
    arr[MN], difOfT[MN << 2], difOfLazy[MN << 3];
ll best = LLINF;

void push(int i) {
    if (difOfLazy[i]) {
        difOfT[i] += difOfLazy[i];
        difOfLazy[i << 1] += difOfLazy[i];
        difOfLazy[i << 1 | 1] += difOfLazy[i];
        difOfLazy[i] = 0;
    }
}

int qu(int i, int l, int r, int q) {
    push(i);
    if (l == q && r == q) return difOfT[i];
    int mid = (l + r) >> 1;
    if (q <= mid) return qu(i << 1, l, mid, q);
    return qu(i << 1 | 1, mid + 1, r, q);
}

void setnum(int i, int l, int r, int q, int v) {
    push(i);
    if (l == q && r == q) return void(difOfT[i] = v);
    int mid = (l + r) >> 1;
    if (q <= mid) setnum(i << 1, l, mid, q, v);
    else setnum(i << 1 | 1, mid + 1, r, q, v);
}

void upd(int i, int l, int r, int ql, int qr, int v) {
    push(i);
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {return void(difOfLazy[i] += v);}
    int mid = (l + r) >> 1;
    upd(i << 1, l, mid, ql, qr, v);
    upd(i << 1 | 1, mid + 1, r, ql, qr, v);
}

int qu(int idx) {
    return qu(1, 1, n, idx + 1);
}

void setnum(int idx, int v) {
    setnum(1, 1, n, idx + 1, v);
}

// Returns the difference gained
ll upd(int l, int r, int v) {
    upd(1, 1, n, l + 1, r + 1, v);
    return (ll)(r - l + 1) * v;
}

// END WHATEVER THE FUCK THAT WAS
int wrapAroundDiff(int target) {
    int d = qu(target);
    return (m - d) - d;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    for (int i = 0; i < n; i++) {
        scan(arr[i]);
    }

    sort(arr, arr + n);

    // Init for Best=0
    ll tot = 0;
    int lptr = 0, rptr = n;
    for (int i = 0; i < n; i++) {
        int d = abs(arr[i] - arr[0]);
        if (m - d < d && rptr == n)
            rptr = i;
        setnum(i, min(d, m - d));
        tot += min(d, m - d);
    }

    for (int i = 0; i < n; i++) {
        // for (int j = 0; j < n; j++)
        //     debug(j, qu(j));

        // debug(rptr, wrapAroundDiff(rptr));
        while (rptr < n && wrapAroundDiff(rptr) < 0) {
            tot += wrapAroundDiff(rptr);
            rptr++;
        }

        while (lptr < i && wrapAroundDiff(lptr) < 0) {
            tot += wrapAroundDiff(lptr);
            lptr++;
        }

        // debug(i, tot, best, lptr, rptr);
        mina(best, tot);

        // Updates for next one
        if (i < n - 1) {
            int d = arr[i + 1] - arr[i];

            // first
            tot += upd(0, lptr - 1, -d);
            tot += upd(lptr, i, d);

            // second
            tot += upd(i + 1, rptr - 1, -d);
            tot += upd(rptr, n - 1, d);
        }
    }

    println(best);

    return 0;
}
