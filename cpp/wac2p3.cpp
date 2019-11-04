#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using um = unordered_map<K, V>; template<typename K, typename V> using om = map<K, V>;
template <typename K> using us = unordered_set<K>; template <typename K> using os = set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Function Macros
#define Fori(a, b) for (int i = (a); i < (b); i++)
#define Forj(a, b) for (int j = (a); j < (b); j++)
#define Fork(a, b) for (int k = (a); k < (b); k++)
#define Forinci(a, b) for (int i = (a); i <= (b); i++)
#define Forincj(a, b) for (int j = (a); j <= (b); j++)
#define Forinck(a, b) for (int k = (a); k <= (b); k++)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(type) bool operator()(const type &a, const type &b)
// Shorthand Function Macros Part 2
#define Pow2(x) (1LL << (x))
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void debugArray(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, casttostr_ = ",";
void debug_(){cout<<endl;}
template<typename T> string debug_tostring_(T val) { ostringstream os; os << val; return os.str(); }
string debug_name_(string s, string str_val) {
    string ret = ""; if (s[0] == ' ') { ret += ' '; s = s.substr(1); } if (s[0] == '"' && s[s.length() - 1] == '"') { ret += string("[") + str_val + "]"; }
    else if (s.length() == (size_t)3 && s[0] == '\'' && s[2] == '\'') { ret += '(' + str_val + ')'; } else { ret += s + ": " + str_val; } return ret;
} template<typename F, typename... R> void debug_(F f, R... r) {
    int bc = 0; string pr = "";
    while (bc != 0 || dnms_[di_] != ',') { if (dnms_[di_] == '(') { bc++; } else if (dnms_[di_] == ')') { bc--; } pr += dnms_[di_++]; }
    di_++; cout << debug_name_(pr, debug_tostring_(f)) << ","; debug_(r...);
}
#define debug(...) do{dnms_=#__VA_ARGS__+casttostr_,di_=0,debug_(__VA_ARGS__);}while(0)
#pragma endregion

const int MN = 1001;
int n,
    tot = 0;
char grid[MN][MN << 1];
bool vis[MN][MN << 1];

// do dfs
int minx, maxx, miny, maxy;

inline void resetVars() {
    minx = miny = INF;
    maxx = maxy = -INF;
}

void dfs(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= 2 * n ||
        grid[x][y] != '#' ||
        vis[x][y]) return;
    
    // debug(x, y);
    vis[x][y] = true;
    
    mina(minx, x);
    maxa(maxx, x);
    mina(miny, y);
    maxa(maxy, y);

    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
    // dfs(x + 1, y + 1);
    // dfs(x - 1, y - 1);
    // dfs(x - 1, y + 1);
    // dfs(x + 1, y - 1);
}

// check Pumpkin
inline int ceildiv(int x, int y) { return (x + y - 1) / y; }

int pumpSize(int rc, int cc) { // Row count
    if ((cc - 3) % 2) return -1; // invalid
    
    int m = (cc - 3) / 2,
        trueRc = 2 + m / 5 + ceildiv(2 * m, 3),
        trueCc = 2 * m + 3;

    if (m <= 0) return -1;
    if (rc != trueRc || cc != trueCc) return -1;

    return m;
}

// spot is filled, or false if out of bounds
inline bool filled(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= 2 * n) return false;
    // debug("filled", x, y, grid[x][y]);
    return grid[x][y] == '#';
}

// spot is filled, or false if out of bounds
inline bool nonfilled(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= 2 * n) return false;
    // debug("filled", x, y, grid[x][y]);
    return grid[x][y] == '.';
}


bool check(int x, int y, int m) { // x, y, size
    bool work = true;

    // Pt 1
    Fori(0, 3)
        work &= nonfilled(x - 1, y + m + i);

    // Pt 2
    int add = m / 5;
    while (add--) {
        work &= nonfilled(x, y + m);
        work &= filled(x, y + m + 1);
        work &= nonfilled(x, y + m + 2);

        x++;
    }

    // Pt 3
    Fori(0, m + 2)
        work &= nonfilled(x, y + i - 1);
    work &= filled(x, y + m + 1);
    Fori(0, m + 2)
        work &= nonfilled(x, y + m + 2 + i);
    x++;

    // pt 4
    add = ceildiv(2 * m, 3) + 1;
    int go = 2 * m + 3;
    while (add--) {
        work &= nonfilled(x, y - 1);
        Fori(0, go)
            work &= filled(x, y + i);
        work &= nonfilled(x, y + go);

        x++;
    }

    // pt 5
    Fori(0, 2 * m + 5)
        work &= nonfilled(x, y - 1 + i);

    return work;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    Fori(0, n)
        scan(grid[i]);
    
    Fori(0, n) {
        Forj(0, n << 1) {
            if (!vis[i][j] && grid[i][j] == '#') {
                resetVars();
                dfs(i, j);

                int rc = maxx - minx + 1, cc = maxy - miny + 1, psz = pumpSize(rc, cc);
                // debug("ee", i, j, rc, cc, psz);
                if (psz ^ -1) {
                    tot += check(minx, miny, psz);
                }
            }
        }
    }

    println(tot);

    return 0;
}
