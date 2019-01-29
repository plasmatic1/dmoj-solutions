//============================================================================
// Name        : LeftoverEggnog.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct cups{
	int a, b;

	cups(int a0, int b0) : a(a0), b(b0){}
	cups() : a(-1), b(-1){}
};

struct trip{
	int a, b, c;

	trip(int a0, int b0, int c0) : a(a0), b(b0), c(c0){}
	trip() : a(-1), b(-1), c(-1){}
};

struct adjec{
	cups cup;
	trip ins;

	adjec(cups c, trip i) : cup(c), ins(i){}
	adjec(){}
};

const int MAX = 1001;

int va, vb, m, buf,
	levels[MAX][MAX];

adjec par[MAX][MAX]; //1 = fill, 2 = chug, 3 = pour

deque<cups> nextt;

// Does 1 -> 'A', 2 -> 'B'
inline char getlet(int leti){
	return leti == 1 ? 'A' : 'B';
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> va >> vb >> m;

	memset(levels, 0x3f, sizeof(levels));
	nextt.emplace_back(0, 0);
	levels[0][0] = 0;

	while(!nextt.empty()){
		cups curr = nextt.front();
		int nlevel = levels[curr.a][curr.b] + 1;
		nextt.pop_front();

		int pouramta = min(curr.a, vb - curr.b), pouramtb = min(curr.b, va - curr.a);

		for(adjec adj : {adjec(cups(va, curr.b), trip(1, 1, -1)), adjec(cups(curr.a, vb), trip(1, 2, -1)),
			adjec(cups(curr.a - pouramta, curr.b + pouramta), trip(2, 1, 2)),
			adjec(cups(curr.a + pouramtb, curr.b - pouramtb), trip(2, 2, 1)),
			adjec(cups(0, curr.b), trip(3, 1, -1)), adjec(cups(curr.a, 0), trip(3, 2, -1))}){

			if(nlevel < levels[adj.cup.a][adj.cup.b]){
				levels[adj.cup.a][adj.cup.b] = nlevel;
				par[adj.cup.a][adj.cup.b] = adjec(curr, adj.ins);

				nextt.emplace_back(adj.cup.a, adj.cup.b);
			}
		}
	}

	// Getting stuff

	// Getting best path
	int minv = 0x3f3f3f3f, mini = -1, ab = -1;

	for (int i = 0; i < MAX; ++i) {
		if(levels[m][i] < minv){
			minv = levels[m][i];
			mini = i;
			ab = 1;
		}

		if(levels[i][m] < minv){
			minv = levels[i][m];
			mini = i;
			ab = 2;
		}
	}

	// If not possible
	if(minv == 0x3f3f3f3f){
		printf("Not possible\n");
		return 0;
	}

	// Else if possible

	int cx = -1, cy = -1;

	if(ab == 1){
		cx = m;
		cy = mini;
	}
	else if(ab == 2){
		cx = mini;
		cy = m;
	}

//	printf("cx=%d cy=%d\n", cx, cy);
//	printf("minlvl=%d\n", minv);

	// Getting instructions
	vector<adjec> instructs;

	while(cx != 0 || cy != 0){
		adjec cpar = par[cx][cy];

		instructs.push_back(cpar);

		cx = cpar.cup.a;
		cy = cpar.cup.b;
	}

	reverse(instructs.begin(), instructs.end());

	for(adjec cpar : instructs){
		if(cpar.ins.a == 1){
			printf("fill %c\n", getlet(cpar.ins.b));
		}
		else if(cpar.ins.a == 2){
			printf("pour %c %c\n", getlet(cpar.ins.b), getlet(cpar.ins.c));
		}
		else{ // par.ins.a == 3
			printf("chug %c\n", getlet(cpar.ins.b));
		}
	}
}
