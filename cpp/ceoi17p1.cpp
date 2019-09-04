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

struct edi {
    int v, i;
};

const int MN = 1e5 + 1;
int n, m, p, ba, bb,
    A[MN], B[MN];
vector<edi> g[MN], comp[MN];

// Tarjan Bridge Finding
namespace asdpfiajsdofisj {
    int cord = -1, 
        ord[MN], low[MN], vis[MN];
    bool isCycle[MN];

    void dfs(int cur, int par, int parEdi) {
        if (vis[cur] != -1) return;
        ord[cur] = low[cur] = ++cord;
        vis[cur] = parEdi;

        // debug(cur, par, parEdi);

        for (edi adj : g[cur]) {
            if (adj.v ^ par) {
                dfs(adj.v, cur, adj.i);
                low[cur] = min(low[cur], low[adj.v]);
                
                if (low[adj.v] <= ord[cur])
                    isCycle[adj.i] = true;
            }
            else {
                // debug("back", cur, par, adj.v, adj.i);

                if (parEdi != adj.i) {
                    isCycle[parEdi] = true;
                    isCycle[adj.i] = true;
                }
            }
        }
    }
    void tarjan() {
        memset(vis, -1, sizeof vis);
        for (int i = 1; i <= n; i++)
            dfs(i, -1, -1);
    }
}
using asdpfiajsdofisj::tarjan; using asdpfiajsdofisj::isCycle;

namespace aosifoisdfoiadjfi {
    int to[MN];
    bool vis[MN];

    void dfs(int begin, int cur) {
        if (vis[cur]) return;
        vis[cur] = true;
        to[cur] = begin;

        for (edi adj : g[cur])
            if (isCycle[adj.i])
                dfs(begin, adj.v);
    }
    void compress() {
        for (int i = 1; i <= n; i++)
            dfs(i, i);
        for (int i = 1; i <= n; i++) {
            for (edi adj : g[i]) {
                int a = to[i], b = to[adj.v];
                if (a ^ b) 
                    comp[a].push_back({b, adj.i});
            }
        }
        // for (int i = 1; i <= n; i++) {
        //     sort(comp[i].begin(), comp[i].end());
        //     comp[i].resize(unique(comp[i].begin(), comp[i].end()) - comp[i].begin());
        // }
    }
}
using aosifoisdfoiadjfi::compress; using aosifoisdfoiadjfi::to;

// Tree (difference array)
int dif[MN], lv[MN];

int dfs(int cur, int par) {
    lv[cur] = lv[par] + 1;
    for (edi adj : comp[cur])
        if (adj.v ^ par)
            dif[cur] += dfs(adj.v, cur);
    return dif[cur];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("out.txt", "w", stdout);

    scan(n, m);

    for (int i = 0; i < m; i++) {
        scan(A[i], B[i]);
        g[A[i]].push_back({B[i], i});
        g[B[i]].push_back({A[i], i});
    }

    tarjan();
    compress();

    // printArray(cout, to, n + 1); cout << "\n";

    // Calculating L and R directions
    scan(p);

    for (int i = 0; i < p; i++) {
        scan(ba, bb);
        dif[to[ba]]++;
        dif[to[bb]]--;
    }

    for (int i = 1; i <= n; i++)
        if (!lv[to[i]])
            dfs(to[i], 0);
    
    // for (int i = 1; i <= n; i++) debug(i, dif[i]);

    for (int i = 0; i < m; i++) {
        // if (isCycle[i])
        //     cout << 'B';
        // else {
            int a = to[A[i]], b = to[B[i]];

            if (a == b) {
                cout << 'B';
                continue;
            }

            bool isSwap = false;
            if (lv[a] > lv[b]) { // B is the child
                swap(a, b);
                isSwap = true;
            }

            // debug(i, A[i], B[i], a, b, lv[a], lv[b], dif[a], dif[b]);
            
            if (dif[b] > 0)
                cout << (isSwap ? 'R' : 'L');
            else if (dif[b] < 0)
                cout << (isSwap ? 'L' : 'R');
            else
                cout << 'B';
        // }
    }
    cout << "\n";

    return 0;
}
