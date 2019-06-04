//============================================================================
// Name        : naq16d.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f, R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct p {
	int i; char c;
};

const int MAX = 5001;
int n,
	vals[MAX], mins[MAX][MAX], maxs[MAX][MAX];
string s;

inline int sumOf(int l, int r) { return vals[r] - vals[l - 1]; }
inline int minOf(int l, int r) { return mins[l][r]; }
inline int maxOf(int l, int r) { return maxs[l][r]; }

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(s);
	n = s.length();

	for (int i = 0; i < n; i++) {
		int dif = s[i] == '(' ? 1 : -1;
		vals[i] = dif;
		if (i > 0)
			vals[i] += vals[i - 1];
	}

	if (vals[n - 1] == 0 && *min_element(vals, vals + n) >= 0) {
		cout << "possible\n";
		return 0;
	}

	copy(vals, vals + n, vals + 1); vals[0] = 0;

	for (int i = 1; i <= n; ++i) {
		int cmin = 0x3f3f3f3f, cmax = -0x3f3f3f3f;
		for (int j = i; j <= n; ++j) {
			cmin = min(cmin, vals[j] - vals[i - 1]);
			cmax = max(cmax, vals[j] - vals[i - 1]);
			mins[i][j] = cmin;
			maxs[i][j] = cmax;
		}
	}

	int dif = vals[n];
	for (int i = 1; i <= n; ++i) {
		for (int j = i; j <= n; ++j) {
			bool flag = dif - (sumOf(i, j) << 1) == 0 && sumOf(1, i - 1) - maxOf(i, j) >= 0;
			if (i > 1)
				flag &= minOf(1, i - 1) >= 0;
			if (j < n)
				flag &= sumOf(1, i - 1) - sumOf(i, j) + minOf(j + 1, n) >= 0;

//			int so = minOf(i, j); debug(i, j, so);

			if (flag) {
//				debug(i, j);

				cout << "possible\n";
				return 0;
			}
		}
	}

	cout << "impossible\n";
}