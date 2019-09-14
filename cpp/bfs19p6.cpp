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

const int MN = 1e5 + 1, P = 21 + 1, MP = 1 << 21;
int n,
    arr[MN], cnt[2][MP], best[P];
vi primes;

bool isp(int x) {
    int sqx = sqrt(x);
    for (int i = 2; i <= sqx; i++)
        if (x % i == 0)
            return false;
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 2; i <= 75; i++)
        if (isp(i))
            primes.pb(i);

    for (int i = 0; i < n; i++) {
        scan(arr[i]);

        int bitm = 0;
        for (int p : primes) {
            bitm <<= 1;
            if (arr[i] % p == 0)
                bitm |= 1;
        }

        cnt[0][bitm]++;
        // for (int i = 0; i < P; i++)
        //     cnt[i][bitm]++;
        // for (int j = bitm; j < MP; j = (j + 1) | bitm) {
        //     cnt[j]++;
        // }
    }

    int prev = 0, cur = 1;

    // Do SOS DP
    for (int i = 1; i < P; i++) {
        for (int j = 0; j < MP; j++) {
            cnt[cur][j] = cnt[prev][j];
            if ((j >> (i - 1)) & 1) {
                cnt[cur][j] += cnt[prev][j ^ (1 << (i - 1))];
            }
        }

        prev ^= 1;
        cur ^= 1;
    }

    // Calculate bests for each K
    for (int i = 1; i < MP; i++) {
        maxa(best[__builtin_popcount(i)], cnt[prev][i]);
    }

    // printDebug(best, P);

    int last = 0;
    for (int i = 1; i < P; i++) {
        for (int j = last + 1; j <= best[i]; j++)
            print(i, ' ');
        last = best[i];
    }
    print('\n');

    return 0;
}