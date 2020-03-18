#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define mtup make_tuple
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
#define finline __attribute__((always_inline))
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << (x) << ", "
#define dblb(s) cout << "[" << (s) << "] "
#define dba(alias, x) cout << (alias) << ": " << (x) << ", "
template<typename F> inline string __generic_tostring(F f) { stringstream ss; ss << f; return ss.str(); }
template<typename F> inline string __join_comma(F f) {return __generic_tostring(f);}
template<typename F, typename... R> string __join_comma(F f, R... r) { return __generic_tostring(f) + ", " + __join_comma(r...); }
#define dbp(alias, ...) cout << (alias) << ": (" << __join_comma(__VA_ARGS__) << "), "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

struct line {
    int b, m, i;
    Cmplt(line) { return m == o.m ? b > o.b : m < o.m; }
};

/*
y=ax+b
y=cx+d

(c-a)x+(d-b)=0
(c-a)x=-(d-b)
x=-(d-b)/(c-a)
*/

const int MN = 1e5 + 1, MQ = 5e5 + 1;
int N, Q,
    ans[MQ];
line lines[MN];
pii qus[MQ];

ld eval(int i, ld x) {
    return lines[i].m * x + lines[i].b;
}

ld inter(int i, int j) {
    return -ld(lines[j].b - lines[i].b) / (lines[j].m - lines[i].m);
}

const ld EPS = 1e-10;
bool skip(int i, int j, int k) {
    ld i1 = inter(i, k), i2 = inter(i, j);
    // db(i); db(j); db(k); db(i1); db(i2); dbln;
    return abs(i1 - i2) > EPS && i1 < i2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q);
    repi(0, N) {
        int b, m; scan(b, m);
        lines[i] = {b, m, i};
    }
    sort(lines, lines + N);
    repi(0, Q) {
        int x; scan(x);
        qus[i] = mpr(x, i);
    }
    sort(qus, qus + Q);

    // get convex hull
    vi dq;
    repi(0, N) {
        if (i > 0 && lines[i].m == lines[i - 1].m) continue; // line definitely will never be used
        while (sz(dq) >= 2 && skip(dq[dq.size() - 2], dq.back(), i))
            dq.pop_back();
        dq.pb(i);
    }

    // make "important" map
    map<ld, int> important;
    important[-1e18] = lines[dq[0]].i;
    int sz = sz(dq);
    repi(1, sz) {
        ld i1 = inter(dq[i - 1], dq[i]);
        if (i1 > 500010) continue;
        // db(i); db(i1); db(dq[i]); db(lines[dq[i]].i); dbln;

        // at intersection
        int id = min(lines[dq[i]].i, lines[dq[i - 1]].i);
        if (important.find(i1) == important.end())
            important[i1] = id;
        else 
            mina(important[i1], id);

        // post intersection
        i1 += EPS;
        important[i1] = lines[dq[i]].i;
    }

    // setprec(cout, 15);
    // for (auto p : important)
    //     dba("x", p.first), dba("id", p.second), dbln;

    // answer queries
    deque<pair<ld, int>> dq2(all(important)); // x-pos, id
    int cans = -1;
    repi(0, Q) {
        auto q = qus[i];
        while (!dq2.empty() && dq2[0].first <= q.first) {
            cans = dq2[0].second;
            dq2.pop_front();
        }
        ans[q.second] = cans;
    }

    // output
    repi(0, Q)
        println(ans[i]);

    return 0;
}