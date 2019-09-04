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

const int MN = (1 << 16) + 10, LG = 16;
int lgn, n, q, ba, bb,
    arr[MN];
vec<mp<int, int>> hasNum[LG];
mp<int, int> numCnts[LG];
multiset<int> cnts[LG];

inline void insert(int id, int x) {
    arr[id] = x;
    for (int i = 0; i < lgn; i++) {
        hasNum[i][id][x]++;
        if (hasNum[i][id][x] == 1) { // New #
            int toFind = numCnts[i][x]++;
            auto ptr = cnts[i].find(toFind);

            if (ptr != cnts[i].end())
                cnts[i].erase(ptr);
            cnts[i].insert(toFind + 1);
        }

        id >>= 1;
    }
}

inline void remove(int id) {
    int val = arr[id];
    for (int i = 0; i < lgn; i++) {
        hasNum[i][id][val]--;
        if (!hasNum[i][id][val]) {
            int toFind = numCnts[i][val]--;

            cnts[i].erase(cnts[i].find(toFind));
            cnts[i].insert(toFind - 1);
        }

        id >>= 1;
    }
}

inline void query() {
    for (int i = 0; i < lgn; i++) {
        int maxv = *(--cnts[i].end());
        if (maxv == 1 << (lgn - i)) {
            println(i);
            return;
        }
    }

    println(lgn);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(lgn, q);
    n = 1 << lgn;

    // Set up unordered sets
    for (int i = 0; i < lgn; i++) {
        hasNum[i].resize(1 << (lgn - i));
    }

    for (int i = 0; i < n; i++) {
        scan(ba);
        insert(i, ba);
    }

    query();

    for (int i = 0; i < q; i++) {
        scan(ba, bb);

        remove(ba);
        insert(ba, bb);

        query();
    }

    return 0;
}
