//============================================================================
// Name        : PhonomenalReviews.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

//#define DEBUG

using namespace std;

const int MAX = 100000;

int n, m, st, edges = 0,
		levels[MAX], levels0[MAX];
bool pho[MAX];
vector<int> matrix[MAX], matrix2[MAX]; //, phos;

bool dfs(int node, int parent){
	bool flag = pho[node];
	for(int adj : matrix[node]){
		if(adj == parent){
			continue;
		}
		if(dfs(adj, node)){
			flag = true;
		}
	}

	// && parent != -1
	if(flag && parent != -1){
#ifdef DEBUG
		printf("Adding edge %d to %d\n", parent, node);
#endif

		matrix2[node].push_back(parent);
		matrix2[parent].push_back(node);
		edges++;
	}

	return flag;
}

void bfs(int levelss[], int start, int n){
	fill(levelss, levelss + n, -1);
	levelss[start] = 0;
	queue<int> next;
	next.push(start);

	while(!next.empty()){
		int curr = next.front(), level = levelss[curr];
		next.pop();

		for(int adj : matrix2[curr]){
			if(levelss[adj] != -1){
				continue;
			}

			levelss[adj] = level + 1;
			next.push(adj);
		}
	}
}

int maxNode(int arr[], int n){
	int max = 0, node = -1;
	for(int i = 0; i < n; i++){
		if(arr[i] > max){
			max = arr[i];
			node = i;
		}
	}

	return node;
}

int main() {
	scanf("%d %d", &n, &m);

	for(int i = 0; i < m; i++){
		int p;
		scanf("%d", &p);

		pho[p] = true;
		st = p;
	}

	for(int i = 0, n0 = n - 1; i < n0; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		matrix[a].push_back(b);
		matrix[b].push_back(a);
	}

	dfs(st, -1);

//	memset(levels, -1, sizeof(levels));
//	memset(levels0, -1, sizeof(levels0));

	bfs(levels, st, n);
	int end = maxNode(levels, n);
	bfs(levels0, end, n);

	int dia = *max_element(levels0, levels0 + n);

#ifdef DEBUG
	cout << "st " << st << endl;

	cout << "levels ";
	for(int i = 0; i < n; i++){
		cout << levels[i] << ", ";
	}
	cout << endl;

	printf("levels0: ");
	for (int i = 0; i < n; ++i) {
		printf("%d, ", levels0[i]);
	}
	printf("\n");

	printf("edges=%d, dia=%d\n", edges, dia);

	cout << "end " << end << endl;
#endif

	cout << (2 * edges - dia) << endl;

	return 0;
}
