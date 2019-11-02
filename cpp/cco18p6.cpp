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

ostream& operator<<(ostream& out, pii x) {
    out << x.first << " " << x.second;
    return out;
}

const int MN = 4096 + 1;
int n, buf,
    st[MN], idxOfEn[MN];
vec<pii> q, qq;

// Assumes sorted
inline void swapv(int i, int j) {
    q.pb(mpr(i, j));
    swap(st[i], st[j]);
}

// Assumes sorted
inline void reversev(int l, int r) {
    while (l < r) {
        swapv(l, r);
        l++; r--;
    }
}

inline int getMid(int l, int r) {
    int sz = r - l + 1, h = sz >> 1,
        cp[sz];
    copy(st + l, st + r + 1, cp);
    sort(cp, cp + sz);
    return cp[h];
}

int mt = 750;
void mergev(int l, int r, int mid) {
    if (l >= r) return;
    if (l + 1 == r) {
        if (st[l] > st[r])
            swapv(l, r);
        return;
    }
    if (l + 2 == r) {
        Fori(0, 3)
            Forj(l, r)
                if (st[j] > st[j + 1])
                    swapv(j, j + 1);
        return;
    }

    // assert(mv--);
    int div = getMid(l, r), lbegin = mid + 1, rend = mid;

    // find lbegin
    for (int i = l; i <= mid; i++) {
        if (st[i] >= div) {
            lbegin = i;
            break;
        }
    }

    // find rend
    for (int i = mid + 1; i <= r; i++)
        if (st[i] <= div)
            rend = i;
        
    // debug(l, r, mid, div, lbegin, rend);
    // debugArray(st + l, r - l + 1);
    // assert(mt--);
    
    // Merge Lbegin to Rend
    reversev(lbegin, mid);
    reversev(mid + 1, rend);
    reversev(lbegin, rend);

    // cout << "after: "; debugArray(st + l, r - l + 1);

    // merge subarrays
    int newMid = l;
    for (int i = l; i <= r; i++)
        if (st[i] < div)
            newMid = i;

    mergev(l, newMid, lbegin - 1);
    mergev(newMid + 1, r, rend);
}

void mergeSort(int l, int r) {
    // debug(l, r, (l + r) >> 1);
    if (l >= r) return;
    if (l + 1 == r) {
        if (st[l] > st[r])
            swapv(l, r);
        return;
    }

    int mid = (l + r) >> 1;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    mergev(l, r, mid);
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 1; i <= n; i++)
        scan(st[i]);

    mergeSort(1, n);
    qq.resize(q.size());
    copy(q.begin(), q.end(), qq.begin());

    for (int i = 1; i <= n; i++)
        scan(st[i]);
    
    // debug("PART 2 -------------------------------------------------------------------------");
    
    q.clear();
    mergeSort(1, n);
    for (auto it = q.rbegin(); it != q.rend(); it++)
        qq.pb(*it);

    // Output
    cout << qq.size() << "\n";
    for (auto p : qq)
        cout << p << "\n";

    return 0;
}
