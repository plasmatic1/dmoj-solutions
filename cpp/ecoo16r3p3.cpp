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

#ifdef LOCAL
int T = 4;
#else
int T = 10;
#endif

const int MAX = 2001;
int n, l, 
    dp[MAX];
string s;
unordered_set<string> dic[MAX];

void solve() {
    // There are much better ways to do the hashing thing
    for (int i = 0; i < l; i++)
        for (int j = 1; j <= l - i; j++)
            if (dic[j].find(s.substr(i, j)) != dic[j].end())
                dp[i + j] = min(dp[i + j], dp[i] + 1);

    cout << (dp[l] - 1) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++) {
        scan(s);
        dic[s.length()].insert(s);
    }

    while(T--) {
        scan(s);
        l = s.length();
        memset(dp, 0x3f, sizeof dp);
        dp[0] = 0;

        solve();
    }

    return 0;
}