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

/*
* types
* 1 -> snowflake insert
* 2 -> snowflake delete
* 3 -> query - row
* 4 -> query - col
* 5 -> query - both
*/
struct qu {
    int type, idx, x, y, x2, y2, time;

    bool operator<(const qu &o) const {
        if(time == o.time)
            return type < o.type;
        return time < o.time;
    }
};

const int MAX = 5001, MM = 100001, MQ = 100001, MTOT = (MM + MQ) << 1;
int n, m, q, ba, bb, bc, bd, bt,
    rowTree[MAX], colTree[MAX], tree[MAX][MAX], ans[MQ];
qu items[MTOT];
char bType;

inline int sum(int tree[MAX], int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += tree[x];
    return sum;
}

inline void add(int tree[MAX], int x, int v) {
    for(; x <= n; x += x & -x)
        tree[x] += v;
}

inline int sum2D(int x, int y) {
    int sum = 0;
    for (int cx = x; cx; cx -= cx & -cx)
        for (int cy = y; cy; cy -= cy & -cy)
            sum += tree[cx][cy];
    
    return sum;
}

inline int sum2DRange(int x, int y, int x2, int y2) {
    return sum2D(x2, y2) - sum2D(x - 1, y2) - sum2D(x2, y - 1) + sum2D(x - 1, y - 1);
}

inline void add2D(int x, int y, int v) {
    for (int cx = x; cx <= n; cx += cx & -cx)
        for (int cy = y; cy <= n; cy += cy & -cy)
            tree[cx][cy] += v;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n, m, q);
    int itemPtr = 0;

    for (int i = 0; i < m; i++) {
        scan(ba, bb, bc, bd); // x, y, add time, delete time
        items[itemPtr++] = {1, -1, ba, bb, -1, -1, bc};
        items[itemPtr++] = {2, -1, ba, bb, -1, -1, bd};
    }

    for (int i = 0; i < q; i++) {
        scan(bType);

        if(bType == 'R') {
            scan(ba, bb, bt);
            items[itemPtr++] = {3, i, ba, bb, -1, -1, bt};
        }
        else if(bType == 'C') {
            scan(ba, bb, bt);
            items[itemPtr++] = {4, i, ba, bb, -1, -1, bt};
        }
        else { // bType == 'V'
            scan(ba, bb, bc, bd, bt);
            items[itemPtr++] = {5, i, ba, bb, bc, bd, bt};
        }
    }

    sort(items, items + itemPtr);

    // it.x = row, it.y = col
    for (int i = 0; i < itemPtr; i++) {
        qu it = items[i];

        if(it.type == 1) { // Insert
            add(rowTree, it.x, 1);
            add(colTree, it.y, 1);
            add2D(it.x, it.y, 1);
        }
        else if(it.type == 2) {
            add(rowTree, it.x, -1);
            add(colTree, it.y, -1);
            add2D(it.x, it.y, -1);
        }
        else if(it.type == 3) // row
            ans[it.idx] = sum(rowTree, it.y) - sum(rowTree, it.x - 1);
        else if(it.type == 4) // col
            ans[it.idx] = sum(colTree, it.y) - sum(colTree, it.x - 1);
        else { // it.type == 5, row and col (Rectangle (it.x, it.x2) -> (it.y, it.y2))
            ans[it.idx] = sum(rowTree, it.y) - sum(rowTree, it.x - 1) + sum(colTree, it.y2) - sum(colTree, it.x2 - 1)
                - sum2DRange(it.x, it.x2, it.y, it.y2);
        }
    }

    for (int i = 0; i < q; i++)
        printf("%d\n", ans[i]);

    return 0;
}