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

#define MAXD 140
int t;
ll n,
    dp[MAXD];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    dp[2] = dp[3] = 1;
    for (int i = 4; i < MAXD; i++)
        dp[i] = dp[i - 2] + dp[i - 3];

    scan(t);
    while (t--) {
        scan(n);

        int digc = 0;
        ll cc = 0;
        for (int i = 1; i < MAXD; i++) {
            ll r = cc + dp[i];
            if (cc <= n && n <= r) {
                digc = i;
                break;
            }
            cc = r;
        }

        for (int i = 0; i < digc; i++)
            n -= dp[i];

        string ans = "";
        while (digc > 3) {
            ll d420 = dp[digc - 3], d69 = d420 + dp[digc - 2];
            
            if (d420 + 1 <= n && n <= d69) {
                n -= d420;
                digc -= 2;
                ans += "69";
            }
            else {
                digc -= 3;
                ans += "420";
            }
        }

        if (digc == 3)
            ans += "420";
        else
            ans += "69";

        cout << ans << "\n";
    }

    return 0;
}