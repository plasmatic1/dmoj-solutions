

#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"

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

// Structures for Problem
struct line {
    int m, b;
    void merge(line o) {
        m += o.m;
        b += o.b;
    }
    void inv() {
        m *= -1;
        b *= -1;
    }
    int gety(int x) {
        return m * x + b;
    }
};

OUT_OPERATOR(line, m, b)

const line ZERO = {0, 0};

inline line mergel(const line a, const line b) {
    return {a.m + b.m, a.b + b.b};
}

inline line invl(const line a) {
    // a.inv();
    return {-a.m, -a.b};
}

// Segment Tree
const int MSN = 20e6 + 1;
struct InnerSegNode {
    int l, r; line v;
} nodes[MSN];

#define nrt nodes[rt] // Current node

int cqr; line cv; // Current QL and QR
void __attribute__((optimize("-O3"))) upd(int &rt, int l, int r) {
    static int ctr = 0;
    if (!rt) rt = ++ctr;

    // static int mn = 100;
    // assert(mn--);
    // debug(l, r, cv, cqr);

    nrt.v.merge(cv);
    
    if (l == cqr && r == cqr) return;

    int mid = (l + r) >> 1;

    if (cqr > mid)
        upd(nrt.r, mid + 1, r);
    else
        upd(nrt.l, l, mid);
}

line __attribute__((optimize("-O3"))) query(int &rt, int l, int r) {
    if (!rt) return ZERO;

    if (r <= cqr) return nrt.v;

    int mid = (l + r) >> 1;

    line ret = query(nrt.l, l, mid);
    if (mid + 1 <= cqr) ret.merge(query(nrt.r, mid + 1, r));
    return ret;
}

#undef nrt

const int MN = 3e5 + 1;
int n, q, ba, bb;
string bt;
bool state[MN];
map<int, int> segs;

// BIT Functions
int bit[MN]; // Bit of "SegTree"

inline line __attribute__((optimize("-O3"))) sum(int a, int b) {
    cqr = b;
    line ret = ZERO;
    for (; a; a -= a & -a)
        ret.merge(query(bit[a], 1, n));
    return ret;
}

inline void __attribute__((optimize("-O3"))) add(int a, int ya, int yb) {
    for(; a <= n; a += a & -a) {
        if (ya <= n) {
            cqr = ya; upd(bit[a], 1, n);
        }

        if (yb <= n) {   
            cv.inv();
            cqr = yb; upd(bit[a], 1, n);
            cv.inv();
        }
    }
}

// Range Add/Sub functions and other utility functions used in main()
#define X(...) __VA_ARGS__

#define updRect(x1, y1, x2, y2, x) \
    cv = x; \
    add(x1, y1, y2 + 1); \
    add(x2 + 1, y2 + 1, y1);

OUT_OPERATOR(X(pair<int, int>), first, second)

int __attribute__((optimize("-O3"))) main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q, bt);

    // Init hashmaps and set states
    for (int i = 1; i <= n; i++)
        state[i] = bt[i - 1] == '1';

    // for (int i = 1; i <= n; i++) {
    //     bit[i].reserve(128);
    //     bit[i].max_load_factor(0.25);
    // }
    
    // Initial states
    int lastBegin = -1;
    for (int i = 1; i <= n; i++) {
        if (state[i] && lastBegin == -1)
            lastBegin = i;
        else if (!state[i] && lastBegin != -1) {
            segs[lastBegin] = i - 1;
            lastBegin = -1;
        }
    }
    if (lastBegin != -1)
        segs[lastBegin] = n;

    // Add states onto 2D BIT
    for (auto &seg : segs) {
        updRect(seg.first, seg.first, seg.second, seg.second, X({1, 0}));
    }
    
    for (int i = 0; i < q; i++) {
        // CurTime = i + 1
        scan(bt, ba);

        // Debug
        // vector<pair<int, int>> vss(segs.begin(), segs.end());
        // debug(i, vss);
        // for (int j = 1; j <= n; j++) {
        //     vector<int> vc;
        //     for (int k = 1; k <= n; k++) {
        //         auto sumv = sum(j, k);
        //         // debug(j, k, sumv, sumv.gety(i + 1));
        //         vc.push_back(sumv.gety(i + 1));
        //     }
        //     debug(vc);
        // }

        if (bt == "query") {
            scan(bb);
            bb--;

            cout << sum(ba, bb).gety(i + 1) << "\n";
        }
        else { // bt == "toggle"
            if (state[ba]) {
                // Find state to split
                auto ptr = --segs.upper_bound(ba);
                // There should always be an L who is less than the current thing

                updRect(ptr->first, ba, ba, ptr->second, X({-1, i + 1}));

                if (ba + 1 <= ptr->second)
                    segs[ba + 1] = ptr->second;
                
                if (ptr->first <= ba - 1)
                    ptr->second = ba - 1;
                else
                    segs.erase(ptr);
            }
            else { // !state[ba]
                // Find states to combine
                auto ptr2 = segs.upper_bound(ba), ptr = ptr2; // ptr = left, ptr2 = right
                // ptr is invalid -> ptr2 == segs.begin(), ptr2 s invalid, ptr2 == segs.end()

                bool condPtr = false, condPtr2 = false;
                if (segs.size()) { // If the segs set is empty, don't try to set the ptr
                    ptr--; // 
                    condPtr = (ptr2 != segs.begin()) && (ptr->second + 1 == ba); 
                    condPtr2 = (ptr2 != segs.end()) && (ptr2->first - 1 == ba);
                }

                int l = condPtr ? ptr->first : ba, r = condPtr2 ? ptr2->second : ba;
                updRect(l, ba, ba, r, X({1, -i - 1}));

                // debug(i, ba, condPtr, condPtr2, l, r);
                
                if (condPtr && condPtr2) { // Both satisfy
                    ptr->second = ptr2->second;
                    segs.erase(ptr2);
                }
                else if (condPtr) { // Left satsfies only
                    ptr->second = ba;
                }
                else if (condPtr2) { // Right satisfies only
                    segs[ba] = ptr2->second;
                    segs.erase(ptr2);
                }
                else
                    segs[ba] = ba; // insert new
            }

            state[ba] ^= true;
        }
    }
    
    // n = 300000;
    // for (int i = 0; i < 300000; i++) {
    //     updRect(i+1, i+1, i+1, i+1, X({1, i}));
    // }
    // for (int i = 0; i < 150000; i++) {
    //     sum(i + 1, i + 1);
    // }

    return 0;
}