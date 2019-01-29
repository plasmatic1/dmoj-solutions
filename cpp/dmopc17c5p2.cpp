//============================================================================
// Name        : MimiAndBinary.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> p;

const int MAX = 200000, MAX_D = 2;

int q, len, st_buf, cnt_buf, dig_buf, z_cnt = 0, o_cnt = 0,
	pfx[MAX_D][MAX];
char bstr[MAX];
p pfx_set[MAX_D][MAX];

bool cmp(const p &a, const p &b){
	return a.second < b.second;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> bstr >> q;
	len = strlen(bstr);

	for (int i = 0; i < len; ++i) {
		z_cnt += bstr[i] == '0';
		o_cnt += bstr[i] == '1';

		pfx[0][i] = z_cnt;
		pfx[1][i] = o_cnt;

		pfx_set[0][i] = p(i, z_cnt);
		pfx_set[1][i] = p(i, o_cnt);
	}

	for (int i = 0; i < q; ++i) {
		cin >> st_buf >> cnt_buf >> dig_buf;
		st_buf -= 2;
		int st_cnt = 0;

		if(st_buf >= 0){
			st_cnt = pfx[dig_buf][st_buf] + cnt_buf;
		}
		else{
			st_cnt = cnt_buf;
		}
		st_buf++;

		auto b_lb = lower_bound(pfx_set[dig_buf], pfx_set[dig_buf] + len, p(-1, st_cnt), cmp);

		if(b_lb == (pfx_set[dig_buf] + len)){
			printf("-1\n");
		}
		else{
			printf("%d\n", b_lb->first + 1);
		}
	}

	return 0;
}
