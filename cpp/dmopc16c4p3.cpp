//============================================================================
// Name        : CarnivalPhantasm.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

const int MAX = 100001, FLAV_MAX = 101;

struct stand{
	int id, dist;

	stand(int idd, int distt) : id(idd), dist(distt){
		//
	}

	stand(){
		id = -1;
		dist = -1;
	}

	friend bool operator<(const stand &a, const stand &b){
		return a.dist > b.dist;
	}
};

int n, s, q, buf, buf2;
char buf_c;
int curr_dist[MAX];
bool curr_apple[MAX][FLAV_MAX];
priority_queue<stand> apples[FLAV_MAX];

int main(){
	cin >> n >> s;

	memset(curr_apple, false, sizeof(curr_apple));

	for (int i = 0; i < n; ++i) {
		cin >> buf;

		curr_dist[i + 1] = buf;
	}

	for (int i = 0; i < s; ++i) {
		cin >> buf >> buf2;
		//buf (stand) (apple)

		apples[buf2].emplace(buf, curr_dist[buf]);
		curr_apple[buf][buf2] = true;
	}

	cin >> q;

	for (int i = 0; i < q; ++i) {
		cin >> buf_c >> buf;

//		printf("Qu: %c, %d\n", buf_c, buf);

		if(buf_c == 'Q'){
			// buf (apple)
			if(!apples[buf].empty()){
				stand top = apples[buf].top();
				while(top.dist != curr_dist[top.id]){ //Get rid of defunct values
					apples[buf].pop();
					apples[buf].push(stand(top.id, curr_dist[top.id]));
					top = apples[buf].top();
				}

//				printf("found normal top (%d %d)\n", top.id, top.dist);
//				assert(false);

				while(!apples[buf].empty() && !curr_apple[top.id][buf]){
					apples[buf].pop();
					top = apples[buf].top();
//					printf("top is %d %d\n", top.id, top.dist);
//					assert(false);
				}

//				assert(false);

				if(apples[buf].empty()){
					printf("-1\n");
				}
				else{
					printf("%d\n", top.id);
				}
			}
			else{
				printf("-1\n");
			}

			continue;
		}

		cin >> buf2;
		// buf (stand, apple)

		if(buf_c == 'A'){
			apples[buf2].emplace(buf, curr_dist[buf]);
			curr_apple[buf][buf2] = true;
		}
		else if(buf_c == 'S'){
			curr_apple[buf][buf2] = false;
		}
		else{
			//Query is E

			curr_dist[buf] = buf2;
			memset(curr_apple[buf], false, sizeof(curr_apple[buf]));
		}
	}

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
}
