#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

int n, t;
ll ans = 0;

ll sumTo(ll x) { return (x * (x + 1)) >> 1; }

ll bestPowerOfDuration(int to) {
    ll full = (ll)n * to, mainSub = sumTo((to - 1) >> 1) << 1;
    // debug(to, full, mainSub, full - mainSub - (to >> 1));
    if (to % 2 == 0)
        return full - mainSub - (to >> 1);
    return full - mainSub;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, t);

    int times = n / t, diff = n % t;

    cout << (bestPowerOfDuration(t) * times + bestPowerOfDuration(diff));

    return 0;
}