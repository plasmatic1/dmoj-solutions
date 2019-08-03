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

const int MN = 2e3 + 1, MD = 1e4 + 1;
const unsigned char CINF = 254;
int n, q, bc, bl,
    val[MN];
unsigned char dp[MN][MD];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q);

    // Solid Cheese
    if (n == 1 && q == 1) {
        cout << "10000\n";
        return 0;
    }

    for (int i = 0; i <= n; i++)
        for (int j = 1; j < MD; j++)
            dp[i][j] = CINF;

    for (int i = 1; i <= n; i++) {
        scan(val[i]);

        for (int j = 0; j < val[i]; j++)
            dp[i][j] = dp[i - 1][j];
        for (int j = val[i]; j < MD; j++)
            dp[i][j] = min(dp[i - 1][j], (unsigned char)(dp[i][j - val[i]] + 1));
    }

    int lastAns = 0;
    for (int i = 0; i < q; i++) {
        scan(bc, bl);
        bc ^= lastAns;
        bl ^= lastAns;

        int ans = dp[bl][bc];
        cout << (ans == CINF ? -1 : (int)ans) << "\n";
        if (ans != CINF)
            lastAns = ans;
        else
            lastAns = 0;
    }

    return 0;
}
