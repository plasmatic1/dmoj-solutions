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

const int MN = 1e5 + 1, B = 50;
int N, Q;
ll S,
    val[MN];

// SQRT
struct Block {
    int L, R;
    vec<ll> psum;
    vec<pair<int, ll>> jmp;
};

vec<Block*> blocks;
int bid[MN];

void brute(int &cnt, ll &rem, int L, int R) {
    repi(L, R + 1) {
        // db(i); db(L); db(R); db(rem); db(cnt); db(val[i]); db(S); dbln;
        if (rem + val[i] > S) {
            rem = val[i];
            cnt++;
        }
        else
            rem += val[i];
    }
}

void recalc(Block *b) {
    int sz = b->R - b->L + 1;
    // db(b->L); db(b->R); db(sz); dbln;
    b->jmp.resize(sz);
    b->psum.resize(sz);
    partial_sum(val + b->L, val + b->R + 1, b->psum.begin());
    repi(0, sz) {
        int st = b->L + i;
        ll rem = 0; int cnt = 0;
        brute(cnt, rem, st, b->R);
        b->jmp[i] = {cnt, rem};
    }
}

// RMQ 
int seg[MN << 2];
int query(int i, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return -INF;
    if (l >= ql && r <= qr) return seg[i];
    int mid = (l + r) >> 1;
    return max(query(i << 1, l, mid, ql, qr), query(i << 1 | 1, mid + 1, r, ql, qr));
}
int update(int i, int l, int r, int q, int v) {
    if (l > q || r < q) return seg[i];
    if (l == q && r == q) return seg[i] = v;
    int mid = (l + r) >> 1;
    return seg[i] = max(update(i << 1, l, mid, q, v), update(i << 1 | 1, mid + 1, r, q, v));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(N, Q, S);
    repi(1, N + 1) {
        scan(val[i]);
        bid[i] = i / B;
        update(1, 1, N, i, val[i]);
    }

    // build
    repi(1, N + 1) {
        if ((int)bid[i] >= blocks.size()) {
            Block *b = new Block;
            b->L = b->R = i;
            blocks.pb(b);
        }
        else
            maxa(blocks[bid[i]]->R, i);
    }
    for (auto &b : blocks)
        recalc(b);
    

    // answer queries
    while (Q--) {
        char T; int a, b;
        scan(T, a, b);

        if (T == 'U') {
            val[a] = b;
            recalc(blocks[bid[a]]);
            update(1, 1, N, a, b);
        }
        else {
            // invalid
            bool bad = query(1, 1, N, a, b) > S;
            if (bad) {
                println(-1);
                continue;
            }

            assert(1 <= a && a <= N);
            assert(1 <= b && b <= N);
            assert(a <= b);

            // brute force and sqrt
            int bl = bid[a], br = bid[b];
            // db(a); db(b); db(bl); db(br); dbln;
            int cnt = 0; ll rem = 0;
            if (bl == br)
                brute(cnt, rem, a, b);
            else {
                brute(cnt, rem, a, blocks[bl]->R);
                repi(bl + 1, br) {
                    Block *b = blocks[i];
                    int idx = upper_bound(all(b->psum), S - rem) - b->psum.begin();
                    if (idx < (int)b->psum.size()) {
                        cnt += 1 + b->jmp[idx].first;
                        rem = b->jmp[idx].second;
                    }
                    else {
                        rem += b->psum.back();
                    }
                }
                brute(cnt, rem, blocks[br]->L, b);
            }

            // print answer
            // db(Q); db(rem); db(cnt); db(a); db(b); dbln;
            if (rem > 0) cnt++;
            println(cnt);
        }
    }

    return 0;
}