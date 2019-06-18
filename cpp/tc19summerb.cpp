#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct p {
    double pro; int roomNo;
    bool operator<(const p &o) const {
        return pro < o.pro;
    }
};

const int MAX = 500001;
int n, bc, totCam = 0;
priority_queue<double> bex[MAX]; // sex in bed
priority_queue<p> pro;
double ans = 0, bv,
    proLeft[MAX];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++) {
        scan(bc);
        totCam += bc;

        for (int j = 0; j < bc; j++) {
            scan(bv);
            bex[i].push(bv);
        }
        
        pro.push({bex[i].top(), i});
        bex[i].pop();
        proLeft[i] = 1.;
    }

    while(totCam--) {
        auto cur = pro.top(); //debug(ans, cur.pro, proLeft[cur.roomNo], cur.roomNo);
        ans += cur.pro;
        proLeft[cur.roomNo] -= cur.pro;
        pro.pop();
        
        if (!bex[cur.roomNo].empty()) {
            pro.push({bex[cur.roomNo].top() * proLeft[cur.roomNo], cur.roomNo});
            bex[cur.roomNo].pop();
        }

        printf("%.8f\n", ans);
    }

    return 0;
}