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

template <typename S>
struct p {
    S x, y;
    friend istream& operator>>(istream& in, p& obj) { in >> obj.x >> obj.y; return in; }
    friend ostream& operator<<(ostream& out, const p obj) { out << "(x=" << obj.x << ", y=" << obj.y << ")"; return out; }
};
struct Heron {
    double prec;
    Heron(double prec0) : prec(prec0) {}
    bool roughlyEqual(double a, double b) {
        return abs(a - b) < prec;
    }
    template <typename T> double dis(p<T> a, p<T> b) { // Distance between line segment (a, b)
        T da = b.x - a.x, db = b.y - a.y;
        return sqrt(da * da + db * db);
    }
    template <typename T> double heron(p<T> a, p<T> b, p<T> c) { // Area of triangle (a, b, c)
        double da = dis(a, b), db = dis(b, c), dc = dis(a, c), semi = (da + db + dc) / 2.;
        return sqrt(semi * (semi - da) * (semi - db) * (semi - dc));
    }
    template <typename T> bool contains(p<T> a, p<T> b, p<T> c, p<T> pt, bool strict) { // Checks whether triangle (a, b, c) contains point pt
        double tot = heron(a, b, c), area1 = heron(a, b, pt), area2 = heron(b, c, pt), area3 = heron(a, c, pt);
        // debug(tot, a.x, a.y, b.x, b.y, c.x, c.y);
        return (!strict || (area1 != 0 && area2 != 0 && area3 != 0)) 
            && roughlyEqual(area1 + area2 + area3, tot);
    }
};

const int MAX = 31;
int n, tot = 0;
p<int> pts[MAX];
Heron heron(1e-6);

void solve() {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                tot += heron.contains(pts[i], pts[j], pts[k], {0, 0}, true);

    cout << tot << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 2;
    while (t--) {
        scan(n);
        for (int i = 0; i < n; i++)
            scan(pts[i]);
        tot = 0;

        solve();
    }

    return 0;
}