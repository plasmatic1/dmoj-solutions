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

struct p { 
    int c, f, v;

    bool operator<(const p &o) const {
        if (f == o.f) return v < o.v;
        return f > o.f;
    }
};

const int MN = 4e3 + 1, MK = 1e5 + 1;
int n, m;
ll dp[2][MK];
p vals[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++) {
        scan(vals[i].c, vals[i].f, vals[i].v);
        vals[i].v *= -1;
    }

    scan(m);

    for (int i = n; i < n + m; i++) {
        scan(vals[i].c, vals[i].f, vals[i].v);
        vals[i].c *= -1;
    }
    
    int sz = n + m;
    sort(vals, vals + sz);
    copy(vals, vals + sz, vals + 1);

    // DP[0][0] = 0;
    bool cur = 1, prev = 0;

    for (int i = 1; i < MK; i++)
        dp[prev][i] = -LLINF;
    
    for (int i = 1; i <= sz; i++) {
        for (int j = 0; j < MK; j++) {
            dp[cur][j] = dp[prev][j];
            if (j - vals[i].c >= 0 && j - vals[i].c < MK)
                dp[cur][j] = max(dp[cur][j], dp[prev][j - vals[i].c] + vals[i].v);
            
            // debug(i, j, vals[i].c, vals[i].f, vals[i].v);
            // debug(dp[cur][j]);
        }

        cur ^= 1;
        prev ^= 1;
    }

    cout << *max_element(dp[prev], dp[prev] + MK) << "\n";

    return 0;
}