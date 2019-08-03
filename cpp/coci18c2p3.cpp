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

const int MN = 1e5 + 1, MLOG = 25;
int n, ba, bb,
    val[MN];
vector<int> g[MN];

// Centroid Decomp
int sz[MN], cnt[MLOG], nonCnt[MLOG];
bool blocked[MN];
ll tot = 0;

int gsz(int cur, int par) {
    sz[cur] = 1;
    for (int &adj : g[cur])
        if ((adj ^ par) && !blocked[adj])
            sz[cur] += gsz(adj, cur);
    return sz[cur];
}

int gcentroid(int cur, int par, int half) {
    for (int &adj : g[cur])
        if ((adj ^ par) && !blocked[adj] && sz[adj] > half)
            return gcentroid(adj, cur, half);
    return cur;
}

inline void incrementCntsForDis(int cdis) {
    for (int i = 0; i < MLOG; i++) {
        if ((cdis >> i) & 1)
            cnt[i]++;
        else
            nonCnt[i]++;
    }
}

void dfsAdd(int cur, int par, int cdis) {
    incrementCntsForDis(cdis);
    // debug(cur, par, cdis);
    
    for (int adj : g[cur])
        if ((adj ^ par) && !blocked[adj])
            dfsAdd(adj, cur, cdis ^ val[adj]);
}

void dfsCount(int cur, int par, int cdis) {
    for (int i = 0; i < MLOG; i++) {
        bool bit = (cdis >> i) & 1;
        tot += (1LL << i) * (bit ? nonCnt[i] : cnt[i]);
        // debug("count", cur, par, cdis, i, bit, nonCnt[i], cnt[i], tot);
    }

    for (int adj : g[cur])
        if ((adj ^ par) && !blocked[adj])
            dfsCount(adj, cur, cdis ^ val[adj]);
}

void decomp(int cur) {
    gsz(cur, -1);
    if (sz[cur] == 1)
        return;
    
    memset(cnt, 0, sizeof cnt);
    memset(nonCnt, 0, sizeof nonCnt);
    int centroid = gcentroid(cur, -1, sz[cur] >> 1);
    incrementCntsForDis(val[centroid]);

    // debug(centroid);

    for (int adj : g[centroid]) {
        if (!blocked[adj]) {
            dfsCount(adj, centroid, val[adj]);
            dfsAdd(adj, centroid, val[centroid] ^ val[adj]);
        }
    }

    blocked[centroid] = true;
    for (int adj : g[centroid])
        if (!blocked[adj])
            decomp(adj);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 1; i <= n; i++)
        scan(val[i]);
    
    for (int i = 1; i < n; i++) {
        scan(ba, bb);
        g[ba].push_back(bb);
        g[bb].push_back(ba);
    }
    
    decomp(1);
    // debug(tot);

    // Length-0 Paths
    for (int i = 1; i <= n; i++)
        tot += val[i];

    cout << tot << "\n";

    return 0;
}
