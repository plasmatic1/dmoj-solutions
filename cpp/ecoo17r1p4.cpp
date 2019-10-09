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
#define ForI(a, b) for (int i = a; i < b; i++)
#define ForJ(a, b) for (int j = a; j < b; j++)
#define ForK(a, b) for (int k = a; k < b; k++)
#define ForincI(a, b) for (int i = a; i <= b; i++)
#define ForincJ(a, b) for (int j = a; j <= b; j++)
#define ForincK(a, b) for (int k = a; k <= b; k++)
#define CmpLt(type) bool operator<(const type &o) const
#define CmpGt(type) bool operator>(const type &o) const
#define CmpFn(type) bool operator()(const type &a, const type &b)
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

struct name {
    string v;
    int id;
    CmpLt(name) {
        return v < o.v;
    }
};

const int MN = 1e3 + 1;
int n;
name names[MN];

// Dfs util
bool vis[MN];
int dfs(int cur, vi &to) {
    if (vis[cur]) return 0;
    vis[cur] = true;
    return dfs(to[cur - 1], to) + 1;
}

ll invCount(vi &perm) {
    memset(vis, 0, sizeof vis);
    ll tot = 0;
    for (int x : perm) {
        // debug(x, perm);
        if (!vis[x]) {
            tot += dfs(x, perm) - 1;
        }
    }
    return tot;
}

void solve(){
    scan(n);

    ForI(0, n) {
        scan(names[i].v);
        names[i].id = i;
    }

    // debug("operm");
    // debugArray(operm, n);

    ll best = LLINF;
    ForI(0, n) {
        vec<name> tnames(names, names + n);
        tnames.erase(tnames.begin() + i);
        ForJ(0, n - 1)
            tnames[j].id = j;
        sort(tnames.begin(), tnames.end());
        
        vi perm; perm.resize(n - 1);
        ForJ(0, n - 1)
            perm[tnames[j].id] = j + 1;
        // debug(i, perm);

        mina(best, invCount(perm));
    }

    println(best);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = 10;
    while (T--) {
        solve();
    }

    return 0;
}
