//============================================================================
// Name        : lkp18c1p6.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
struct p{
	int i, x, y;
    bool comm;

    bool operator<(const p &o) const{
    	if(x == o.x)
    		return comm < o.comm;
    	return x < o.x;
    }

    bool operator>(const p &o) const{
    	if(x == o.x)
    		return comm < o.comm;
    	return x > o.x;
    }
};

const int MAX = 100001, MPTS = 200001;
int n, m, ba, bb, rsz, ptr = 0;
p pts[MPTS];
unordered_map<int, int> rnk;
ll tot = 0,
    best[MAX],
    mint[MPTS << 2], maxt[MPTS << 2], // min (right), max (left)
    minlazy[MPTS << 3], maxlazy[MPTS << 3];

void init(int i, int l, int r){
    if(l == r){
        mint[i] = 0x3f3f3f3f3f3f3f3f;
        maxt[i] = -0x3f3f3f3f3f3f3f3f;
        return;
    }

    int mid = (l + r) >> 1;
    init(i << 1, l, mid);
    init(i << 1 | 1, mid + 1, r);

    mint[i] = 0x3f3f3f3f3f3f3f3f;
    maxt[i] = -0x3f3f3f3f3f3f3f3f;
}

inline void lazy(ll tree[], ll lazy[], int i){
    if(lazy[i]){
        lazy[i << 1] += lazy[i];
        lazy[i << 1 | 1] += lazy[i];
        tree[i] += lazy[i];
        lazy[i] = 0;
    }
}

// Min query
ll qmin(int i, int l, int r, int ql, int qr){
	if(ql > qr) return 0x3f3f3f3f3f3f3f3f;
    lazy(mint, minlazy, i);
    if(l >= ql && r <= qr) return mint[i];
    if(r < ql || l > qr) return LLONG_MAX;

    int mid = (l + r) >> 1;
    return min(qmin(i << 1, l, mid, ql, qr), qmin(i << 1 | 1, mid + 1, r, ql, qr));
}

// Min Point Update
ll updmin(int i, int l, int r, int q, int v){
    lazy(mint, minlazy, i);
    if(l == q && r == q) return mint[i] = v;
    if(r < q || l > q) return mint[i];

    int mid = (l + r) >> 1;
    return mint[i] = min(updmin(i << 1, l, mid, q, v), updmin(i << 1 | 1, mid + 1, r, q, v));
}

// Min Range Update
ll rngupdmin(int i, int l, int r, int ql, int qr, int v){
    lazy(mint, minlazy, i);
    if(l >= ql && r <= qr){
        minlazy[i] = v;
        lazy(mint, minlazy, i);
        return mint[i];
    }
    if(r < ql || l > qr) return mint[i];

    int mid = (l + r) >> 1;
    return mint[i] = min(rngupdmin(i << 1, l, mid, ql, qr, v), rngupdmin(i << 1 | 1, mid + 1, r, ql, qr, v));
}

// Max Query
ll qmax(int i, int l, int r, int ql, int qr){
	if(ql > qr) return -0x3f3f3f3f3f3f3f3f;
    lazy(maxt, maxlazy, i);
    if(l >= ql && r <= qr) return maxt[i];
    if(r < ql || l > qr) return LLONG_MIN;

    int mid = (l + r) >> 1;
    return max(qmax(i << 1, l, mid, ql, qr), qmax(i << 1 | 1, mid + 1, r, ql, qr));
}

// Max Point Update
ll updmax(int i, int l, int r, int q, int v){
    lazy(maxt, maxlazy, i);
    if(l == q && r == q) return maxt[i] = v;
    if(r < q || l > q) return maxt[i];

    int mid = (l + r) >> 1;
    return maxt[i] = max(updmax(i << 1, l, mid, q, v), updmax(i << 1 | 1, mid + 1, r, q, v));
}

// Max Range Update
ll rngupdmax(int i, int l, int r, int ql, int qr, int v){
    lazy(maxt, maxlazy, i);
    if(l >= ql && r <= qr){
        maxlazy[i] = v;
        lazy(maxt, maxlazy, i);
        return maxt[i];
    }
    if(r < ql || l > qr) return maxt[i];

    int mid = (l + r) >> 1;
    return maxt[i] = max(rngupdmax(i << 1, l, mid, ql, qr, v), rngupdmax(i << 1 | 1, mid + 1, r, ql, qr, v));
}

// line sweep
inline void run(){
    int last = pts[0].x;
    for(int i = 0; i < ptr; i++){
        int idx = rnk[pts[i].y], diff = abs(pts[i].x - last);

        // Change diffs
        rngupdmax(1, 1, rsz, 1, rsz, -diff);
        rngupdmin(1, 1, rsz, 1, rsz, diff);

        if(pts[i].comm){ // Community
            ll retmax = qmax(1, 1, rsz, 1, idx), retmin = qmin(1, 1, rsz, idx + 1, rsz);
            best[pts[i].i] = min(best[pts[i].i], min(pts[i].y - retmax, retmin - pts[i].y));
        }
        else{ // Bunker
            updmin(1, 1, rsz, idx, pts[i].y);
            updmax(1, 1, rsz, idx, pts[i].y);
        }

        last = pts[i].x;
    }
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    set<int> trnk;

	cin >> n;

    for(int i = 0; i < n; i++){
        cin >> ba >> bb;
        pts[ptr++] = {i, ba, bb, true};
        trnk.insert(bb);
    }

    cin >> m;

    for(int i = 0; i < m; i++){
        cin >> ba >> bb;
        pts[ptr++] = {-1, ba, bb, false};
        trnk.insert(bb);
    }

    int idx = 1;
    for(int i : trnk)
        rnk[i] = idx++;
    rsz = rnk.size();

    fill(best, best + n, LLONG_MAX);

    sort(pts, pts + ptr);
    init(1, 1, ptr);
    run();

    sort(pts, pts + ptr, greater<p>()); // Have to sort since bunkers before communities
    init(1, 1, ptr);
    run();

    for(int i = 0; i < n; i++)
        tot += best[i];

    printf("%lld\n", tot);
}