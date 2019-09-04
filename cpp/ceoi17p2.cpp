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

const double PREC = 1e-6;
const int MN = 1e5 + 1;
int n;
double a[MN], b[MN];

double sim(double target) {
    double pa = 0., pb = 0.;
    int aptr = 0, bptr = 0;

    bool flaga = false, flagb = false;
    do {
        flaga = flagb = false;

        // debug(pa, pb, aptr, bptr, a[aptr], b[bptr]);

        while (aptr < n && pa < target) {
            flaga = true;
            pa += a[aptr++] - 1.;
            pb--;
        }
        
        while (bptr < n && pb < target) {
            flagb = true;
            pa--;
            pb += b[bptr++] - 1.;
        }
    } while (flaga || flagb);

    return min(pa, pb) >= target;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 0; i < n; i++)
        scan(a[i], b[i]);
    
    sort(a, a + n, greater<double>());
    sort(b, b + n, greater<double>());

    // printArray(cout, a, n); cout << "\n";

    // sim(0.5);

    double l = 0, r = 1e9;
    while (l + PREC < r) {
        double mid = (l + r) / 2.;
        if (sim(mid))
            l = mid;
        else
            r = mid;
    }

    // debug(l, r);
    cout << fixed << setprecision(4) << l << "\n";

    return 0;
}