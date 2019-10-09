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

const string F0 = "Good writing is good writing is good writing.", 
    A = "Good writing is good ",
    B = " writing is good ",
    C = " is good writing.";

const int MN = 31;
ll n, k,
    lens[MN];

char getChar(int cn, int ck) {
    if (ck > lens[cn]) return '.';
    if (cn == 0) {
        return F0[ck - 1];
    }

    if (ck <= A.length()) {
        return A[ck - 1];
    }
    else if (ck <= A.length() + lens[cn - 1]) {
        return getChar(cn - 1, ck - A.length());
    }
    else if (ck <= A.length() + lens[cn - 1] + B.length()) {
        return B[ck - 1 - A.length() - lens[cn - 1]];
    }
    else if (ck <= A.length() + lens[cn - 1] + B.length() + lens[cn - 1]) {
        return getChar(cn - 1, ck - A.length() - lens[cn - 1] - B.length());
    }
    return C[ck - 1 - A.length() - lens[cn - 1] - B.length() - lens[cn - 1]];
}

void solve() {
    print(getChar(n, k), '\n');
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    lens[0] = F0.length();
    for (int i = 1; i < MN; i++)
        lens[i] = A.length() + lens[i - 1] + B.length() + lens[i - 1] + C.length();

    int t; scan(t);
    while (t--) {
        scan(n, k);
        solve();
    }

    return 0;
}