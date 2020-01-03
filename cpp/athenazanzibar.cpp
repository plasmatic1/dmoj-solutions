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

const int MN = 3e6 + 10;
// Correct solver
namespace solver {
    struct p {
        int i, v;
        bool operator<(const p &o) const {
            return v == o.v ? i < o.i : v < o.v;
        }
    };

    bool cmpUnique(const p &a, const p &b) {
        return a.v == b.v;
    }

    inline void setBest(int &best, int &besti, int &bestj, int alt, int i, int j) {
        if (alt < best) {
            best = alt;
            besti = i;
            bestj = j;
        }
        else if (alt == best && i < besti) {
            besti = i;
            bestj = j;
        }
        else if (alt == best && i == besti && j < bestj)
            bestj = j;
    }

    pair<int, pair<int, int>> solve(int n, p val[MN]) {
        if (n <= 1000000) // May not be sorted but only if small input
            sort(val, val + n);

        int best = 2000000001, besti = -1, bestj = -1;

        // two of same value
        for (int i = 0; i < n - 1; i++) {
            setBest(best, besti, bestj, abs(val[i].v + val[i + 1].v), val[i].i, val[i + 1].i);
        }

        // opposite sign
        n = unique(val, val + n, cmpUnique) - val;
        int rptr = n - 1;
        for (int i = 0; i < n; i++) {
            while (rptr > i && val[rptr].v > -val[i].v)
                rptr--;
            
            for (int j = rptr; j < rptr + 2; j++) {
                if (j <= i || j >= n) continue;
                int ci = val[i].i, cj = val[j].i;
                if (ci > cj) swap(ci, cj);

                int alt = abs(val[i].v + val[j].v);
                setBest(best, besti, bestj, alt, ci, cj);
            }
        }

        return make_pair(best, make_pair(besti + 1, bestj + 1));
    }
}

// Obselete solver to test index-based WA
// namespace solver {
//     struct p {
//         int i, v;
//         bool operator<(const p &o) const {
//             return v == o.v ? i < o.i : v < o.v;
//         }
//     };

//     pair<int, pair<int, int>> solve(int n, p val[MN]) {
//         if (n <= 1000000) // May not be sorted but only if small input
//             sort(val, val + n);

//         int best = 2000000001, besti = -1, bestj = -1, rptr = n - 1;
//         for (int i = 0; i < n; i++) {
//             while (rptr > i && val[rptr].v >= -val[i].v)
//                 rptr--;
            
//             int alta = abs(val[rptr].v + val[i].v), altb = abs(val[rptr + 1].v + val[i].v);
            
//             if (rptr > i && alta < best) {
//                 best = alta;
//                 besti = val[i].i;
//                 bestj = val[rptr].i;
//             }

//             if (rptr + 1 < n && altb < best) {
//                 best = altb;
//                 besti = val[i].i;
//                 bestj = val[rptr + 1].i;
//             }
//         }
        
//         if (besti > bestj)
//             swap(besti, bestj);

//         return make_pair(best, make_pair(besti + 1, bestj + 1));
//     }
// }

// Slow solver for case bashing
// namespace solver {
//     struct p {
//         int i, v;
//         bool operator<(const p &o) const {
//             return v == o.v ? i < o.i : v < o.v;
//         }
//     };

//     pair<int, pair<int, int>> solve(int n, p val[MN]) {
//         int best = 2000000001, besti = -1, bestj = -1, rptr = n - 1;
//         for (int i = 0; i < n; i++) {
//             for (int j = i + 1; j < n; j++) {
//                 int a = val[i].v, b = val[j].v;
//                 if (abs(a + b) < best) {
//                     best = abs(a + b);
//                     besti = i;
//                     bestj = j;
//                 }
//             }
//         }

//         return make_pair(best, make_pair(besti + 1, bestj + 1));
//     }
// }

int n;
solver::p val[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    repi(0, n) {
        int x; scan(x);
        val[i] = {i, x}; 
    }
    
    auto ans = solver::solve(n, val);
    println(ans.first);
    println(ans.second.first, ans.second.second);

    return 0;
}
