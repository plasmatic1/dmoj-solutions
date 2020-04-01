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

struct prob {
    int l, r; ll v;
};
Inop(prob) {
    in >> o.v >> o.l >> o.r;
    return in;
}
struct stu {
    int i, done, day;
    Cmplt(stu) {
        return done > o.done;
    }
};
Inop(stu) {
    in >> o.done >> o.day;
    return in;
}

const int MN = 2e5 + 10;
int N, M, D;
ll valP[MN], ans[MN], basePenalty[MN];
prob probs[MN];
stu studs[MN];

ll rsq(int l, int r) {
    return valP[r] - valP[l - 1];
}

// idk
struct line {
    int id;
    ll m, b;
    ll eval(ll x) { return m * x + b; }
    Cmplt(line) {
        return id >= o.id;
    }
};

line lines[MN];

// bashing dynamic cht, a new low
using T = long double; const T EPS = 1e-9;
bool lt(T a, T b) { return a + EPS < b; }
bool le(T a, T b) { return !lt(b, a); }
bool gt(T a, T b) { return lt(b, a); }
bool ge(T a, T b) { return !lt(a, b); }
bool eq(T a, T b) { return !lt(a, b) && !lt(b, a); }
bool ne(T a, T b) { return lt(a, b) || lt(b, a); }
struct Line {
    T m, b; bool isQuery; mutable function<const Line*()> succ; Line(T m, T b, bool isQuery) : m(m), b(b), isQuery(isQuery) {}
    bool operator < (const Line &L) const {
        if (!L.isQuery) return lt(m, L.m);
        const Line *s = succ(); T x = L.m;
        if (!s) return 0;
        return lt(b - s->b, (s->m - m) * x);
    }
};
template <const bool maxHull> struct DynamicConvexHullTrick : public multiset<Line> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return eq(y->m, z->m) && le(y->b, z->b);
        }
        auto x = prev(y);
        if (z == end()) return eq(y->m, x->m) && le(y->b, x->b);
        return ge((x->b - y->b) * (z->m - y->m), (y->b - z->b) * (y->m - x->m));
    }
    void addLine(T m, T b) {
        if (!maxHull) { m = -m; b = -b; }
        auto y = emplace(m, b, false);
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        while (y != begin() && bad(prev(y))) erase(prev(y));
        if (y != begin()) prev(y)->succ = [=] { return &*y; };
    }
    T getMax(T x) { auto l = *lower_bound(Line(x, 0, true)); return maxHull ? l.m * x + l.b : -(l.m * x + l.b); }
};

DynamicConvexHullTrick<true> seg[MN << 2];
ll query(int i, int l, int r, int day, int qx) {
    if (r < day || l > day) return 0LL;
    ll res = seg[i].empty() ? 0LL : round(seg[i].getMax(qx));
    // db(i); db(l); db(r); db(day); db(qx); db(res); dbln;
    if (l == r) return res;
    int mid = (l + r) / 2;
    return max(res, max(query(i << 1, l, mid, day, qx), query(i << 1 | 1, mid + 1, r, day, qx)));
}
void ins(int i, int l, int r, int ql, int qr, const line& line) {
    if (l > qr || r < ql) return;
    if (l >= ql && r <= qr) {
        seg[i].addLine(line.m, line.b);
        // dblb("adding"); db(i); db(l); db(r); db(ql); db(qr); db(line.m); db(line.b); dbln;
        return;
    }
    int mid = (l + r) / 2;
    ins(i << 1, l, mid, ql, qr, line); ins(i << 1 | 1, mid + 1, r, ql, qr, line);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, M, D);

    repi(0, M) {
        scan(probs[i]);
        valP[i + 1] = probs[i].v;
    }
    partial_sum(valP, valP + M + 1, valP);
    
    // base student stuff :P
    repi(0, N) {
        scan(studs[i]);
        studs[i].i = i;
    }
    reprev(i, M - 1, -1) {
        basePenalty[i] = basePenalty[i + 1] + rsq(i + 1, M);
    }

    // insert lines
    repi(0, M)
        lines[i] = {i, probs[i].v, rsq(i + 2, M) - (M - i - 1) * probs[i].v};
    sort(lines, lines + M);

    // cht...
    sort(studs, studs + N);
    int ptr = 0;
    repi(0, N) {
        auto &s = studs[i]; // basectr = ???
        while (ptr < M && lines[ptr].id >= s.done) {
            auto &l = lines[ptr];
            // dblb("try ins"); db(l.id); db(l.m); db(l.b); dbln;
            ins(1, 1, D, probs[l.id].l, probs[l.id].r, l);
            ptr++;
        }

        int xVal = M - s.done;
        ll adv = 0;
        if (s.done < M) {
            adv = query(1, 1, D, s.day, xVal);
            // db(i); db(s.i); db(s.day); db(s.done); db(adv); dbln;
            if (adv < 0) adv = 0;
        }

        ans[s.i] = basePenalty[s.done] - adv;
    }
    // dbarr(basePenalty, M+1); dbln;

    repi(0, N)
        println(ans[i]);

    return 0;
}