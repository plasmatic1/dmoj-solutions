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
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
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
#define db(x) cout << (#x) << ": " << x << ", "
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

struct rect {
    int x1, y1, x2, y2;
};

const int MN = 1e5 + 1, MX = 2e5 + 1;
int n, xSz, ySz;
ll ans[MN];
vi ranksx, ranksy;
rect rects[MN];

inline int rankx(int x) { return lower_bound(ranksx.begin(), ranksx.end(), x) - ranksx.begin() + 1; }
inline int ranky(int x) { return lower_bound(ranksy.begin(), ranksy.end(), x) - ranksy.begin() + 1; }

// range update bit 
ll bit1[MX], bit2[MX];
inline void _update(ll bit[MN], int x, ll v) { for (; x <= ySz; x += x & -x) bit[x] += v;}
inline ll _query(ll bit[MN], int x) { ll sum = 0; for (; x; x -= x & -x) sum += bit[x]; return sum; }
void update(int l, int r, ll v) {
    _update(bit1, l, v); _update(bit1, r + 1, -v);    
    _update(bit2, l, v * (l - 1)); _update(bit2, r + 1, -v * r);
}
ll query(int l, int r) {
    ll a = _query(bit1, r) * r - _query(bit1, l - 1) * (l - 1), b = _query(bit2, r) - _query(bit2, l - 1);
    return a - b;
}

// answer query
void ask(int i, rect &r) {
    if (!ans[i])
        ans[i] += query(r.y1, r.y2);
}

// CDQ on x dimension
void CDQ(int l, int r, vec<int> &events) {
    if (l > r || events.empty()) return;

    int mid = (l + r) >> 1;
    vec<int> lhs, rhs;

    // solve for all that completely surround range
    for (auto event : events) {
        auto &rect = rects[event];
        if (l >= rect.x1 && r <= rect.x2)
            ask(event, rect);
        update(rect.y1, rect.y2, 1);
    }
    for (auto event : events)
        update(rects[event].y1, rects[event].y2, -1);
 
    // solve for children
    if (l < r) {
        for (auto event : events) {
            auto &rect = rects[event];
            if (l >= rect.x1 && r <= rect.x2)
                update(rect.y1, rect.y2, 1);
            else {
                ask(event, rect);
                if (rect.x1 <= mid) lhs.pb(event);
                if (rect.x2 > mid) rhs.pb(event);
            }
        }
        for (auto event : events)
            if (l >= rects[event].x1 && r <= rects[event].x2) 
                update(rects[event].y1, rects[event].y2, -1);
        
        CDQ(l, mid, lhs); CDQ(mid + 1, r, rhs);
    } 
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    repi(0, n) {
        int x, y, a, b;
        scan(x, y, a, b);
        rects[i] = {x, y, x + a - 1, y + b - 1};

        ranksx.pb(rects[i].x1); ranksx.pb(rects[i].x2);
        ranksy.pb(rects[i].y1); ranksy.pb(rects[i].y2);
    }

    // Rank compression
    sort(ranksx.begin(), ranksx.end());
    ranksx.resize(unique(ranksx.begin(), ranksx.end()) - ranksx.begin());
    sort(ranksy.begin(), ranksy.end());
    ranksy.resize(unique(ranksy.begin(), ranksy.end()) - ranksy.begin());
    xSz = ranksx.size(); ySz = ranksy.size();

    // cdq
    vec<int> events;
    for (int i = n - 1; i >= 0; i--) {
        rects[i].x1 = rankx(rects[i].x1); rects[i].x2 = rankx(rects[i].x2);
        rects[i].y1 = ranky(rects[i].y1); rects[i].y2 = ranky(rects[i].y2);
        events.pb(i);
    }
    CDQ(1, xSz, events);

    // print
    repi(0, n)
        println(ans[i] == 0 ? "DA" : "NE");

    return 0;
}