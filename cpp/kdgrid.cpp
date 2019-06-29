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

template <ll MOD>
struct FastPow {
    ll fastPow(ll x, ll y, ll ans = 1) {
        for (ll mag = 1, cpow = x; mag <= y; mag <<= 1, cpow = (cpow * cpow) % MOD)
            if (y & mag) ans = (ans * cpow) % MOD;
        return ans;
    }
    ll divMod(ll x, ll y) { return (x * fastPow(y, MOD - 2)) % MOD; }
};

const int MAX = 21, MF = 401, MOD = 1e9 + 7;
int w, n,
    len[MAX];
ll facts[MF];
FastPow<MOD> fp;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    scan(w, n);

    facts[0] = 1;
    for (int i = 1; i < MF; i++)
        facts[i] = (facts[i - 1] * i) % MOD;

    for (int i = 0; i < n; i++)
        scan(len[i]);

    int msub = 1 << n;
    for (int i = 0; i < msub; i++) {
        if (__builtin_popcount(i) < 2)
            continue;

        int dtot = 0;
        ll totDiv = 1;
        vector<int> ds;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                dtot += len[j];
                ds.push_back(len[j]);
                totDiv = (totDiv * facts[len[j]]) % MOD;
            }
        }

        // debug(i, dtot, ds);

        ll tot = fp.divMod(facts[dtot], totDiv);
        
        if (tot == w) {
            sort(ds.begin(), ds.end());
            cout << ds.size() << "\n";
            for (int d : ds)
                cout << d << " ";
            cout << "\n";

            return 0;
        }
    }

    cout << "-1\n";

    return 0;
}