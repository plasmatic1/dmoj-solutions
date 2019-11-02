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

struct seg {
    int l, r, v;
    Cmplt(seg) { return r < o.r; }
};

const int MN = 1e5 + 1;
int n, q,
    arr[MN];
set<seg> segs;
multiset<int> tots;

inline void removeSeg(set<seg>::iterator s) {
    segs.erase(s);
    tots.erase(tots.find(s->v));
}

inline void insertSeg(seg s) {
    segs.insert(s);
    tots.insert(s.v);
}

// segtree
int segtree[MN << 2];

int _query(int i, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (l >= ql && r <= qr) return segtree[i];
    int mid = (l + r) >> 1;
    return _query(i << 1, l, mid, ql, qr) | _query(i << 1 | 1, mid + 1, r, ql, qr);
}

int _update(int i, int l, int r, int q, int v) {
    if (q > r || q < l) return segtree[i];
    if (l == q && r == q) return segtree[i] = v;
    int mid = (l + r) >> 1;
    return segtree[i] = _update(i << 1, l, mid, q, v) | _update(i << 1 | 1, mid + 1, r, q, v);
}

#define query(l, r) _query(1, 1, n, l, r)
#define update(q, v) _update(1, 1, n, q, v)

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);

    segs.insert({-1, -1, 0});
    segs.insert({n + 2, n + 2, 0});
    Forinci(1, n) {
        scan(arr[i]);
        update(i, arr[i]);
    }

    int cumOr = 0, start = 1;
    Forinci(1, n) {
        if (arr[i] >= 0) {
            cumOr |= arr[i];
            if (arr[i + 1] < 0 || i == n) { // last one
                insertSeg({start, i, cumOr});
                cumOr = 0;
            }
        }
        else
            start = i + 1;
    }

    while (q--) {
        int i, x; scan(i, x);

        // Update seg
        update(i, x);

        if (arr[i] < 0) {
            if (x >= 0) { // Join segments
                auto rhs = segs.lower_bound({-1, i, -1}), lhs = rhs; lhs--;

                seg toadd = {i, i, x};

                if (lhs->r + 1 == i) {
                    toadd.l = lhs->l;
                    toadd.v |= lhs->v;
                    removeSeg(lhs);
                }

                if (rhs->l - 1 == i) {
                    toadd.r = rhs->r;
                    toadd.v |= rhs->v;
                    removeSeg(rhs);
                }

                insertSeg(toadd);
            } // otherwise do nothing
        }
        else {
            if (x >= 0) { // Augment current seg
                auto cseg = segs.lower_bound({-1, i, -1});
                seg toadd = {cseg->l, cseg->r, query(cseg->l, cseg->r)};
                removeSeg(cseg);
                insertSeg(toadd);
            }
            else { // Split 2 segs
                auto cseg = segs.lower_bound({-1, i, -1});
                seg toadd1 = {cseg->l, i - 1, query(cseg->l, i - 1)},
                    toadd2 = {i + 1, cseg->r, query(i + 1, cseg->r)};
                removeSeg(cseg); 
                if (toadd1.l <= toadd1.r) insertSeg(toadd1);
                if (toadd2.l <= toadd2.r) insertSeg(toadd2);
            }
        }

        // debug(i);
        // for (auto s : segs)
        //     debug(s.l, s.r, s.v);

        // update vals and arr[i]
        arr[i] = x;

        // Output
        if (!tots.empty())
            println(*(--tots.end()));
        else
            println(query(1, n));
    }

    return 0;
}
