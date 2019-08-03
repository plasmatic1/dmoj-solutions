#include <bits/stdc++.h>

#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC optimize "omit-frame-pointer"
#pragma GCC optimize "prefetch-loop-arrays"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,aes,sse4a,sse4.1,sse4.2,mmx,popcnt,tune=native"

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

const int MN = 16 + 1, MS = 1 << 16;
int n, hptr = 0,
    vals[MN][MN], has[MN + 5];
ll gain[MS], dp[MS];

int __attribute__((optimize("-O3"))) main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scan(vals[i][j]);
    
    int msub = 1 << n;
    for (int i = 0; i < msub; i++) {
        hptr = 0;
        for (int j = 0; j < n; j++)
            if ((i >> j) & 1)
                has[hptr++] = j;
        
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1)
                continue;
            
            ll &val = gain[i | (1 << j)];
            if (!val) {
                val = gain[i];
                for (int k = 0; k < hptr; k++)
                    val += vals[has[k]][j] + vals[j][has[k]];
            }
        }
        // debug(i, gain[i]);
    }

    for (int i = 0; i < msub; i++) {
        hptr = 0;
        for (int j = 0; j < n; j++)
            if (!((i >> j) & 1))    
                has[hptr++] = j;

        int msub2 = 1 << hptr;
        for (int j = 0; j < msub2; j++) {
            int mask = 0;
            for (int k = 0; k < hptr; k++)
                if ((j >> k) & 1)
                    mask |= 1 << has[k];

            ll &val = dp[i | mask];
            val = max(val, dp[i] + gain[mask]);
        }
    }

    // End DP values are doubled for some reason
    cout << (dp[msub - 1] >> 1) << "\n";

    return 0;
}
