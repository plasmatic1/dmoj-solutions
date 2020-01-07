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

struct p {
    int bx, by, ex, ey;
};

const int MN = 15 + 1;
int n, rs, cs, re, ce, // starting cells, ending cells
    dis[MN][MN][MN][MN];
deque<p> dq;
vec<p> adjs;

void makeAdj(p &c) {
    int bx = c.bx, by = c.by, ex = c.ex, ey = c.ey;
    adjs.clear();

    // moving ball
    if ((ex == bx - 1 || ex == bx + 1) && ey == by) // move right/left
        adjs.pb({ex, ey, bx, by});
    if ((ey == by - 1 || ey == by + 1) && ex == bx) // move up/down
        adjs.pb({ex, ey, bx, by});
    
    // moving empty cell
    if (ex < n && !(ex + 1 == bx && ey == by)) // move right
        adjs.pb({bx, by, ex + 1, ey});
    if (ex > 1 && !(ex - 1 == bx && ey == by)) // move right
        adjs.pb({bx, by, ex - 1, ey});
    if (ey < n && !(ey + 1 == by && ex == bx)) // move up
        adjs.pb({bx, by, ex, ey + 1});
    if (ey > 1 && !(ey - 1 == by && ex == bx)) // move down
        adjs.pb({bx, by, ex, ey - 1});
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, rs, cs, re, ce);

    int oex, oey;
    repi(0, 2) {
        scn(int, x, y);
        if (x != rs || y != cs) { // other empty cell
            oex = x;
            oey = y;
        }
    }

    // bfs
    memset(dis, 0x3f, sizeof dis);
    dis[rs][cs][oex][oey] = 0;
    dq.pb({rs, cs, oex, oey});
    while (!dq.empty()) {
        p cur = dq.front(); dq.pop_front();
        int curDis = dis[cur.bx][cur.by][cur.ex][cur.ey];
        // db(cur.bx); db(cur.by); db(cur.ex); db(cur.ey); db(curDis); dbln;

        makeAdj(cur);
        for (p adj : adjs) {
            // dblb("adj"); db(adj.bx); db(adj.by); db(adj.ex); db(adj.ey); dbln;
            int &altDis = dis[adj.bx][adj.by][adj.ex][adj.ey];
            if (altDis == INF) {
                altDis = curDis + 1;
                dq.pb(adj);
            }
        }
    }

    // best
    int best = INF;
    repi(1, n + 1) {
        repj(1, n + 1) {
            mina(best, dis[re][ce][i][j]); // doesnt matter empty spot loc
        }
    }
    println(best);

    return 0;
}
