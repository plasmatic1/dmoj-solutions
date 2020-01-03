#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"

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

using namespace std::chrono;
ll timeMs() { return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count(); }

/*
N -> Time
K -> NapTime

N  / K
10 / 1 ->  10
10 / 2 ->  5
10 / 3 ->  3
10 / 4 ->  2
10 / 5 ->  2
10 / 6 ->  1
10 / 7 ->  1
10 / 8 ->  1
10 / 9 ->  1
10 / 10 -> 1

N=10, K=4, go to next:

Go from (N/K) to (N/K)-1 (such that K is maximized)
N/(N/K - 1) -> i.e. 10/1

Go from (N/K) to (N/K)-1 (such that K is minimised)
N/(N/K) + 1 -> i.e. 10/1
*/

// wesley <3 thank you
template <class T, class Comparator = less<uint32_t>> struct RadixHeap {
    Comparator cmp; int n; uint32_t last; vector<pair<uint32_t, T>> x[33];
    int bsr(uint32_t a) { return a ? 31 - __builtin_clz(a) : -1; }
    void aux(const pair<uint32_t, T> &p) { x[bsr(p.first ^ last) + 1].push_back(p); }
    RadixHeap() : n(0), last(0) {}
    bool empty() const { return 0 == n; }
    int size() const { return n; }
    pair<uint32_t, T> top() {
        assert(n > 0);
        if (x[0].empty()) {
            int i = 1;
            while (x[i].empty()) ++i;
            last = x[i][0].first;
            for (int j = 1; j < int(x[i].size()); j++) if (cmp(last, x[i][j].first)) last = x[i][j].first;
            for (auto &&p : x[i]) aux(p);
            x[i].clear();
        }
        return x[0].back();
    }
    void pop() { assert(n > 0); top(); n--; x[0].pop_back(); }
    void push(uint32_t key, const T &value) { n++; aux(make_pair(key, value)); }
};

struct p {
    int i, time; bool pushNew;
    Cmplt(p) { return time > o.time; }
};

struct pp {
    int i; bool pushNew;
};

const int MK = 5e4 + 10;
int n, m, k,
    times[MK], vals[MK], curNapCount[MK];

// priority_queue<p> pq;
RadixHeap<pp, greater<int>> pq;

__attribute__((optimize("-O3"))) int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll st = timeMs();
    scan(n, m, k);

    repi(0, m)
        scan(times[i]);
    times[m++] = n + 1;
    sort(times, times + m);
    
    int last = 0;
    repi(0, m) {
        vals[i] = times[i] - 1 - last;
        last = times[i];
    }

    // setup PQ and array
    repi(0, m) {
        curNapCount[i] = vals[i];
        pq.push(2, {i, true});
        // dblb("push"); db(i); dbln;
    }

    // count
    ll napCount = n - m + 1, best = min(m - 1, k);
    // int its = 500;
    while (!pq.empty()) {
        int time = -1;
        do {
            // assert(its--);
            auto ttp = pq.top(); pq.pop();
            auto &tp = ttp.second;

            // set time
            if (time == -1) time = ttp.first; 
            // dblb("upd"); db(tp.i); db(vals[tp.i]); db(curNapCount[tp.i]); db(vals[tp.i] / time); dbln;

            // set new dif
            ll newCount = vals[tp.i] / time, dif = curNapCount[tp.i] - newCount;
            curNapCount[tp.i] = newCount;
            napCount -= dif;
            
            // push only is val isnt 0
            if (tp.pushNew) {
                if (newCount > 1) {
                    int newTimeR = vals[tp.i] / (newCount - 1), newTimeL = vals[tp.i] / newCount + 1;
                    if (newTimeR == time)
                        pq.push(time + 1, {tp.i, true});
                    else {
                        pq.push(newTimeL, {tp.i, true});
                        pq.push(newTimeR, {tp.i, false});
                    }
                }
                else if (newCount == 1)
                    pq.push(vals[tp.i] + 1, {tp.i, false});
            }
        } while (!pq.empty() && pq.top().first == time);

        // dblb("calc time"); db(time); db(napCount); db(min(napCount, (ll)k) * time); dbln;
        maxa(best, min(napCount, (ll)k) * time);
    }

    println(best);
    ll en = timeMs();
    if (en - st > 1000) println("elapsed:", en - st);

    return 0;
}
