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

const int MAX = 21, MSUB = 1 << MAX, MOD = 1000000007;
int n,
    dp[MSUB];
bool comp[MAX][MAX]; // comp[i][j] -> man i and woman j are compatible

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scan(comp[i][j]);

    int msub = (1 << n) - 1;
    dp[0] = 1;
    for (int i = 0; i < msub; i++) {
        int curMan = __builtin_popcount(i);
        for (int j = 0; j < n; j++) {
            if((i >> j) & 1)
                continue;

            if(comp[curMan][j]) {
                int &val = dp[i | (1 << j)];
                val = (val + dp[i]) % MOD;
            }
        }
    }

    printf("%d\n", dp[(1 << n) - 1]);

    return 0;
}