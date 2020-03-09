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

namespace solver {
    using ll = long long; using ull = unsigned long long;
    using pii = pair<int, int>; using pll = pair<ll, ll>;
    template <typename T> using vec = vector<T>;
    using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
    // Shorthand Functions
    template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
    template<typename T> inline void mina(T& st, T v) { st = min(st, v); }

    const int MN = 2e3 + 1;
    int n, best = 0;
    set<pii> ptSet;

    void solve(int n, vpi &pts, ostream &out) {
        ptSet.clear();
        for (auto pt : pts)
            ptSet.insert(pt);
        
        // Solving problem
        int best = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                pii oth = mpr(pts[i].first, pts[j].second), 
                    oth2 = mpr(pts[j].first, pts[i].second);
            
                if (ptSet.find(oth) != ptSet.end() && ptSet.find(oth2) != ptSet.end()) {
                    maxa(best, abs(pts[j].first - pts[i].first) * abs(pts[j].second - pts[i].second));
                }
            }
        }
        out << best << '\n';
    }
}

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);

    int n;
    vpi pts;

    scan(n);
    pts.resize(n);
    
    assert(4 <= n && n <= 2000);

    for (int i = 0; i < n; i++) {
        scan(pts[i].first, pts[i].second);
        assert(-20000 <= pts[i].first && pts[i].first <= 20000);
        assert(-20000 <= pts[i].second && pts[i].second <= 20000);
    }

    solver::solve(n, pts, cout);

    return 0;
}