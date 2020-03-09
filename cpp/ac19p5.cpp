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

namespace SS {
    struct p {
        int i, j;
    };

    const int MN = 3e3 + 1;
    int n,
        arr[MN][MN], dis[MN][MN];

    vector<p> makeAdjs(int i, int j) {
        return {{i + 1, j}, {i - 1, j}, {i, j + 1}, {i, j - 1}};
    }

    int dfs(int i, int j) {
        int &ret = dis[i][j];
        if (ret != -1) return ret;
    
        ret = 0;
        for (auto adj : makeAdjs(i, j)) {
            if (adj.i < 0 || adj.i >= n || adj.j < 0 || adj.j >= n || arr[adj.i][adj.j] <= arr[i][j])
                continue;
            ret = max(ret, dfs(adj.i, adj.j) + 1);
        }

        return ret;
    }

    int solve() {
        memset(dis, -1, sizeof dis);
        int best = -INF;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                best = max(best, dfs(i, j));
        return best;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(SS::n);

    for (int i = 0; i < SS::n; i++)
        for (int j = 0; j < SS::n; j++)
            scan(SS::arr[i][j]);
    
    cout << SS::solve() << "\n";

    return 0;
}