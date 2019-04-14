//===========================================================================
// Name        : coci17c2p3.cpp
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
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

const int MAX = 500001;
int n,
	arr[MAX], samePoint[MAX];
unordered_map<double, vector<int>> fixPoints;

double currMid;
bool cmp(const int &a, const int &b){
    return abs(a - currMid) < abs(b - currMid);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	scan(n);
	for(int i = 1; i <= n; i++){
		scan(arr[i]);

		double fixPoint = (i + arr[i]) / 2.;
		fixPoints[fixPoint].push_back(i);
		if(fixPoint == (double)i)
			samePoint[i]++;
		samePoint[i] += samePoint[i - 1];
	}

	int best = 0, bestl, bestr, allPoints = samePoint[n];
	for (pair<double, vector<int>> pi : fixPoints){
        int idx = pi.first;
        bool isDec = pi.first != (int)pi.first; // Is decimal midpoint

        vector<int> idxs = pi.second;
        currMid = pi.first;
        sort(idxs.begin(), idxs.end());

        for (int x : idxs){
            int left, right;
            if(x <= idx + isDec){
                left = x;
                right = idx + isDec + (idx - x);
            }
            else{
                right = x;
                left = idx - (right - (idx + isDec));
            }
            
            int ans = -(samePoint[right] - samePoint[left - 1]) + allPoints + 
                    (upper_bound(idxs.begin(), idxs.end(), right) - lower_bound(idxs.begin(), idxs.end(), left));
            
            // debug(x, idx, pi.first, left, right, ans, isDec);
            
            if(ans > best){
                best = ans;
                bestl = arr[left];
                bestr = arr[right];
            }
        }
    }

	printf("%d %d\n", bestl, bestr);
}