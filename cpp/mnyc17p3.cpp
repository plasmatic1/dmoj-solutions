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

template <int MAX, int PRIME = 113, char A = 'A'>
struct SubstrHash {
    int n; string s;
    ll pows[MAX], pfxHash[MAX];
    inline int charVal(char c) { return c - A; }
    SubstrHash() {}
    void init(string &s0) {
        n = s0.length(); s = s0;
        pows[0] = 1; pfxHash[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = (pows[i - 1] * PRIME);
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
SubstrHash<1000001> aHash, bHash;
string a, b;
int n, m;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(a, b);
    aHash.init(a);
    bHash.init(b);
    n = a.length();
    m = b.length();

    int end = min(n, m), best = 0;
    for (int i = 1; i <= end; i++)
        if (aHash.hashSubstr(n - i + 1, n) == bHash.hashSubstr(1, i))
            best = i;
    
    cout << a << b.substr(best, m);

    return 0;
}