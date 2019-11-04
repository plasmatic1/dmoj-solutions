#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common DS shorteners
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <typename T>
using vec = vector<T>;
template <typename K, typename V>
using um = unordered_map<K, V>;
template <typename K, typename V>
using om = map<K, V>;
template <typename K>
using us = unordered_set<K>;
template <typename K>
using os = set<K>;
using vi = vec<int>;
using vl = vec<ll>;
using vpi = vec<pii>;
using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Function Macros
#define Fori(a, b) for (int i = a; i < b; i++)
#define Forj(a, b) for (int j = a; j < b; j++)
#define Fork(a, b) for (int k = a; k < b; k++)
#define Forinci(a, b) for (int i = a; i <= b; i++)
#define Forincj(a, b) for (int j = a; j <= b; j++)
#define Forinck(a, b) for (int k = a; k <= b; k++)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(type) bool operator()(const type &a, const type &b)
// Shorthand Function Macros Part 2
#define Pow2(x) (1LL << (x))
// Shorthand Functions
template <typename T>
inline void maxa(T &st, T v) { st = max(st, v); }
template <typename T>
inline void mina(T &st, T v) { st = min(st, v); }
inline void setprec(ostream &out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T>
ostream &operator<<(ostream &out, vector<T> iter) {
    out << "[";
    for (auto t : iter) {
        out << t << ", ";
    }
    out << "]";
    return out;
}
template <typename T>
void debugArray(T *arr, int sz) {
    cout << "[";
    for (int i = 0; i < sz; i++) {
        cout << arr[i] << ", ";
    }
    cout << "]\n";
}
template <typename T>
void printArray(T *arr, int sz) {
    for (int i = 0; i < sz; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
#define OUT_OPERATOR(type, propa, propb)                                                       \
    ostream &operator<<(ostream &out, type obj) {                                              \
        out << "(" << #propa << "=" << obj.propa << ", " << #propb << "=" << obj.propb << ")"; \
        return out;                                                                            \
    }
// I/O Operations
inline void scan() {}
template <typename F, typename... R>
inline void scan(F &f, R &... r) {
    cin >> f;
    scan(r...);
}
template <typename F>
inline void println(F t) { cout << t << '\n'; }
template <typename F, typename... R>
inline void println(F f, R... r) {
    cout << f << " ";
    println(r...);
}
inline void print() {}
template <typename F, typename... R>
inline void print(F f, R... r) {
    cout << f;
    print(r...);
}
// Debugging
int di_;
string dnms_, casttostr_ = ",";
void debug_() { cout << endl; }
template <typename T>
string debug_tostring_(T val) {
    ostringstream os;
    os << val;
    return os.str();
}
string debug_name_(string s, string str_val) {
    string ret = "";
    if (s[0] == ' ') {
        ret += ' ';
        s = s.substr(1);
    }
    if (s[0] == '"' && s[s.length() - 1] == '"') {
        ret += string("[") + str_val + "]";
    } else if (s.length() == (size_t)3 && s[0] == '\'' && s[2] == '\'') {
        ret += '(' + str_val + ')';
    } else {
        ret += s + ": " + str_val;
    }
    return ret;
}
template <typename F, typename... R>
void debug_(F f, R... r) {
    int bc = 0;
    string pr = "";
    while (bc != 0 || dnms_[di_] != ',') {
        if (dnms_[di_] == '(') {
            bc++;
        } else if (dnms_[di_] == ')') {
            bc--;
        }
        pr += dnms_[di_++];
    }
    di_++;
    cout << debug_name_(pr, debug_tostring_(f)) << ",";
    debug_(r...);
}
#define debug(...)                                                       \
    do {                                                                 \
        dnms_ = #__VA_ARGS__ + casttostr_, di_ = 0, debug_(__VA_ARGS__); \
    } while (0)
#pragma endregion

/*

State: L, R, SZ, TYPE
- Min. steps req'D to reduce [L,R] to TYPE (G/H)

TYPE 0 -> G
TYPE 1 -> H

*/

const int MN = 101, MK = 7;
int n, k,
    dp[MN][MN][MK][2], cnts[2][MN];
string s;

int rsq(int l, int r, int type) { return cnts[type][r] - cnts[type][l - 1]; }

int rec(int l, int r, int ck, int type) {
    // if (rsq(type, l, r) < k) return INF;
    if (rsq(l, r, type) == r - l + 1) return ck <= r - l + 1 ? 0 : INF;
    int &ret = dp[l][r][ck][type];
    if (ret != -1) return ret;

    ret = INF;
    Forinci(l, r - 1) {
        Forincj(0, ck)
            mina(ret, rec(l, i, j, type) + rec(i + 1, r, ck - j, type));
    }

    Forinci(l, r - 1) {
        mina(ret, rec(l, i, ck, type) + rec(i + 1, r, k, !type) + 1);
        mina(ret, rec(l, i, k, !type) + 1 + rec(i + 1, r, ck, type));
    }

    // debug(l, r, type, ret);

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k, s);
    s = " " + s;

    Forinci(1, n) {
        if (s[i] == 'G')
            cnts[0][i] = 1;
        else
            cnts[1][i] = 1;

        cnts[0][i] += cnts[0][i - 1];
        cnts[1][i] += cnts[1][i - 1];
    }

    memset(dp, -1, sizeof dp);
    int ans = INF;

    Fori(0, 2) {
        mina(ans, rec(1, n, k, i) + 1);
    }

    // debug(rec(1,5,2,1));
    // debug(rec(1,5,3,1));
    // debug(rec(1,6,1,1));
    // debug(rec(1,6,2,1));
    // debug(rec(1,6,3,1));
    // debug(rec(1,6,4,1));

    if (ans == INF)
        println(-1);
    else
        println(ans);

    return 0;
}
