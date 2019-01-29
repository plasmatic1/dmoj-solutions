//============================================================================
// Name        : DeliveryService.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct po{
    int end, pos;

    friend bool operator<(const po &a, const po &b){
        return a.end > b.end;
    }
};

const int MAX = 100001, MOD = 1000000007, MB = 31;
int x;

inline int pos(int v){
    while(v < 0) v += MOD;
    return v;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> x;

    if(x == 1){
        int d, n, p, bq, br,
            dp[MAX], f[MAX];
        bool is[MAX];
        priority_queue<po> currs;

        cin >> d >> n >> p;

        memset(is, false, sizeof is);
        memset(dp, 0, sizeof dp);

        for (int i = 0; i < p; ++i) {
            cin >> bq >> br;

            is[bq] = true;
            f[bq] = br;
        }

        int cv = 1;
        currs.push({n, 1});
        is[d] = true;

        for(int i = 1; i <= d; i++){
            if(is[i]){
                dp[i] = cv;

                cv = (cv + dp[i]) % MOD;
                currs.push({i + f[i], dp[i]});
            }

            while(!currs.empty() && currs.top().end <= i){
                cv = pos(cv - currs.top().pos);
                currs.pop();
            }
        }

        printf("%d\n", dp[d]);
    }
    else{
        int w;

        cin >> w;

        printf("%d 1 %d\n", MB + 2, (w & (1 << (MB - 1))) ? MB + 1 : MB);

        for (int i = 0; i <= MB; ++i) {
			int base = MB - i;

			if(w & (1 << (i - 1)))
				printf("%d %d\n", i + 1, base + 1);
			else{
				if(base) printf("%d %d\n", i + 1, base);
			}
		}

        printf("\n");
    }
}