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
    int x, y, w;
    bool operator<(const p &o) const {
        return w < o.w;
    }
};

const int MAX = 2501;
string north, east, west, south, s;
int l;
set<pair<int, int>> dp[MAX];

void rec(int x, int y, int c);

void tryGo(int x, int y, int c, string &dir) {
    if (s.substr(c, dir.length()) == dir)
        rec(x, y, c + dir.length());
}

void rec(int x, int y, int c) {
    auto cLoc = make_pair(x, y);
    if (dp[c].find(cLoc) != dp[c].end())
        return;

    dp[c].insert(cLoc);
    tryGo(x + 1, y, c, north);
    tryGo(x - 1, y, c, south);
    tryGo(x, y + 1, c, east);
    tryGo(x, y - 1, c, west);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(north, south, east, west, s);
    l = s.length();
    rec(0, 0, 0);
    
    cout << dp[l].size() << "\n";

    return 0;
}