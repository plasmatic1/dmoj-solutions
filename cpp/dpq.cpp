#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

template <int MAX, typename T = int>
struct BIT {
    int n; T defaultV, tree[MAX];
    inline void merge(T& a, T& b){ a = max(a, b); };
    void init(int n0, T defaultV0) { n = n0; defaultV = defaultV0; }
    void upd(int x, T z){ // Adds value `z` to index `x`
        for(; x <= n; x += x & -x)
            merge(tree[x], z);
    }
    T query(int x){ // Queries index `x`
        T sum = defaultV;
        for(; x; x -= x & -x)
            merge(sum, tree[x]);
        return sum;
    }
    void reverseUpd(int x, T z) { upd(n - x + 1, z); }
    T reverseQuery(int x) { return query(n - x + 1); }
};

const int MAX = 2e5 + 1;
int n,
    a[MAX], h[MAX];
ll dp[MAX];
BIT<MAX, ll> bit;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    bit.init(n, 0);

    for (int i = 1; i <= n; i++)
        scan(h[i]);
    for (int i = 1; i <= n; i++)
        scan(a[i]);
    
    for (int i = 1; i <= n; i++) {
        dp[i] = bit.query(h[i] - 1) + a[i];
        bit.upd(h[i], dp[i]);
    }

    cout << *max_element(dp + 1, dp + n + 1) << "\n";

    return 0;
}