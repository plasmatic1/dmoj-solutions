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

const int MAX = 2001, MOD = 998244353;
int n, 
    arr[MAX];
ll dp[MAX][MAX]; // i -> amount of elements chosen, j -> number of numbers in the set

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n);

    for (int i = 1; i <= n; i++) {
        scan(arr[i]);
        arr[i] %= MOD;
    }
    
    for (int i = 0; i <= n; i++)
        dp[0][i] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 1;
        for (int j = 1; j <= i; j++) {
            dp[i][i] = (dp[i][i] * arr[j]) % MOD;
            dp[i][i] = (dp[i][i] + MOD) % MOD;
        }
        
        for (int j = i + 1; j <= n; j++) {
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j - 1] * arr[j]) % MOD;
            dp[i][j] = (dp[i][j] + MOD) % MOD;
        }
    }

    for (int i = 1; i <= n; i++)
        printf("%lld ", dp[i][n]), assert(dp[i][n] >= 0);
    printf("\n");

    return 0;
}