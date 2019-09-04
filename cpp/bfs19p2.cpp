#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printDebug(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
inline void println(){cout<<"\n";}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

struct p {
    int x, y, w;
    bool operator<(const p &o) const {
        return w > o.w;
    }
};

const int MN = 1e3 + 1;
int n,
    lv[MN][MN];
char grid[MN][MN];
bool vis[MN][MN];
priority_queue<p> nxt;
pii adjs[3];

void makeAdj(p &cur) {
    adjs[0] = {cur.x + 1, cur.y};
    adjs[1] = {cur.x, cur.y + 1};
    adjs[2] = {cur.x, cur.y - 1};
}

// D and R are fixed
// D = N-1
// R = L+N-1

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++) {
        scan(grid[i]);
    }

    memset(lv, 0x3f, sizeof lv);
    lv[0][0] = 0;
    vis[0][0] = true;
    nxt.push({0, 0, 0});

    while (!nxt.empty()) {
        auto cur = nxt.top(); nxt.pop();

        if (cur.w > lv[cur.x][cur.y]) 
            continue;

        makeAdj(cur);
        for (auto adj : adjs) {
            int alt = cur.w;
            if (adj.second < cur.y) // To the left
                alt++;

            if (adj.first < 0 || adj.first >= n || adj.second < 0 || adj.second >= n || alt >= lv[adj.first][adj.second] || grid[adj.first][adj.second] == '#')
                continue;
            
            lv[adj.first][adj.second] = alt;
            nxt.push({adj.first, adj.second, alt});
        }
    }

    // for (int i = 0; i < n; i++)
    //     printDebug(lv[i], n);

    ll l = lv[n - 1][n - 1], r = n - 1 + l, d = n - 1;
    // debug(l, r, d);

    if (l == INF)
        println(-1);
    else
        println(l * l + r * r + d * d);

    return 0;
}
