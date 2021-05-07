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

const ll MOD = 1e9+7;
template <int MAX, int PRIME = 113, char A = 'A'>
struct SubstrHash {
    int n; string s;
    ll pows[MAX], pfxHash[MAX];
    inline int charVal(char c) { return c; }
    SubstrHash() : n(0), s("") {}
    void init(string &s0) {
        n = s0.length(); s = s0;
        pows[0] = 1; pfxHash[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = (pows[i - 1] * PRIME)%MOD;
            pfxHash[i] = (pfxHash[i - 1] * PRIME + charVal(s[i - 1]))%MOD;
        }
    }
    ll hashSubstr(int l, int r) {
        ll res = pfxHash[r] - pfxHash[l - 1] * pows[r - l + 1];
        res %= MOD;
        if (res < 0) res += MOD;
        return res;
    }
    ll hashOtherStr(string &s) { // Can also hash any other string using the same prime value
        ll hash = charVal(s[0]);
        for (int i = 1, sz = s.length(); i < sz; i++)
            hash = (hash * PRIME + charVal(s[i]))%MOD;
        return hash;
    }
};

#define ARGS 1000001, 117, 'a'

string s, t;
SubstrHash<ARGS> sHash;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s, t);
    sHash.init(s);
    ll hash = sHash.hashOtherStr(t);

    for (int i = 1, sz = t.size(), end = s.size() - sz + 1; i <= end; i++) {
        if (sHash.hashSubstr(i, i + sz - 1) == hash) {
            cout << (i - 1) << "\n";
            return 0;
        }
    }
    
    cout << "-1\n";

    return 0;
}