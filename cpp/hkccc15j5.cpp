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

const int MN = 1e3 + 1, MM = 1e5 + 1;
int n, m, csz,
    A[MM], B[MM], clr[MN];
bool vis[MN];
vector<int> g[MN];
vector<pair<int, int>> offsets;

void setColor(int cur, bool cclr) {
    clr[cur] = cclr;
    for (int adj : g[cur])
        if (clr[adj] == -1)
            setColor(adj, !cclr);
}

// Offsets
int curOffset = 0;
void getOffset(int cur, bool cclr) {
    vis[cur] = true;
    curOffset += cclr ? 1 : -1;
    for (int adj : g[cur])
        if (!vis[adj])
            getOffset(adj, !cclr);
}

// Preform DP with offsets
const int D = 1e3;
bool dp[MN][MN << 1];
struct p {
    int i, j, lastType = INF;
    bool operator<(const p &o) const {
        return lastType < o.lastType;
    }
} par[MN][MN << 1];

#define get(c, cc) (dp[(c)][(cc + D)])
#define getp(c, cc) (par[(c)][(cc + D)])

void rec(int cur, int ccnt) {
    bool &ret = get(cur, ccnt);
    if (ret) return;
    
    ret = true;
    if (cur < csz) {
        int ch = offsets[cur].second;
        if (getp(cur + 1, ccnt - ch).lastType == INF)
            getp(cur + 1, ccnt - ch) = {cur, ccnt, 0};
        rec(cur + 1, ccnt - ch);
        if (getp(cur + 1, ccnt + ch).lastType == INF)
            getp(cur + 1, ccnt + ch) = {cur, ccnt, 1};
        rec(cur + 1, ccnt + ch);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);

    for (int i = 0; i < m; i++) {
        scan(A[i], B[i]);
        g[A[i]].push_back(B[i]);
        g[B[i]].push_back(A[i]);
    }

    // Get offsets
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            curOffset = 0;
            getOffset(i, 0);
            offsets.push_back(make_pair(i, curOffset));
        }
    }

    // Preform DP
    csz = offsets.size();
    rec(0, 0);

    int best = INF;
    for (int i = D; i >= -D; i--)
        if (get(csz, i) && abs(i) < abs(best))
            best = i;

    // debug(best);

    // Set colours
    memset(clr, -1, sizeof clr);
    int curi = csz, curj = best;
    while (curi || curj) {
        // debug(curi, curj, offsets[curi - 1].second, par[curi][curj+D].lastType);
        setColor(offsets[curi - 1].first, getp(curi, curj).lastType);
        int ti = curi, tj = curj;
        curi = getp(ti, tj).i;
        curj = getp(ti, tj).j;
    }

    // Check colours
    for (int i = 0; i < m; i++) {
        if (clr[A[i]] == clr[B[i]]) {
            cout << "-1\n";
            return 0;
        }
    }

    for (int i = 1; i <= n; i++)
        cout << (clr[i] + 1);
    cout << "\n";

    return 0;
}