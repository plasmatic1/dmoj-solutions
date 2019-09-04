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

const int MN = 31, ML = 26;
int v, t, r1, r2, q, start = -1,
    dp[MN][MN][ML];
char ba, bb, bc, 
    vars[MN], terms[MN];
bool termMap[ML][ML];
vector<pair<int, int>> rules[ML];
string buf;

inline int chl(char c) { return c - 'a'; }
inline int chu(char c) { return c - 'A'; }

bool rec(int l, int r, int let) {
    if (l == r) return termMap[chl(buf[l])][let];
    int &ret = dp[l][r][let];
    if (ret != -1) return ret;

    ret = 0;
    for (int i = l; i < r; i++) {
        for (auto &rule : rules[let]) {
            ret |= rec(l, i, rule.first) && rec(i + 1, r, rule.second);
            if (ret) break;
        }
        if (ret) break;
    }

    // char nl = (char)(let+'A'); debug(l, r, let, nl, ret);

    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(v, t);

    for (int i = 0; i < v; i++) {
        scan(vars[i]);
        if (!i) start = chu(vars[i]);
    }

    for (int i = 0; i < t; i++)
        scan(terms[i]);

    scan(r1);

    for (int i = 0; i < r1; i++) {
        scan(ba, bb);
        termMap[chl(bb)][chu(ba)] = true;
    }

    scan(r2);

    for (int i = 0; i < r2; i++) {
        scan(ba, bb, bc);
        rules[chu(ba)].push_back(make_pair(chu(bb), chu(bc)));
    }

    scan(q);

    for (int i = 0; i < q; i++) {
        scan(buf);
        buf = " " + buf;

        memset(dp, -1, sizeof dp);
        cout << rec(1, buf.length() - 1, start) << "\n";
    }

    return 0;
}