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

struct seg {
    int pfxMax, sfxMax, sum, lazy, l, r; // All initialized to 0 in global struct
    // seg() : pfxMax(0), sfxMax(0), totMax(0), sum(0), lazy(0), l(nullptr), r(nullptr) {}
};
const int MP = 8000001;
seg nodes[MP], zeroSeg;

inline int make() {
    static int cptr = 0;
    assert(cptr + 1 < MP);
    return ++cptr;
}

inline void setNode(int nd, int l, int r, int val) {
    // Assign values
    int sz = r - l + 1;
    nodes[nd].sum = sz * (val == -INF ? 0 : val); // -INF as placeholder for 0LL

    if (val > 0)
        nodes[nd].pfxMax = nodes[nd].sfxMax = nodes[nd].sum;
    else
        nodes[nd].pfxMax = nodes[nd].sfxMax = 0LL;
}

inline void pushDown(int &nd, int l, int r) {
    if (nodes[nd].lazy && (l ^ r)) {
        if (!nodes[nd].l) nodes[nd].l = make();
        if (!nodes[nd].r) nodes[nd].r = make();

        // Set child values
        int mid = (l + r) >> 1;
        setNode(nodes[nd].l, l, mid, nodes[nd].lazy);
        setNode(nodes[nd].r, mid + 1, r, nodes[nd].lazy);

        // Propagate and finalize
        nodes[nodes[nd].l].lazy = nodes[nodes[nd].r].lazy = nodes[nd].lazy;
        nodes[nd].lazy = 0;
    }
}

inline void mergeNodes(seg &nd, seg l, seg r) {
    nd.sum = l.sum + r.sum;
    nd.pfxMax = max(l.pfxMax, l.sum + r.pfxMax);
    nd.sfxMax = max(r.sfxMax, l.sfxMax + r.sum);
    // nd.totMax = max(l.sfxMax + r.pfxMax, max(l.totMax, r.totMax));
}

seg upd(int &rt, int l, int r, int ql, int qr, int qv) {
    if (!rt)
        rt = make();

    if (l >= ql && r <= qr) {
        nodes[rt].lazy = qv;
        setNode(rt, l, r, qv);
        // debug("full", l, r, ql, qr, qv, nodes[rt].sum);
        return nodes[rt];
    }
    if (l > qr || r < ql) return nodes[rt];
    pushDown(rt, l, r);
    
    int mid = (l + r) >> 1;
    mergeNodes(nodes[rt], upd(nodes[rt].l, l, mid, ql, qr, qv), upd(nodes[rt].r, mid + 1, r, ql, qr, qv));
    // debug(l, r, ql, qr, qv, nodes[rt].sum, nodes[rt].pfxMax, nodes[rt].sfxMax);

    return nodes[rt];
}

seg query(int &rt, int l, int r, int ql, int qr) {
    if (!rt)
        return zeroSeg;
    
    if (l >= ql && r <= qr) return nodes[rt];
    if (l > qr || r < ql) return zeroSeg;
    pushDown(rt, l, r);

    int mid = (l + r) >> 1;
    seg nd;
    mergeNodes(nd, query(nodes[rt].l, l, mid, ql, qr), query(nodes[rt].r, mid + 1, r, ql, qr));
    return nd;
}

int n, ba, bb, bd;
char bt;
int tree = 0;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    do {
        scan(bt);

        if (bt == 'I') {
            scan(ba, bb, bd);

            if (bd == 0)
                bd = -INF;
            upd(tree, 1, n, ba, bb, bd);
        }
        else if (bt == 'Q') {
            scan(ba);

            int l = 0, r = n + 1;
            while (l + 1 < r) {
                int mid = (l + r) >> 1;
                
                auto ans = query(tree, 1, n, 1, mid).pfxMax; //debug(l, r, mid, ans);
                if (ans <= ba)
                    l = mid;
                else
                    r = mid;
            }

            // debug(l, r);
            cout << l << "\n";
        }
    } while (bt != 'E');

    // Test Memory
    // mt19937 mt(time(NULL));
    // for (int i = 0; i < 50000; i++) {
    //     uniform_int_distribution<int> dis(1, 1e9);
    //     int l = dis(mt), r = dis(mt);
    //     if (l > r) swap(l, r);
    //     upd(tree, 1, 1000000000, l, r, dis(mt));

    //     l = dis(mt); r = dis(mt);
    //     if (l > r) swap(l, r);
    //     query(tree, 1, 1000000000, l, r);
    // }

    return 0;
}