#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printDebug(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
inline void println(){cout<<"\n";}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

struct rect {
    int i, a, b, c, d;
};

namespace solver {
    struct p {
        int w, xBot, xTop;
    };

    struct CmpFW {
        bool operator()(const p &a, const p &b) {
            return a.w > b.w;
        }
    };

    struct CmpBW {
        bool operator()(const p &a, const p &b) {
            return a.w < b.w;
        }
    };

    #define MKCMP(name) bool name(const rect &a, const rect &b)
    MKCMP(cmpa) { return a.a < b.a; }
    MKCMP(cmpb) { return a.b < b.b; }
    MKCMP(cmpc) { return a.c < b.c; }
    MKCMP(cmpd) { return a.d < b.d; }

    const int MN = 1e6 + 1;
    int n, 
        bit1[MN], bit2[MN];
    ll tot = 0,
        cnt[MN];
    rect sortByA[MN], sortByB[MN], sortByC[MN], sortByD[MN];

    int qu(int bit[MN], int x) {
        int sum = 0;
        for (; x; x -= x & -x)
            sum += bit[x];
        return sum;
    }

    void add(int bit[MN], int x, int v) {
        for (; x < MN; x += x & -x)
            bit[x] += v;
    }

#define BEG(arr) (arr + 1)
#define END(arr) (arr + n + 1)
#define ALL(arr) BEG(arr), END(arr)

    void solve(vector<rect> &v, ostream& out) {
        n = v.size();

        memset(cnt, 0, sizeof cnt);

        // Make it 1-indexed
        v.insert(v.begin(), {-1, -1, -1, -1});

        copy(v.begin(), v.end(), sortByA);
        copy(v.begin(), v.end(), sortByB);
        copy(v.begin(), v.end(), sortByC);
        copy(v.begin(), v.end(), sortByD);
        sort(ALL(sortByA), cmpa);
        sort(ALL(sortByB), cmpb);
        sort(ALL(sortByC), cmpc);
        sort(ALL(sortByD), cmpd);

        // Do Bina ry Search
        for (int i = 1; i <= n; i++) {
            cnt[i] = n;
            cnt[i] -= END(sortByA) - lower_bound(ALL(sortByA), (rect){-1, v[i].c, -1, -1, -1}, cmpa);
            cnt[i] -= upper_bound(ALL(sortByC), (rect){-1, -1, -1, v[i].a, -1}, cmpc) - BEG(sortByC);
            cnt[i] -= END(sortByB) - lower_bound(ALL(sortByB), (rect){-1, -1, v[i].d, -1, -1}, cmpb);
            cnt[i] -= upper_bound(ALL(sortByD), (rect){-1, -1, -1, -1, v[i].b}, cmpd) - BEG(sortByD);

            // debug(i, v[i].a, v[i].b, v[i].c, v[i].d);
            // debug(i, END(sortByA) - lower_bound(ALL(sortByA), (rect){-1, v[i].c, -1, -1, -1}, cmpa));
            // debug(i, upper_bound(ALL(sortByC), (rect){-1, -1, -1, v[i].a, -1}, cmpc)->c, upper_bound(ALL(sortByC), (rect){-1, -1, -1, v[i].a, -1}, cmpc) - BEG(sortByC));
            // debug(i, END(sortByB) - lower_bound(ALL(sortByB), (rect){-1, -1, v[i].d, -1, -1}, cmpb));
            // debug(i, upper_bound(ALL(sortByD), (rect){-1, -1, -1, -1, v[i].b}, cmpd) - BEG(sortByD));
        }

        // printDebug(cnt + 1, n);

        // BIT of bottom left and top left
        memset(bit1, 0, sizeof bit1);
        memset(bit2, 0, sizeof bit2);
        
        priority_queue<p, vec<p>, CmpFW> pq;
        for (int i = 1; i <= n; i++) {
            pq.push({v[i].c, v[i].b, v[i].d});
        }

        for (int i = 1; i <= n; i++) {
            while (!pq.empty() && pq.top().w <= sortByA[i].a) {
                add(bit1, pq.top().xBot, 1);
                add(bit2, pq.top().xTop, 1);
                pq.pop();
            }

            // debug(i, sortByA[i].i, sortByA[i].d);
            // debug(i, qu(bit1, MN), qu(bit1, sortByA[i].d - 1));
            cnt[sortByA[i].i] += qu(bit1, MN - 1) - qu(bit1, sortByA[i].d - 1);
            cnt[sortByA[i].i] += qu(bit2, sortByA[i].b);
        }

        // BIT of bottom right and top right
        memset(bit1, 0, sizeof bit1);
        memset(bit2, 0, sizeof bit2);

        priority_queue<p, vec<p>, CmpBW> pq2;
        for (int i = 1; i <= n; i++) {
            pq2.push({v[i].a, v[i].b, v[i].d});
        }

        for (int i = n; i >= 1; i--) {
            while (!pq2.empty() && pq2.top().w >= sortByC[i].c) {
                add(bit1, pq2.top().xBot, 1);
                add(bit2, pq2.top().xTop, 1);
                pq2.pop();
            }

            cnt[sortByC[i].i] += qu(bit1, MN - 1) - qu(bit1, sortByC[i].d - 1);
            cnt[sortByC[i].i] += qu(bit2, sortByC[i].b);
        }

        // sum up totals
        // printDebug(cnt + 1, n);

        tot = 0;
        for (int i = 1; i <= n; i++)
            tot += cnt[i] - 1;
        assert(tot % 2 == 0);
        out << (tot >> 1) << "\n";
    }
}

int n;
vector<rect> v;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);
    v.resize(n);

    for (int i = 0; i < n; i++) {
        scan(v[i].a, v[i].b, v[i].c, v[i].d);
        v[i].i = i + 1;
    }

    solver::solve(v, cout);

    return 0;
}
