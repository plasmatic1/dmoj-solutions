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

void solveProblem(ostream& out, int n, int arr[3]) {
    int ans[3];

    for (int i = 2; i >= 0; i--) {
        int sub = min(n, arr[i]);
        ans[i] = sub;
        n -= sub;
    }

    if (n != 0)
        out << "-1\n";
    else {
        for (int i = 0; i < 3; i++)
            out << ans[i] << " ";
        out << "\n";
    }
}

int n, arr[3];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; scan(t);
    while (t--) {
        scan(n, arr[0], arr[1], arr[2]);
        assert(1 <= n && n <= 1e9);
        assert(1 <= arr[0] && arr[0] <= 1e9);
        assert(1 <= arr[1] && arr[1] <= 1e9);
        assert(1 <= arr[2] && arr[2] <= 1e9);
        solveProblem(cout, n, arr);
    }

    return 0;
}