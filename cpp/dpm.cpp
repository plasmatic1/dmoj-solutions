#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MN = 101, MK = 100001, MOD = 1000000007;
int n, k, 
    amt[MN], dp[MN][MK];

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n, k);

    for (int i = 1; i <= n; i++)
        scan(amt[i]);
    
    dp[0][k] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++)
            dp[i - 1][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % MOD;
        for (int j = 0; j <= k; j++) {
            dp[i][j] = dp[i - 1][min(j + amt[i], k)];
            if (j > 0)
                dp[i][j] = (dp[i][j] - dp[i - 1][j - 1] + MOD) % MOD;
            
            // debug(i, j, dp[i][j]);
        }
    }

    cout << dp[n][0] << "\n";

    return 0;
}
