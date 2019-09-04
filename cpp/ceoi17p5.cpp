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

template <int MAX, int PRIME = 113, char A = 'a'>
struct SubstrHash {
    int &n; string &s; ll pows[MAX], pfxHash[MAX];
    inline int charVal(char c) { return c - A; }
    SubstrHash(int &n0, string &s0) : n(n0), s(s0) { assert(n < MAX); }
    void init() {
        pows[0] = 1; pfxHash[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * PRIME;
            pfxHash[i] = pfxHash[i - 1] * PRIME + charVal(s[i - 1]);
        }
    }
    ll hashSubstr(int l, int r) { return pfxHash[r] - pfxHash[l - 1] * pows[r - l + 1]; }
    ll hashOtherStr(string &s) { // Can also hash any other string using the same prime value
        ll hash = charVal(s[0]);
        for (int i = 1, sz = s.length(); i < sz; i++)
            hash = hash * PRIME + charVal(s[i]);
        return hash;
    }
};

const int MN = 1e6 + 1;
int n,
    dp[MN];
string s;
SubstrHash<MN> ssh(n, s);

int getAns(int l, int r) {
    if (dp[l] != -1) return dp[l];
    if (l > r) return r - l + 1;
    
    int best = 1;
    for (int i = 0; l + i <= r - i; i++) {
        if (ssh.hashSubstr(l, l + i) == ssh.hashSubstr(r - i, r)) {
            best = max(best, getAns(l + i + 1, r - i - 1) + 2);
            break;
        }
    }

    // debug(l, r, best);

    return dp[l] = best;
}

void solve() {
    cout << getAns(1, n) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; scan(t);
    while (t--) {
        scan(s);
        n = s.length();
        
        memset(dp, -1, sizeof dp);
        ssh.init();

        solve();
    }

    return 0;
}