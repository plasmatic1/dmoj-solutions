#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

int n;

void solve() {
    int tot = 0, sqn = sqrt(n);
    for (int i = 2; i <= sqn; i++) {
        while (n % i == 0) {
            n /= i;
            tot++;
        }
    }
    tot += n > 1;
    cout << (tot == 1 ? 0 : tot) << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 5;
    while (t--) {
        scan(n);
        solve();
    }

    return 0;
}