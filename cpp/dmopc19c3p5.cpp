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

const int MN = 3e5 + 1;
int n, q;
ll v[MN];

// const int BLK = 420; // blaze it
const int BLK = 1; // haha oops
const int MVRNG = 4e5 + 15;
ll D = 0, totadj = 0;
ll mx = -LLINF, mn = LLINF;
ll modcnt[BLK][BLK], modshift[BLK];

struct {
    ll bit[MVRNG];

    inline ll tind(ll l) {
        // dblb("tind"); db(l);
        l += D;
        mina(l, MVRNG - 1LL);
        maxa(l, 1LL);
        // db(l); dbln;
        return l;
    }

    inline ll sum(ll x) {
        x = tind(x);
        ll sum = 0;
        for (; x; x -= x & -x)
            sum += bit[x];
        return sum;
    }

    inline void add(ll x, ll v) {
        x = tind(x);
        for (; x < MVRNG; x += x & -x)
            bit[x] += v;
    }

    ll rsq(ll l, ll r) {
        return sum(r) - sum(l - 1);
    }
} bit, bitcnt;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);

    repi(1, n + 1) {
        scan(v[i]);
        mina(mn, v[i]);
        maxa(mx, v[i]);
    }
    D = -mn + 200000 + 3;

    // pfx sum array
    repi(1, n + 1) {
        bit.add(v[i], v[i]);
        bitcnt.add(v[i], 1);
    }

    // sqrt lul
    repi(1, BLK) {
        repj(1, n + 1) {
            modcnt[i][v[j] % i]++;
        }
    }

    while (q--) {
        int t; ll x;
        scan(t, x);

        if (t == 1) {
            bit.add(x, x - totadj);
            bitcnt.add(x, 1);
            maxa(mx, x);
            mina(mn, x);

            repi(1, BLK)
                modcnt[i][(x + modshift[i]) % i]++;
        }
        else if (t == 2) {
            D -= x; // modify D
            totadj += x;
            mn += x;
            mx += x;

            repi(1, BLK) {
                modshift[i] = (modshift[i] - x) % i + i;
                while (modshift[i] >= i) modshift[i] -= i;
            }
        }
        else {
            // db(t);
            // db(x);
            // dbarr(v + 1, n);
            // dbln;

            if (x < BLK) {
                ll tot = 0;
                repi(0, x) {
                    ll mind = min((ll)i, x - i);
                    tot += mind * modcnt[x][(i + modshift[x]) % x];
                }
                println(tot);
            }
            else if (x >= BLK) {
                ll st = (mn / x) * x;
                while (st > mn) st -= x; // if mn is negative

                ll lreach = x / 2, rreach = x / 2;
                if (x % 2 == 0) rreach--;

                // db(lreach);
                // db(rreach);
                // dbln;
                // db(bitcnt.sum(3));
                // db(bit.sum(3));
                // dbln;

                ll tot = 0;
                for (; st <= mx + x; st += x) {
                    // db(st);
                    // db(bitcnt.rsq(st - lreach, st));
                    // if (rreach > 0)
                    //     db(bitcnt.rsq(st + 1, st + rreach));
                    // dbln;

                    // smaller than or equal
                    ll cntrsq = bitcnt.rsq(st - lreach, st);
                    tot += st * cntrsq - (bit.rsq(st - lreach, st) + cntrsq * totadj);
                    // greater than
                    if (rreach > 0) {
                        cntrsq = bitcnt.rsq(st + 1, st + rreach);
                        tot += (bit.rsq(st + 1, st + rreach) + cntrsq * totadj) - st * cntrsq;
                    }
                }

                println(tot);
            }
        }
    }

    return 0;
}
