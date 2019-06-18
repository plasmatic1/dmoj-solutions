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

int a, b, c, d, e, f,
    creeper, ender, mag;

double euclid() {
    double dx = d - a, dy = e - b, dz = f - c;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(a, b, c, d, e, f);

    int dx = abs(d - a), dy = abs(e - b), dz = abs(f - c);

    cout << (max(dx, max(dy, dz))) << "\n";
    cout << (int)(euclid()) << "\n";
    cout << (dx + dy + dz) << "\n";

    return 0;
}