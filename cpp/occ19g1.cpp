/*
SOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOBSOB
B D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: S
O D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: O
S D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: B
B D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: S
O D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: O
S D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: B
B D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: S
O D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: O
S D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: B
B D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: S
O D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: O
S D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: B
B D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: S
O D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: O
S D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: B
B D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: S 
O D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: O
S D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: D: B
BOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOSBOS
*/

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

const int MN = 1e5 + 1, MK = 11;
int n, k,
    init[MK], skill[MK][MN];

#define debug(...) 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k);

    for (int i = 0; i < k; i++) {
        scan(init[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            scan(skill[j][i]);
        }
    }
    
    ll maxTot[k]; copy(init, init + k, maxTot);
    for (int i = 0; i < k; i++) {
        vi tots(skill[i], skill[i] + n);
        sort(tots.begin(), tots.end());
        for (int x : tots) {
            if (maxTot[i] >= x) {
                maxTot[i] += x;
            }
        }
    }

    vi usable;
    for (int i = 0; i < n; i++) {
        bool work = true;
        for (int j = 0; j < k; j++)
            work &= maxTot[j] >= skill[j][i];

        if (work)
            usable.pb(i);
    }

    // debug(usable);
    // printDebug(maxTot, k);

    int tot = 0;
    bool used[n + 1]; memset(used, 0, sizeof used);

    while (true) {
        bool foundA = false;
        for (int j : usable) {
            if (used[j]) {
                continue;
            }

            bool work = true;
            for (int l = 0; l < k; l++)
                work &= init[l] >= skill[l][j];

            foundA |= work;
            if (work) {
                for (int l = 0; l < k; l++)
                    init[l] += skill[l][j];
                
                tot++;
                used[j] = true;
            } 
        }

        if (!foundA)
            break;
    }

    // debug(work2);
    // println(work2.size());
    println(tot);

    return 0;
}