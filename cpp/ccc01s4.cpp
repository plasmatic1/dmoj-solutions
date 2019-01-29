//============================================================================
// Name        : Cookies.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 10;
int n,
	x[MAX], y[MAX];
double mdist = 0.;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> x[i] >> y[i];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			for (int k = j + 1; k < n; ++k) {
				if(x[i] == x[j] && x[j] == x[k]){
					mdist = max(mdist, ((double)max(y[i], max(y[j], y[k])) - min(y[i], max(y[j], y[k]))) / 2.);
					continue;
				}
				else if(y[i] == y[j] && y[j] == y[k]){
					mdist = max(mdist, ((double)max(x[i], max(x[j], x[k])) - min(x[i], max(x[j], x[k]))) / 2.);
					continue;
				}

				double dax = x[k] - x[j], dbx = x[j] - x[i], dcx = x[k] - x[i], day = y[k] - y[j], dby = y[j] - y[i],
					dcy = y[k] - y[i], da = sqrt(dax * dax + day * day), db = sqrt(dbx * dbx + dby * dby), dc = sqrt(dcx * dcx + dcy * dcy),
					semi = (da + db + dc) / 2;

				double sides[3] = {da, db, dc};
				sort(sides, sides + 3);

				if(sides[2] * sides[2] > sides[0] * sides[0] + sides[1] * sides[1]){
					mdist = max(mdist, sides[2] / 2.);
				}
				else{
					mdist = max(mdist, da * db * dc / 4. / sqrt(semi * (semi - da) * (semi - db) * (semi - dc)));
				}
			}
		}
	}

	printf("%.10f\n", mdist * 2.);
}
