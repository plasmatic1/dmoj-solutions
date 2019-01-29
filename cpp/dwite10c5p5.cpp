//============================================================================
// Name        : CubeWorld.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 21, MAXH = 51;
int n, m, total = 0,
	arr[MAX][MAX];

p adjs[4];
inline void setup_adjs(int i, int j){
	adjs[0] = {i - 1, j};
	adjs[1] = {i + 1, j};
	adjs[2] = {i, j - 1};
	adjs[3] = {i, j + 1};
}

int casec = 5;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	for (int aisdughadsiufhdsiufhadsiufhsa = 0; aisdughadsiufhdsiufhadsiufhsa < casec; ++aisdughadsiufhdsiufhadsiufhsa) {
		cin >> n >> m; //Literally O(4) but who gives a crap

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= m; ++j) {
				cin >> arr[i][j];
			}
		}

//		memset(vis, -1, sizeof(vis));

		for (int i = 2; i < n; ++i) {
			for (int j = 2; j < m; ++j) {
				for (int k = arr[i][j]; k < MAXH - 1; ++k) {
					bool vis[n + 1][m + 1];
					memset(vis, false, sizeof(vis));

					deque<p> nextt;
					bool works = true;
					nextt.push_back({i, j});
					vis[i][j] = true;

					while(!nextt.empty()){
						p curr = nextt.front();
						nextt.pop_front();
						bool bk = false;

						setup_adjs(curr.first, curr.second);
						for(p adj : adjs){
							if(vis[adj.first][adj.second]){
								continue;
							}

							if(arr[adj.first][adj.second] > k){
								continue;
							}

							if(adj.first < 2 || adj.first >= n || adj.second < 2 || adj.second >= m){
//								printf("for i=%d, j=%d, k=%d is over\n", adj.first, adj.second, k);

								works = false;
								bk = true;
								break;
							}

							vis[adj.first][adj.second] = true;
							nextt.push_back({adj.first, adj.second});
						}

						if(bk){
							break;
						}
					}

					if(works){
						total++;
					}
					else{
						break;
					}
				}
			}
		}

		printf("%d\n", total);
		total = 0;
	}
}
