#pragma region
#include "bits/stdc++.h"
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
#define popcountll __builtin_popcountll
#define clzll __builtin_clzll
#define ctzll __builtin_ctzll
#define finline __attribute__((always_inline))
// Shorthand Function Macros
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
template<typename T> inline int sz(const T &x) { return x.size(); }
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

struct Node {
    Node *p, *ch[2];
    int sz; bool rev;
    // aux
    int val, sum, max, min;
    // lazy
    bool isLazySet;
    int lazySet, lazyInc;
    Node(int val0) {
        sz = 1; rev = false;
        p = ch[0] = ch[1] = nullptr;
        val = sum = max = min = val0;
        lazySet = lazyInc = 0;
        isLazySet = false;
    }
    void prop(Node *c) {
        if (c) {
            if (isLazySet) {
                c->isLazySet = true;
                c->lazySet = lazySet;
                c->lazyInc = 0;
            }
            if (lazyInc != 0) {
                c->lazyInc += lazyInc;
            }
            if (rev)
                c->rev ^= 1;
        }
    }
    void apply() {
        if (isLazySet) {
            max = min = val = lazySet;
            sum = lazySet * sz;
        }
        if (lazyInc != 0) {
            max += lazyInc;
            min += lazyInc;
            sum += sz * lazyInc;
            val += lazyInc;
        }
        if (rev) {
            swap(ch[0], ch[1]);
        }
    }
};
#define FUN(type, x, def) type n##x(Node *n) { return n ? n->x : def; }
FUN(int, sum, 0) FUN(int, max, INT_MIN) FUN(int, min, INT_MAX) FUN(int, sz, 0)
bool side(Node *n) { return n->p ? n == n->p->ch[1] : false; }
bool isrt(Node *n) { return n->p ? n != n->p->ch[side(n)] : true; }
void setp(Node *n, Node *p) { if (n) n->p = p; }
void setc(Node *n, Node *c, bool dir) { if (n) { n->ch[dir] = c; setp(c, n); }}

void push(Node *n) {
    if (n) {
        n->apply();
        n->prop(n->ch[0]); n->prop(n->ch[1]);

        n->isLazySet = false;
        n->lazyInc = 0;
        n->rev = false;
    }
}
void upd(Node *n) {
    if (n) {
        push(n->ch[0]); push(n->ch[1]);

        n->sum = nsum(n->ch[0]) + nsum(n->ch[1]) + n->val;
        n->max = max({nmax(n->ch[0]), nmax(n->ch[1]), n->val});
        n->min = min({nmin(n->ch[0]), nmin(n->ch[1]), n->val});
        n->sz = nsz(n->ch[0]) + nsz(n->ch[1]) + 1;
    }
}
void rot(Node *n) { 
    push(n->p); push(n);
    bool ndir = side(n), pdir = side(n->p);
    Node *p = n->p, *d = n->ch[!ndir], *pp = p->p;
    if (isrt(p)) setp(n, pp); else setc(pp, n, pdir); setc(p, d, ndir); setc(n, p, !ndir);
    upd(p); upd(n);
}
void splay(Node *n) {
    while (n && !isrt(n)) {
        if (!isrt(n->p)) {
            if (side(n) == side(n->p)) { rot(n->p); rot(n); }
            else { rot(n); rot(n); }
        }
        else rot(n);
    }
    push(n);
}
void access(Node *n) {
    for (Node *c = n, *pre = nullptr; c; c = c->p) {
        splay(c); c->ch[1] = pre; upd(c);
        pre = c;
    }
    splay(n);
}

void reroot(Node *n) {
    access(n); n->rev ^= 1; push(n);
}
void link(Node *u, Node *v) {
    reroot(v); access(u);
    setc(v, u, 0); upd(v);
}
Node* path(Node *u, Node *v) {
    reroot(u); access(v);
    // db(v->val); db(v->sum); db(v->max); db(v->min); db(v->lazyInc); db(v->lazySet); db(v->rev); dbln;
    return v;
}
Node* lca(Node *u, Node *v) {
    access(u); access(v); splay(u);
    // db(u); db(v); db(u->p); dbln;
    return u->p ? u->p : u;
}
void cut(Node *n) {
    access(n);
    setp(n->ch[0], nullptr); setc(n, nullptr, 0); upd(n);
}

const int MN = 1e5 + 1;
int N, Q, rt;
Node* lct[MN];
map<Node*, int> nodeMp;

void bad(Node *n) {
    if (!n) return;
    push(n);
    repi(0, 2) bad(n->ch[i]);
    upd(n);
}
void bad2() {
    repi(1, N + 1)
        if (isrt(lct[i]))
            bad(lct[i]);
}
void prtree(Node *n) {
    if (!n) return;
    prtree(n->ch[0]);
    print(nodeMp[n], ' ');
    prtree(n->ch[1]);
}
void dbt() {
    repi(1, N + 1) {
        db(i); db(lct[i]); dba("l", nodeMp[lct[i]->ch[0]]); dba("r", nodeMp[lct[i]->ch[1]]); dba("p", nodeMp[lct[i]->p]); db(lct[i]->rev); dbln;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q);
    repi(1, N + 1) {
        scn(int, x);
        lct[i] = new Node(x);
        nodeMp[lct[i]] = i;
    }
    repi(0, N - 1) {
        scn(int, a, b);
        link(lct[a], lct[b]);
        // db(i); db(a); db(b); dbln;dbt();
    }
    scan(rt);
    while (Q--) {
        // bad2();
        scn(int, T);
        if (T == 0) scan(rt);
        else if (T == 1) {
            scn(int, x, y, z);
            Node *n = path(lct[x], lct[y]);
            // db(T); db(x); db(y); db(z); dblb("path 2"); prtree(n); dbln;
            push(n);
            n->isLazySet = true;
            n->lazySet = z;
            push(n);
        }
        else if (T == 2) {
            scn(int, x, y, z);
            Node *n = path(lct[x], lct[y]);
            // db(T); db(x); db(y); db(z); dblb("path 2"); prtree(n); dbln;
            push(n);
            n->lazyInc = z;
            push(n);
        }
        else if (T == 3) {
            scn(int, x, y);
            // db(T); db(x); db(y);  dblb("path 2"); prtree(path(lct[x], lct[y])); dbln;
            println(path(lct[x], lct[y])->min);
        }
        else if (T == 4) {
            scn(int, x, y);
            // db(T); db(x); db(y);  dblb("path 2"); prtree(path(lct[x], lct[y])); dbln;
            println(path(lct[x], lct[y])->max);
        }
        else if (T == 5) {
            scn(int, x, y);
            // db(T); db(x); db(y);  dblb("path 2"); prtree(path(lct[x], lct[y])); dbln;
            println(path(lct[x], lct[y])->sum);
        }
        else if (T == 6) {
            reroot(lct[rt]);
            scn(int, x, y); // par(x) = y
            auto lcav = lca(lct[x], lct[y]);
            if (lcav != lct[x]) {
                cut(lct[x]);
                link(lct[y], lct[x]);
            }
        }
        else {
            reroot(lct[rt]);
            scn(int, x, y);
            println(nodeMp[lca(lct[x], lct[y])]);
        }

        // db(T);dbln;
        // dbt();
    }

    return 0;
}