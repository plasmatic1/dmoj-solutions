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

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

struct ed {
    int v, w;
};

const int MN = 2e5 + 1, MK = 1e6 + 1;
int n, k, ba, bb, bc;
vector<ed> g[MN];

// Centroid Decomp
int sz[MN], pars[MN];
bool blocked[MN];
ll totPath = 0, cTotPath = 0,
    tots[MN], ctots[MN];
namespace __CNTS {
    int cqid = 0, 
        cnts[MK], qid[MK];
    inline void resetCnts() { cqid++; }
    inline int getCnt(int id) {
        if (qid[id] < cqid) {
            qid[id] = cqid;
            return cnts[id] = 0;
        }
        return cnts[id];
    }
    inline void incCnt(int id) {
        if (qid[id] < cqid) {
            qid[id] = cqid;
            cnts[id] = 0;
        }
        cnts[id]++;
    }
}
using __CNTS::getCnt; using __CNTS::incCnt; using __CNTS::resetCnts;

int gsz(int cur, int par) {
    sz[cur] = 1;
    for (ed adj : g[cur])
        if ((adj.v ^ par) && !blocked[adj.v])
            sz[cur] += gsz(adj.v, cur);
    return sz[cur];
}

int gcentroid(int cur, int par, int half) {
    for (ed adj : g[cur])
        if ((adj.v ^ par) && !blocked[adj.v] && sz[adj.v] > half)
            return gcentroid(adj.v, cur, half);
    return cur;
}

// Adding
const int ADD_CTOT = 1,
    ADD_PTOT = 2,
    ADD_CNT = 4,
    FINISH = 8;
int curMode = 0;
void dfs(int cur, int par, ll cdis) {
    if (curMode & FINISH) {
        tots[cur] += ctots[cur];
        ctots[cur] = 0LL;
    }
    else if (cdis <= k) {
        ll addCnt = getCnt(k - cdis);
        if (curMode & ADD_CTOT)
            ctots[cur] += addCnt;
        if (curMode & ADD_PTOT) 
            cTotPath += addCnt;
        if (curMode & ADD_CNT)
            incCnt(cdis);
    }

    for (ed adj : g[cur])
        if ((adj.v ^ par) && !blocked[adj.v])
            dfs(adj.v, cur, cdis + adj.w);
}

ll collect(int begin, int cur, int par) {
    // debug(cur);
    for (ed adj : g[cur])
        if ((adj.v ^ par) && !blocked[adj.v])
            ctots[cur] += (cur != begin) * collect(begin, adj.v, cur);
    return ctots[cur];
}

void decomp(int cur, int par) {
    gsz(cur, par);
    if (sz[cur] == 1)
        return;

    // Centroid DFS for forward-back
    cTotPath = 0;
    incCnt(0);

    int centroid = gcentroid(cur, -1, sz[cur] >> 1);
    for (ed &adj : g[centroid]) {
        if (!blocked[adj.v]) {
            curMode = ADD_CTOT | ADD_PTOT;
            dfs(adj.v, centroid, adj.w);
            curMode = ADD_CNT;
            dfs(adj.v, centroid, adj.w);
        }
    }
    
    // Centroid dfs for back-front
    resetCnts();
    // cnts[0] = 1;

    for (auto it = g[centroid].rbegin(); it != g[centroid].rend(); it++) {
        auto &adj = *it;
        if (!blocked[adj.v]) {
            curMode = ADD_CTOT;
            dfs(adj.v, centroid, adj.w);
            curMode = ADD_CNT;
            dfs(adj.v, centroid, adj.w);
        }
    }

    resetCnts();

    // Move everything back up and add values for total and centroid
    collect(centroid, centroid, -1);
    ctots[centroid] += cTotPath;
    totPath += cTotPath;

    // Finish UP
    curMode = FINISH;
    dfs(centroid, -1, 0LL);

    // Propagate Centroid
    blocked[centroid] = true;
    for (ed adj : g[centroid])
        if (!blocked[adj.v])
            decomp(adj.v, centroid);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k);

    for (int i = 1; i < n; i++) {
        scan(ba, bb, bc);
        g[ba].push_back({bb, bc});
        g[bb].push_back({ba, bc});
    }

    decomp(1, -1);

    for (int i = 1; i <= n; i++) {
        int gcdv = gcd(tots[i], totPath);
        if (gcdv == 0) {
            gcdv = 1;
            totPath = 1;
        }
        
        cout << (tots[i] / gcdv) << " / " << (totPath / gcdv) << "\n";
    }

    return 0;
}
