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

namespace Solver {
    struct Qu {
        char t;

        // update
        int x; char c;

        // query
        string s;
    };

    const int MN = 1e5 + 10;
    int mp[MN], nxt[MN][26];

    vector<int> solve(string &S, int Q, vector<Qu> &qus) {
        // reset and init
        memset(mp, -1, sizeof mp);
        memset(nxt, -1, sizeof nxt);
        vector<int> ans;

        int N = S.length(), clen = 1;
        for (int i = 0; i < Q; i++) {
            auto q = qus[i];
            if (q.t == 'C') {
                clen++;
                int cc = q.c - 'a', actual = mp[q.x] == -1 ? q.x : mp[q.x];
                if (nxt[actual][cc] != -1) {
                    mp[clen] = nxt[actual][cc];
                }
                else {
                    nxt[actual][cc] = clen;
                }
            }
            else {
                string &s = q.s;
                int slen = s.length();

                if (s[0] != S[0]) {
                    ans.pb(-1);
                    continue;
                }

                // dblb("Q"); db(s); dbln;

                // check S
                bool first = slen <= N;
                for (int j = 0; j < slen; j++) {
                    if (j >= N) { break; }
                    // db(j); db(first); db(s[j]); db(S[j]); dbln;
                    if (s[j] != S[j]) { first = true; break; }
                }

                if (first)
                    ans.pb(1);
                else {
                    int ptr = N, pre = 1, cc = s[ptr] - 'a';
                    // db(ptr); db(s[ptr]); db(pre); db(cc); db(nxt[pre][cc]); dbln;
                    while (ptr < slen && nxt[pre][cc] != -1) {
                        pre = nxt[pre][cc];
                        ptr++;
                        if (ptr < slen)
                            cc = s[ptr] - 'a';
                    }

                    ans.pb(pre);
                }
            }
        }

        return ans;
    }
};

string s;
int q;
vector<Solver::Qu> qq;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    scan(s, q);
    repi(0, q) {
        char t;
        scan(t);
        if (t == 'C') {
            int x; char c;
            scan(x, c);
            qq.pb({t, x, c, ""});
        }
        else {
            string s;
            scan(s);
            qq.pb({t, -1, 'A', s});
        }
    }
    
    auto ans = Solver::solve(s, q, qq);
    for (auto x : ans)
        println(x);

    return 0;
}