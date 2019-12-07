#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using um = unordered_map<K, V>; template<typename K, typename V> using om = map<K, V>;
template <typename K> using us = unordered_set<K>; template <typename K> using os = set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Function Macros
#define Fori(a, b) for (int i = a; i < b; i++)
#define Forj(a, b) for (int j = a; j < b; j++)
#define Fork(a, b) for (int k = a; k < b; k++)
#define Forinci(a, b) for (int i = a; i <= b; i++)
#define Forincj(a, b) for (int j = a; j <= b; j++)
#define Forinck(a, b) for (int k = a; k <= b; k++)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(type) bool operator()(const type &a, const type &b)
// Shorthand Function Macros Part 2
#define Pow2(x) (1LL << (x))
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void debugArray(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, casttostr_ = ",";
void debug_(){cout<<endl;}
template<typename T> string debug_tostring_(T val) { ostringstream os; os << val; return os.str(); }
string debug_name_(string s, string str_val) {
    string ret = ""; if (s[0] == ' ') { ret += ' '; s = s.substr(1); } if (s[0] == '"' && s[s.length() - 1] == '"') { ret += string("[") + str_val + "]"; }
    else if (s.length() == (size_t)3 && s[0] == '\'' && s[2] == '\'') { ret += '(' + str_val + ')'; } else { ret += s + ": " + str_val; } return ret;
} template<typename F, typename... R> void debug_(F f, R... r) {
    int bc = 0; string pr = "";
    while (bc != 0 || dnms_[di_] != ',') { if (dnms_[di_] == '(') { bc++; } else if (dnms_[di_] == ')') { bc--; } pr += dnms_[di_++]; }
    di_++; cout << debug_name_(pr, debug_tostring_(f)) << ","; debug_(r...);
}
#define debug(...) do{dnms_=#__VA_ARGS__+casttostr_,di_=0,debug_(__VA_ARGS__);}while(0)
#pragma endregion

const int MN = 1e5 + 1, MK = 51;

struct {
    set<int> ids[MK];

    inline void add(int i, int x) {
        ids[x].insert(i);
    }

    inline void remove(int i, int x) {
        ids[x].erase(ids[x].find(i));
    }

    inline int first(int x, int from, int to) {
        auto ptr = ids[x].lower_bound(from);
        int ret = ptr == ids[x].end() ? INF : *ptr;
        return ret > to ? INF : ret;
    }

    inline int last(int x, int from, int to) {
        if (ids[x].empty()) return -INF;
        auto ptr = ids[x].upper_bound(to);
        int ret = ptr == ids[x].begin() ? -INF : *(--ptr);
        return ret < from ? -INF : ret; 
    }
} Index;

template <typename T> inline void sortedInsert(vec<T> &vv, T v) {
    auto ptr = upper_bound(vv.begin(), vv.end(), v);
    vv.insert(ptr, v);
}

template <typename T> inline void sortedRemove(vec<T> &vv, T v) {
    auto ptr = lower_bound(vv.begin(), vv.end(), v);
    if (v == *ptr)
        vv.erase(ptr);
}

int n, Q, k,
    arr[MN];

struct p {
    int i, v;
    Cmplt(p) { return i == o.i ? v < o.v : i < o.i; }
    bool operator==(const p &o) { return i == o.i && v == o.v; }
};

struct snode {
    int best, 
        pfx[MK], sfx[MK];
    vec<p> firsts;

    inline void tryErase(p x) {
        sortedRemove(firsts, x);
    }

    // assumes index struct has been updated
    inline void changeNum(int l, int r, int oldv, int newv) {
        // debug(l, r, oldv, newv, "changenumst");
        // if (!isInit) {
        //     auto ptr = firsts.find({pfx[oldv], oldv});
        //     auto ptr2 = firsts.find({pfx[newv], newv});
        //     // debug(ptr->i, ptr->v);
        //     // debug(ptr2->i, ptr2->v);
        // }
        tryErase({pfx[oldv], oldv});
        pfx[oldv] = Index.first(oldv, l, r) - l + 1;
        if (pfx[oldv] <= n) sortedInsert(firsts, {pfx[oldv], oldv});

        tryErase({pfx[newv], newv});
        pfx[newv] = Index.first(newv, l, r) - l + 1;
        if (pfx[newv] <= n) sortedInsert(firsts, {pfx[newv], newv});

        sfx[oldv] = r - Index.last(oldv, l, r) + 1;
        sfx[newv] = r - Index.last(newv, l, r) + 1;
        // debug(l, r, oldv, newv, "changenumend");
    }

    // void init() {
    //     memset(pfx, 0x3f, sizeof pfx);
    //     memset(sfx, 0x3f, sizeof sfx);
    //     best = INF;
    // }
};

snode seg[MN << 2];

// merges the two child values of a seg node
inline void mergeSeg(int i, int l, int r) {// debug("merge", i, l, r, q, v);
    auto &lhs = seg[i << 1], &rhs = seg[i << 1 | 1];
    int midMin = INF, lhsMax = 0;
    int pfxMax = 0, sfxMax = 0;
    Forincj(1, k) {
        if (rhs.pfx[j] > n) // not present
            maxa(lhsMax, lhs.sfx[j]);
        maxa(pfxMax, seg[i].pfx[j]);
        maxa(sfxMax, seg[i].sfx[j]);
    }

    for (auto it = rhs.firsts.rbegin(); it != rhs.firsts.rend(); it++) { // go from right to left on rhs, maintain 2-ptr on best options
        // debug(it->i, it->v, it->i, lhsMax);
        mina(midMin, it->i + lhsMax);
        maxa(lhsMax, lhs.sfx[it->v]);
    }

    // debug(pfxMax, sfxMax, lhs.best, rhs.best);
    seg[i].best = min(pfxMax, min(sfxMax, min(lhs.best, min(rhs.best, midMin))));
}

// init seg
void build(int i, int l, int r) {
    auto &node = seg[i];
    if (l == r) {
        memset(node.pfx, 0x3f, sizeof node.pfx);
        memset(node.sfx, 0x3f, sizeof node.sfx);
        node.pfx[arr[l]] = node.sfx[arr[l]] = 1;
        sortedInsert(node.firsts, {1, arr[l]});
        node.best = k == 1 ? 1 : INF;
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid); build(i << 1 | 1, mid + 1, r);

    // debug(i, l, r);
    Forincj(1, k) {
        node.pfx[j] = Index.first(j, l, r) - l + 1;
        node.sfx[j] = r - Index.last(j, l, r) + 1;
        if (node.pfx[j] <= n) sortedInsert(node.firsts, {node.pfx[j], j});
    }
    mergeSeg(i, l, r);
}

void upd(int i, int l, int r, int q, int v) {
    if (l > q || r < q) return;
    seg[i].changeNum(l, r, arr[q], v); // assumes index struct has been updated
    if (l == q && r == q) return;

    // debug(l, r);
    int mid = (l + r) >> 1;
    upd(i << 1, l, mid, q, v); upd(i << 1 | 1, mid + 1, r, q, v);
    mergeSeg(i, l, r);
}

void stressTest() {
    const int N = 100000, Q = 100000, K = 50;
    mt19937 rng(time(NULL));
    uniform_int_distribution<int> disI(1, N), disV(1, K);

    Forinci(1, N) {
        int x = disV(rng);
        Index.add(i, x);
        arr[i] = x;
    }
    build(1, 1, N);

    Fori(0, Q) {
        int q = disI(rng), x = disV(rng);
        Index.remove(q, arr[q]);
        Index.add(q, x);
        upd(1, 1, N, q, x);
        arr[q] = x;
    }

    println("Done!");
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // stressTest();

    scan(n, k, Q);
    Forinci(1, n) {
        int x; scan(x);
        Index.add(i, x);
        arr[i] = x;
    }
    build(1, 1, n);

    while (Q--) {
        int type; scan(type);
        // debug('Q', type);

        if (type == 1) {
            int q, x; scan(q, x);

            Index.remove(q, arr[q]);
            Index.add(q, x);
            upd(1, 1, n, q, x);
            arr[q] = x;
        }
        else {
            int ans = seg[1].best;
            println(ans > n ? -1 : ans);
        }
    }

    return 0;
}
