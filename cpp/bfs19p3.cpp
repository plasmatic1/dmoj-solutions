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

const int MN = 1e5 + 1, MN2 = MN << 2;
int n, l, k;
mp<char, int> cnts;
string s;
ll bit1[MN2], bit2[MN2]; // cnt, sum

void add(ll bit[], int x, ll v) {
    // debug(x);
    for (; x < MN2; x += x & -x)
        bit[x] += v;
}

ll sum(ll bit[], int x) {
    ll sum = 0;
    for (; x; x -= x & -x)
        sum += bit[x];
    return sum;
}

const int LG = 20;

// Search for last index which is less than amt
int search(ll amt) {
    int idx = 0;
    ll camt = 0;
    for (int pow = 1 << LG; pow > 0; pow >>= 1) {
        int altIdx = idx | pow;
        if (altIdx < MN2 && camt + bit1[altIdx] < amt) {
            idx = altIdx;
            camt += bit1[altIdx];
        }
    }

    return idx;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s, l, k);
    n = s.length();
    s = " " + s;

    if (l + k >= n) {
        println(0);
        return 0;
    }

    ll best = LLINF;

    // Add all the counts
    for (int i = l + 1; i <= n; i++) {
        char c = s[i];
        int inc = ++cnts[c];
        inc = (inc << 1) - 1;
        add(bit1, inc, 1);
        add(bit2, inc, inc);
    }

    for (int i = l + 1; i <= n + 1; i++) {
        // Remove the one now used by L (i-1), Add the new one introduced by L (i-L-1)
        if (i > l + 1) {
            int inc = (cnts[s[i - 1]] << 1) - 1;
            add(bit1, inc, -1);
            add(bit2, inc, -inc);
            cnts[s[i - 1]]--;

            inc = ((++cnts[s[i - l - 1]]) << 1) - 1;
            add(bit1, inc, 1);
            add(bit2, inc, inc);
            // cnts[s[i - l - 1]]++;
        }

        // Preform bit search
        ll allowCnt = n - l - k;
        int idx = search(allowCnt);
        // debug(allowCnt, i, idx);

        // 
        ll cans = sum(bit2, idx);
        cans += (ll)(idx + 1) * (allowCnt - sum(bit1, idx));

        mina(best, cans);
    }

    println(best);

    return 0;
}
