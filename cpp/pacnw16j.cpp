#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct qu {
    int i, l, r;
    ll v;

    bool operator<(const qu &o) const {
        return l < o.l;
    }
};

// Reverse for PQueue
class RComp {
    public:
    bool operator()(const qu &a, const qu &b) {
        return a.r > b.r;
    }
};

const int MAX = 200001, MSQ = 450 + 11;
int n, q,
    blockn[MAX], blockl[MAX], blockr[MAX];
ll arr[MAX], ans[MAX], sqrtArr[MAX];
qu queries[MAX];
priority_queue<qu, vector<qu>, RComp> curQus;
vector<ll> delta[MSQ];

inline void updateBlock(int block) {
    if(delta[block].size() > (size_t)0) {
        for (int i = blockl[block]; i <= blockr[block]; i++) {
            if (!sqrtArr[i])
                continue;
            
            // printf("i=%d cDelta=[\n", i);
            // for(ll x : delta[block]) printf("%lld, ", x);
            // printf("\n");
            int cnt = 100;
            
            vector<ll> &cDelta = delta[block];
            int idx = 0, sz = cDelta.size();
            while(idx < sz) {
                assert(cnt--);
                sqrtArr[i] %= cDelta[idx];
                // printf("sqv=%lld, idx=%d\n", sqrtArr[i], idx);

                int l = idx, r = sz;
                while(l + 1 < r) {
                    int mid = (l + r) >> 1;
                    if(cDelta[mid] > sqrtArr[i])
                        l = mid;
                    else
                        r = mid;
                }
                idx = r;
            }
        }
        delta[block].clear();
    }
}

inline ll getVal(int idx) {
    updateBlock(blockn[idx]);
    return sqrtArr[idx];
}

inline void setVal(int idx, ll val) {
    updateBlock(blockn[idx]);
    sqrtArr[idx] = val;
}

inline void modAll(int maxBlock, ll modVal) {
    for (int i = 0; i <= maxBlock; i++)
        if (delta[i].empty() || delta[i][delta[i].size() - (size_t)1] > modVal)
            delta[i].push_back(modVal);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Input
    scan(n, q);

    for (int i = 1; i <= n; i++)
        scan(arr[i]);        

    memset(blockl, 0x3f, sizeof blockl);    
    int sqq = sqrt(q), lastBlock = (q - 1) / sqq;
    for (int i = 0; i < q; i++) {
        scan(queries[i].v, queries[i].l, queries[i].r);
        queries[i].i = i;

        blockn[i] = i / sqq;
        blockl[blockn[i]] = min(blockl[blockn[i]], i);
        blockr[blockn[i]] = max(blockr[blockn[i]], i);
    }
    sort(queries, queries + q);

    // Offline processing (1. Add new queries, 2. Mod all values by arr[i], 3. Answer all queries ending at r)
    int qptr = 0;
    for (int i = 1; i <= n; i++) {
        while(qptr < q && queries[qptr].l == i) {
            setVal(queries[qptr].i, queries[qptr].v);
            curQus.push(queries[qptr]);
            qptr++;
        }

        modAll(lastBlock, arr[i]);

        while(!curQus.empty() && curQus.top().r == i) {
            int idx = curQus.top().i;
            ans[idx] = getVal(idx);
            curQus.pop();
        }
    }

    for (int i = 0; i < q; i++)
        printf("%lld\n", ans[i]);

    return 0;
}