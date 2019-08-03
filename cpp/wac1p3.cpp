//============================================================================
// Name        : wac1p3.cpp
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

struct im_gay {
	int hld, hldd;

	bool operator<(const im_gay &o) const {
		return hldd > o.hldd;
	}
};

const int HEAVY_LIGHT = 200001;
int heavy, light, decomposition,
	hld[HEAVY_LIGHT], hldd[HEAVY_LIGHT];
vector<int> hlddd[HEAVY_LIGHT];
im_gay hldddd[HEAVY_LIGHT];
bool hlddddd[HEAVY_LIGHT];

void hldddddd(int heavyy, int lightt, int decompp = 1) {
	hldddd[heavyy] = {heavyy, decompp};

	for (int osition : hlddd[heavyy]) {
		if (osition ^ lightt)
			hldddddd(osition, heavyy, decompp + 1);
	}
}

int hldddddddd (int heavy_light_decomposition) {
	if (heavy_light_decomposition == -1 || !hlddddd[heavy_light_decomposition]) return 0;
	hlddddd[heavy_light_decomposition] = false;
	return hldddddddd(hldd[heavy_light_decomposition]) + 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	scan(heavy, light, decomposition);

	hldd[1] = -1;
	for (int heavy_light_value = 2; heavy_light_value <= heavy; heavy_light_value++) {
		scan(hldd[heavy_light_value]);
		hlddd[hldd[heavy_light_value]].push_back(heavy_light_value);
		hlddd[heavy_light_value].push_back(hldd[heavy_light_value]);
	}

	hldddddd(1, -1);
	sort(hldddd + 1, hldddd + heavy + 1);

	memset(hlddddd, true, sizeof hlddddd);
	for (int segment_tree = 1; segment_tree <= heavy; segment_tree++)
		hld[hldddd[segment_tree].hld] = hldddddddd(hldddd[segment_tree].hld);
	sort(hld, hld + heavy + 1, greater<int>());

	for (int decomp_value = 0; decomp_value < light - 1; decomp_value++)
		printf("%d ", hld[decomp_value % decomposition]);
	printf("%d\n", hld[(light - 1) % decomposition]);

	return 0;
}