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

// thanks geeksforgeeks
ll fastMul(ll x, ll y, ll mod) {
    if (!y) return 0LL;
    return (x * (y & 1) + fastMul((x + x) % mod, y >> 1, mod)) % mod;
}
ll fastPow(ll x, ll y, ll mod) {
    if (!y) return 1LL;
    return fastMul((y & 1 ? x : 1), fastPow(fastMul(x, x, mod), y >> 1, mod), mod);
}

const int TEST = 50;

ll n;
mt19937_64 mt(time(NULL));

bool isp(ll x) {
    if (x <= 3) return x == 2 || x == 3;

    uniform_int_distribution<ll> dis(2LL, x);
    for (int i = 0; i < TEST; i++) {
        ll test = dis(mt);
        if (test == x) {
            i--;
            continue;
        }
        // ll fpv = fastPow(test, x, x); debug(x, test, fpv);
        if (fastPow(test, x - 1, x) != 1)
            return false;
    }
    return true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);
    if (n < 2) n = 2;

    while (true) {
        if (isp(n)) {
            cout << n << "\n";
            return 0;
        }
        n++;
    }

    return 0;
}