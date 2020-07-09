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

namespace Splay {
    struct Node {
        Node *ch[2], *p;
        bool rev;

        // maintain auxillary information here
        int sum, val;

        Node(int val0) {
            val = sum = val0;
            rev = false;
            ch[0] = ch[1] = p = nullptr;
        }
    };

    int sum(Node *n) { return n ? n->sum : 0; }
    bool dir(Node *n) { return n->p ? n == n->p->ch[1] : false; }
    bool isrt(Node *n) { return n->p ? n->p->ch[dir(n)] != n : true; }
    void setp(Node *n, Node *p) { if (n) n->p = p; }
    void setc(Node *n, Node *c, bool dir) { if (n) { n->ch[dir] = c; setp(c, n); }}

    void push(Node *n) {
        if (n && n->rev) {
            // must include
            swap(n->ch[0], n->ch[1]);
            if (n->ch[0]) n->ch[0]->rev ^= 1;
            if (n->ch[1]) n->ch[1]->rev ^= 1;
            n->rev = false;

            // maintain auxillary information here
        }
    }
    void upd(Node *n) {
        if (n) {
            push(n->ch[0]); push(n->ch[1]); // must include

            // maintain auxillary information here
            n->sum = sum(n->ch[0]) + sum(n->ch[1]) + n->val;
        }
    }
    void rot(Node *n) {
        push(n->p); push(n);
        bool nd = dir(n), pd = dir(n->p);
        Node *p = n->p, *pp = p->p, *d = n->ch[!nd];
        if (isrt(p)) setp(n, pp); else setc(pp, n, pd); setc(p, d, nd); setc(n, p, !nd); // If p is the root of the auxtree, don't set p->p's children
        upd(p); upd(n);
    }
    void splay(Node *n) {
        while (n && !isrt(n)) {
            if (!isrt(n->p)) {
                if (dir(n->p) == dir(n)) { rot(n->p); rot(n); }
                else { rot(n); rot(n); }
            }
            else rot(n);
        } push(n);
    }
    // LCT Time
    void access(Node *n) {
        for (Node *c = n, *pre = nullptr; c; c = c->p) {
            splay(c); c->ch[1] = pre; upd(c);
            pre = c;
        }
        splay(n);
    }
}
using Splay::access; using Splay::upd; using Splay::push; using Splay::splay; using Splay::Node;
using Splay::isrt; using Splay::setp; using Splay::setc;

void makelct(Node *&n, int val) {
    n = new Node(val);
}
void reroot(Node *n) {
    access(n); n->rev ^= 1; push(n);
}
void link(Node *u, Node *v) {
    access(u); reroot(v);
    setc(v, u, false); upd(v);
}
void cut(Node *n) {
    access(n);
    setc(n, nullptr, false); upd(n);
}
int query(Node *u, Node *v) {
    reroot(u); access(v);
    return v ? v->sum : 0;
}
void upd(Node *n, int x) {
    access(n);
    n->val = x; upd(n);
}
Node* getroot(Node *n) {
    access(n); push(n);
    while (n->ch[0]) {
        n = n->ch[0];
        push(n);
    }
    return n;
}

const int MN = 30001;
int N, Q;
Node *lct[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N);
    repi(1, N + 1) {
        scn(int, x);
        makelct(lct[i], x);
    }
    scan(Q);
    while (Q--) {
        scn(string, type);
        scn(int, x, y);
        if (type == "bridge") {
            if (getroot(lct[x]) != getroot(lct[y])) {
                link(lct[x], lct[y]);
                println("yes");
            }
            else println("no");
        }
        else if (type == "penguins") {
            upd(lct[x], y);
        }
        else {
            if (getroot(lct[x]) != getroot(lct[y]))
                println("impossible");
            else
                println(query(lct[x], lct[y]));
        }
        cout.flush();
    }

    return 0;
}