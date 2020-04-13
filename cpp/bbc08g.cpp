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

ll madd(ll a, ll b, ll MOD) { return (a + b) % MOD; }
ll msub(ll a, ll b, ll MOD) { return (a - b + MOD) % MOD; }
ll mmul(ll a, ll b, ll MOD) { return (a * b) % MOD; }
ll fpow(ll x, ll y, ll MOD) {
    if (!y) return 1LL;
    return mmul(fpow(mmul(x, x, MOD), y >> 1, MOD), (y & 1) ? x : 1LL, MOD);
}
ll mdiv(ll x, ll y, ll MOD) { return mmul(x, fpow(y, MOD - 2, MOD), MOD); }

struct Ed {
    int v, d;
};

const int MN = 1e5 + 1, LG = 18, C = 2;
const ll BASE[C] = {131, 151}, MOD[C] = {1000000007, 1000000009};
int N, M;
vec<Ed> g[MN];

// Lca + hash stuff
int par[LG][MN], parDig[MN];
ll tb[LG][MN], pp[C][MN];
ll comb(ll a, ll b) { return (a << 32LL) | b; }
ll single(int dig) { return comb(dig + 1, dig + 1); } // hash out of single char
ll lo(ll a) { return a & 0xFFFFFFFF; }
ll hi(ll a) { return a >> 32LL; }
ll pushSingle(int baseIdx, ll h, int len, ll toPush) {
    return madd(mmul(h, pp[baseIdx][len], MOD[baseIdx]), toPush, MOD[baseIdx]);
}
ll push(ll h, int len, ll toPush) {
    return comb(pushSingle(0, lo(h), len, lo(toPush)), pushSingle(1, hi(h), len, hi(toPush)));
}
void init() {
    repi(0, C) {
        pp[i][0] = 1LL;
        repj(1, MN)
            pp[i][j] = mmul(pp[i][j - 1], BASE[i], MOD[i]);
    }
}
bool LCPCompare(int a, int b) { // returns whether a<b xd
    // dblb("lcpcompare"); db(a); db(b); 
    ll h1 = 0, h2 = 0;
    int amt = 0;
    reprev(i, LG - 1, -1) {
        int len = 1 << i;
        if (par[i][a] != -1 && par[i][b] != -1) {
            ll tmpH1 = push(h1, len, tb[i][a]), tmpH2 = push(h2, len, tb[i][b]);
            if (tmpH1 == tmpH2) {
                amt |= len;
                h1 = tmpH1;
                h2 = tmpH2;
                a = par[i][a];
                b = par[i][b];
            }
        }
    }
    // db(a); db(b); db(parDig[a]); db(parDig[b]); dbln;
    return parDig[a] < parDig[b];
}

queue<int> Q;
int dis[MN];

// more par stuff
int par0[MN], dis0[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, M);
    repi(0, M) {
        scn(int, a, b, d);
        g[a].pb({b, d});
        g[b].pb({a, d});
    }

    // init bfs
    init();
    memset(dis, -1, sizeof dis);
    memset(par, -1, sizeof par);
    memset(tb, -1, sizeof tb);

    // bfs
    Q.push(0);
    dis[0] = 1LL;
    while (!Q.empty()) {
        int c = Q.front(), ndis = dis[c] + 1; Q.pop();
        // db(c); db(ndis); db(par[0][c]); db(tb[0][c]); db(parDig[c]); dbln;

        // update LCA stuff on bfstree
        repi(1, LG) {
            int cpar = par[i - 1][c], jmp = 1 << (i - 1);
            if (cpar != -1 && par[i - 1][cpar] != -1) {
                par[i][c] = par[i - 1][cpar];
                tb[i][c] = push(tb[i - 1][c], jmp, tb[i - 1][cpar]);
            }
        }

        // go to adj
        for (auto to : g[c]) {
            if (dis[to.v] == -1) {
                dis[to.v] = ndis;
                par[0][to.v] = c;
                parDig[to.v] = to.d;
                tb[0][to.v] = single(to.d);
                Q.push(to.v);
            }
            else if (dis[to.v] == ndis) {
                if ((parDig[to.v] == to.d && LCPCompare(c, par[0][to.v])) ||
                    to.d < parDig[to.v]) { // LCP >= 1
                    par[0][to.v] = c;
                    parDig[to.v] = to.d;
                    tb[0][to.v] = single(to.d);
                    // don't push again
                }
            }
        }
    }

    // more par stuff
    memset(par0, -1, sizeof par0);
    memset(dis0, -1, sizeof dis0);
    Q.push(N - 1);
    dis0[N - 1] = 0;
    int best = N - 1;
    while (!Q.empty()) {
        int c = Q.front(); Q.pop();
        // dblb("vis2"); db(c); dbln;
        if (dis[c] < dis[best])
            best = c;
        else if (dis[c] == dis[best] && LCPCompare(c, best))
            best = c;

        for (auto to : g[c]) {
            if (to.d == 0 && dis0[to.v] == -1) {
                dis0[to.v] = dis0[c] + 1;
                Q.push(to.v);
                par0[to.v] = c;
            }
        }
    }

    // output
    int c = best;
    bool allZero = true;
    while (par[0][c] != -1) {
        allZero &= !parDig[c];
        if (parDig[c] || !allZero)
            print(parDig[c]);
        c = par[0][c];
    }
    if (allZero) print(0);
    print('\n');
    println(dis[best] + dis0[best]);
    c = best;
    vi ans;
    while (c != -1) {
        ans.pb(c);
        c = par[0][c];
    }
    reverse(all(ans));
    c = best;
    do {
        if (c == N - 1) break;
        c = par0[c];
        ans.pb(c);
    } while (c != N - 1);
    for (auto x : ans)
        print(x, ' ');
    print('\n');

    return 0;
}