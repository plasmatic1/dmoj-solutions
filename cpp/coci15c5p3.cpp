#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 100001, MK = 51, MOD = 1000000007;
int n, k, buf;
map<int, int> cnts;
ll facts[MAX]; // factorials

inline ll fastPow(ll x, ll y) { // (x ** y) mod M
    ll ans = 1;
    for (ll bit = 1, cpow = x; bit <= y; bit <<= 1, cpow = (cpow * cpow) % MOD) 
        if (y & bit)
            ans = (ans * cpow) % MOD;
    return ans;
}

inline ll divMod(ll x, ll y) { // (x / y) mod M
    return (x * fastPow(y, MOD - 2)) % MOD;
}

inline ll choose(ll n, ll r) { // (nCr) mod M
    if(r == 0 || n == r) return 1;
    return divMod(facts[n], (facts[r] * facts[n - r]) % MOD);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n, k);

    facts[1] = 1;
    for (int i = 2; i <= n; i++)
        facts[i] = (facts[i - 1] * i) % MOD;

    for (int i = 0; i < n; i++) {
        scan(buf);
        cnts[buf]++;
    }

    int curCnt = 0;
    ll tot = 0;
    for (pair<int, int> p : cnts) {
        for (int i = 1; i <= p.second; i++) {
            curCnt++;
            if (curCnt < k)
                continue;
            
            tot = (tot + (choose(curCnt - 1, k - 1) * p.first)) % MOD;
            // debug(curCnt, k, p.first, p.second, tot);
        }
    }
    printf("%lld\n", tot);

    return 0;
}