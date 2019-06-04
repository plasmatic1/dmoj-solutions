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

const int MAX = 1000001;
int n,
    arr[MAX], tree[MAX];
string s, t;
unordered_map<char, deque<int>> idxs;
ll tot = 0;

inline int sum(int x) {
    int sum = 0;
    for (; x; x -= x & -x)
        sum += tree[x];
    return sum;
}

inline void add(int x, int v) {
    for(; x <= n; x += x & -x)
        tree[x] += v;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(n, s, t);

    for (int i = 1; i <= n; i++)
        idxs[t[i - 1]].push_back(i);
    
    for (int i = 1; i <= n; i++) {
        int idx = idxs[s[i - 1]].front();
        idxs[s[i - 1]].pop_front();
        
        tot += sum(n) - sum(idx);
        add(idx, 1);
    }

    printf("%lld\n", tot);

    return 0;
}
