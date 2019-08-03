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

const int MN = 10 + 1, MV = 1e3 + 1;
int n, r, s,
    val[MN], cost1[MN], cost2[MN], dp[MV][MV];
string name[MN];
struct {
    int cost1, cost2, id = 10; // Valid ID should always be <10, so if ID is 10 it's invalid
} par[MV][MV];

// Tallying
int cnt[MN + 1]; // To account for adding to invalid IDs

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, r, s);

    for (int i = 0; i < n; i++) {
        scan(name[i], val[i], cost1[i], cost2[i]);

        for (int j = 0; j < MV; j++) {
            if (j < cost1[i])
                continue;
            for (int k = 0; k < MV; k++) {
                if (k < cost2[i])
                    continue;
                int alt = dp[j - cost1[i]][k - cost2[i]] + val[i], &val = dp[j][k];
                if (alt > val) {
                    val = alt;
                    par[j][k] = {j - cost1[i], k - cost2[i], i};
                }
            }
        }
    }

    cout << dp[r][s] << "\n";

    int curD = r, curV = s;
    while (curD != 0 || curV != 0) {
        auto cpar = par[curD][curV];
        // debug(curD, curV, cpar.id);

        cnt[cpar.id]++;
        curD = cpar.cost1;
        curV = cpar.cost2;
    }

    for (int i = 0; i < n; i++)
        cout << name[i] << " " << cnt[i] << "\n";

    return 0;
}
