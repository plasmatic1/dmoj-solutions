#include <bits/stdc++.h>

using namespace std;

// typedef long long ll;
typedef unsigned long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

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

ll pa_, pb_;
void extEuclid(ll a, ll b){
    if (!b) { pa_ = 1; pb_ = 0; }
    else {
        extEuclid(b, a % b);
        ll tmp = pa_; pa_ = pb_; pb_ = tmp - a / b * pb_;
    }
}
ll modInv(ll x, ll mod) { extEuclid(x % mod, mod); return (pa_ + mod) % mod; }
ll divMod(ll x, ll y, ll mod) { return (x * modInv(y, mod)) % mod; }

ll n, m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    
    cout << modInv(n, m) << "\n";

    return 0;
}
