//============================================================================
// Name        : BinaryIndexedTreeTest.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
//#define DEBUG

using namespace std;

typedef long long ll;
typedef pair<int, int> p;

int n, m, x, y;
char i_typ;

//Defines a fenwick tree
const int MAX = 100001, MAX_BIT = 16;
struct _ftree {
    int bits[MAX_BIT + 1];
    ll a[MAX];
    ll sum(int x) {
        ll sum = 0;
        int ttl = 0;
        for (int i = MAX_BIT; i >= 0; i--) {
            if (x & bits[i]) {
                ttl += bits[i];
                sum += a[ttl];
            }
        }
        return sum;
    }
    void add(int i, int k) {
        for (; i < MAX; i += i & -i) {
            a[i] += k;
        }
    }
    _ftree() {
        bits[0] = 1;
        for (int i = 1; i <= MAX_BIT; ++i) {
            bits[i] = bits[i - 1] << 1;
        }
    }
};
struct fenwick_tree {
    _ftree a, cnts;
    int curr_e[MAX];
    void b_add(int i, int k) {
        a.add(i, k);
        curr_e[i] = k;
        cnts.add(k, 1);
    }
    void add(int i, int k) {
        a.add(i, k);
        cnts.add(curr_e[i], -1);
        cnts.add(curr_e[i] + k, 1);
        curr_e[i] += k;
    }
    void sett(int i, int k) {
        a.add(i, -curr_e[i]);
        cnts.add(curr_e[i], -1);
        cnts.add(k, 1);
        curr_e[i] = k;
        a.add(i, k);
    }
    ll sum(int l, int r) {
        return a.sum(r) - a.sum(l - 1);
    }
    ll cnt(int v) {
        return cnts.sum(v);
    }
    fenwick_tree() {}
};
//This is literally my original solution but put into a concise data type

fenwick_tree totaltree;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m;

	for (int i = 1; i <= n; ++i) {
		cin >> x;

		totaltree.b_add(i, x);
	}

	for (int i = 0; i < m; ++i) {
		cin >> i_typ;

		cin >> x;
		if(i_typ == 'Q'){
			//Count

			printf("%lld\n", totaltree.cnt(x));

			continue;
		}

		cin >> y;
		if(i_typ == 'C'){
			//Change

			totaltree.sett(x, y);
		}
		else if(i_typ == 'S'){
			//Sum
			printf("%lld\n", totaltree.sum(x, y));
		}
	}
}
