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

struct p{
	double x, y;
};

int n;
p pts[3];

inline double dis(p &a, p &b) {
	double dx = b.x - a.x, dy = b.y - a.y;
	return sqrt(dx * dx + dy * dy);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 3; j++)
			scan(pts[j].x, pts[j].y);

		double sa = dis(pts[0], pts[1]), sb = dis(pts[1], pts[2]), sc = dis(pts[0], pts[2]),
				perim = sa + sb + sc, sperim = perim / 2.;

		printf("%.6f %.6f\n", sqrt(sperim * (sperim - sa) * (sperim - sb) * (sperim - sc)), perim);
	}
}