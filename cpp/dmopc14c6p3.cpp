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

const int MAX = 100001;
int n,
    cnt[MAX];
double prec[MAX];

int ans(int busSize) {
    vector<int> busses;

    for (int i = 0; i < n; i++) {
        int sz = busses.size();
        for (int j = 0; j < sz; j++)
            busses[j] -= (int)(busses[j] * prec[i]);

        int ccnt = cnt[i];
        for (int j = 0; j < sz; j++) {
            int add = min(busSize - busses[j], ccnt);
            busses[j] += add;
            ccnt -= add;
        }

        while (ccnt > 0) {
            int add = min(busSize, ccnt);
            busses.push_back(add);
            ccnt -= add;
        }

        // debug(i);
        // cout << "busses: [";
        // for (auto x : busses) {
        //     cout << x << ", ";
        // }
        // cout << "\n";
    }

    return busses.size();
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++) {
        scan(cnt[i], prec[i]);
        prec[i] = prec[i] / 100.;
    }
    
    cout << ans(132) - ans(251) << "\n";

    return 0;
}