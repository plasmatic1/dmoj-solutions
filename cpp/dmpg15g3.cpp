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

const int MN = 2e5 + 1;
int n, lk, rk, lc, rc, ba, bb;
vector<int> g[MN];
char type[MN];

// Centroid Decomp
struct p { // Offline by kinako
    int k, c;
    bool operator<(const p &o) const { return k < o.k; }
};
OUT_OPERATOR(p, k, c)

// Binary Indexed Tree
namespace __QID {
    int cqid = 0,
        qid[MN + 10], bit[MN + 10];
    inline void reset() {
        cqid++;
    }
    inline int& get(int x) {
        if (qid[x] < cqid) {
            qid[x] = cqid;
            bit[x] = 0;
        }
        return bit[x];
    }
    inline int sum(int x) {
        x++; // Increment for Query 0
        if (x < 0) return 0;

        int sum = 0;
        for (; x; x -= x & -x)
            sum += get(x);
        return sum; 
    }
    inline void add(int x, int z) {
        x++; // Increment for Query 0

        for (; x <= (n + 1); x += x & -x)
            get(x) += z;
    }
};
using __QID::reset; using __QID::sum; using __QID::add;

ll tot = 0;
int sz[MN];
bool blocked[MN];

// Basic Centroid Stuff
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

// DFS Utils
inline int getK(int cur) {
    return type[cur - 1] == 'K';
}

inline int getC(int cur) {
    return type[cur - 1] == 'C';
}

inline bool getSelfAdd(int cur) {
    int kCnt = getK(cur), cCnt = getC(cur);
    return lk <= kCnt && kCnt <= rk && lc <= cCnt && cCnt <= rc;
}

vector<p> off, off2;
void dfs(int begin, int cur, int par, int kCnt, int cCnt) {
    // debug(begin, cur, par, kCnt, cCnt);
    off.push_back({kCnt, cCnt});
    off2.push_back({kCnt - getK(begin), cCnt - getC(begin)});
    for (int adj : g[cur])
        if ((adj ^ par) && !blocked[adj])
            dfs(begin, adj, cur, kCnt + getK(adj), cCnt + getC(adj));
}

// Offline Processing Utilities
inline ll offline(int kMax) {
    ll ret = 0;
    int optr = 0, osz = off.size();
    for (p qu : off2) {
        while (optr < osz && off[optr].k + qu.k <= kMax) {
            add(off[optr].c, 1);
            optr++;
        }
        ret += sum(rc - qu.c) - sum(lc - 1 - qu.c);
    }
    
    reset();

    return ret;
}

inline void sortOff() {
    sort(off.begin(), off.end());
    sort(off2.begin(), off2.end());
    reverse(off2.begin(), off2.end());
}

inline void clearOff() {
    off.clear();
    off2.clear();
}

// Main Centroind Function
void decomp(int cur) {
    bool selfAdd = getSelfAdd(cur);
    gsz(cur, -1);
    if (sz[cur] == 1) {
        tot += selfAdd;
        return;
    }

    ll pathAdd = 0;
    int centroid = gcentroid(cur, -1, sz[cur] >> 1);
    selfAdd = getSelfAdd(centroid); // Reset selfAdd for centroid (since cur != centroid (maybe))
    
    // Offline Processing

    // First get all pairs and everything * 2
    dfs(centroid, centroid, -1, getK(centroid), getC(centroid));
    sortOff();
    // debug(centroid, off);
    pathAdd += offline(rk) - offline(lk - 1);
    clearOff();

    // Subtract centroid -> centroid for now and add back later since we divide by 2
    pathAdd -= selfAdd;

    // Subtract all self loopy paths
    for (int adj : g[centroid]) {
        if (!blocked[adj]) {
            dfs(centroid, adj, centroid, getK(centroid) + getK(adj), getC(centroid) + getC(adj));
            sortOff();
            pathAdd -= offline(rk) - offline(lk - 1);
            clearOff();
        }
    }

    // debug(centroid, pathAdd);
    pathAdd >>= 1;
    pathAdd += selfAdd;
    tot += pathAdd;

    blocked[centroid] = true;
    for (int &adj : g[centroid]) {
        if (!blocked[adj])
            decomp(adj);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, lk, rk, lc, rc, type);

    for (int i = 1; i < n; i++) {
        scan(ba, bb);
        g[ba].push_back(bb);
        g[bb].push_back(ba);
    }

    decomp(1);

    cout << tot << "\n";

    return 0;
}
