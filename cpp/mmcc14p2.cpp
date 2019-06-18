#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out, vector<T> iter) { out << "["; for (auto t : iter) { out << t << ", "; } out << "]"; return out; }
template <typename T> void printArray(ostream& out, T* arr, int sz) { out << "["; for (int i = 0; i < sz; i++) { out << arr[i] << ", "; } out << "]"; }
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out, type obj) { out << "(" << #propa << "=" << obj. propa << ", " << #propb << "=" << obj. propb << ")"; return out; }

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

template <int MAX, int PRIME = 113, char A = '0'>
struct SubstrHash {
    int n; string s;
    ll pows[MAX], pfxHash[MAX];
    inline int charVal(char c) { return c - A; }
    SubstrHash() {}
    void init(string &s0) {
        n = s0.length(); s = s0; assert(n < MAX);
        pows[0] = 1; pfxHash[0] = 0;
        for (int i = 1; i <= n; i++) {
            pows[i] = pows[i - 1] * PRIME;
            pfxHash[i] = pfxHash[i - 1] * PRIME + charVal(s[i - 1]);
        }
    }
    ll hashSubstr(int l, int r) { return pfxHash[r] - pfxHash[l - 1] * pows[r - l + 1]; }
    ll hashOtherStr(string &s) { // Can also hash any other string using the same prime value
        ll hash = charVal(s[0]);
        for (int i = 1, sz = s.length(); i < sz; i++)
            hash = hash * PRIME + charVal(s[i]);
        return hash;
    }
};

struct p {
    int id = -1, amt;
};

const int MN = 2001, MM = 5001;
const p DEF_P = {-1, 0};

int n, m, q, bl, br;
p ids[MN];
string buf;
SubstrHash<MM> rows[MN];

template <int MAX, typename T>
struct SegmentTree {
    int n; T DEFAULT, tree[MAX << 2];
    inline T merge(T a, T b){ 
        if (a.id == -1) return b;
        if (b.id == -1) return a;

        T ret = {a.id, -1};
        int l = 0, r = min(a.amt, b.amt) + 1;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (rows[a.id].hashSubstr(1, mid) == rows[b.id].hashSubstr(1, mid))
                l = mid;
            else
                r = mid;
        }
        ret.amt = l; //debug(ret.id, l, r);
        return ret;
    };
    void init(int n0) { n = n0; }
    T build(int i, int l, int r, T* arr){
        if(l == r) return tree[i] = arr[l];

        int mid = (l + r) / 2;
        return tree[i] = merge(build(i << 1, l, mid, arr), build(i << 1 | 1, mid + 1, r, arr));
    }
    T query(int i, int bl, int br, int ql, int qr){
        if(br < ql || bl > qr) return DEFAULT;
        if(bl >= ql && br <= qr) return tree[i];

        int mid = (bl + br) / 2;
        return merge(query(i << 1, bl, mid, ql, qr), query(i << 1 | 1, mid + 1, br, ql, qr));
    }
    T update(int i, int bl, int br, int q, T v){
        if(q < bl || q > br) return tree[i];
        if(bl == q && br == q) return tree[i] = v;

        int mid = (bl + br) / 2;
        return tree[i] = merge(update(i << 1, bl, mid, q, v), update(i << 1 | 1, mid + 1, br, q, v));
    }
};

SegmentTree<MN, p> seg;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m);
    seg.DEFAULT = DEF_P;

    for (int i = 1; i <= n; i++) {
        scan(buf);
        rows[i].init(buf);
        ids[i] = {i, m};
    }

    seg.init(n);
    seg.build(1, 1, n, ids);

    scan(q);

    for (int i = 0; i < q; i++) {
        scan(bl, br);

        cout << seg.query(1, 1, n, bl, br).amt * (br - bl + 1) << "\n";

        swap(ids[bl].id, ids[br].id);
        seg.update(1, 1, n, bl, ids[bl]);
        seg.update(1, 1, n, br, ids[br]);
    }

    return 0;
}