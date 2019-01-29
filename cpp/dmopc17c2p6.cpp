//============================================================================
// Name        : LazyDayshows.cpp
// Author      : Daxi the Taxi
// Version     :
// Copyright   : ALL YOUR CODE IS BELONG TO US
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>

using namespace std;

struct show{ int v, ch, t;};

int N;
map<int, int> mapp;
vector<show> shows;

bool cmp(show x, show y){
	return x.v < y.v;
}

int main(){
    scanf("%d", &N);

    for(int i=1, x; i<=N; i++){
        scanf("%d", &x);
        shows.push_back({x, 1, i});
    }

    for(int i=1, x; i<=N; i++){
        scanf("%d", &x);
        shows.push_back({x, 2, i});
    }

    sort(shows.begin(), shows.end(), cmp);

    mapp[0] = 2;
    mapp[N+1] = 2;

    for(int i = 0, j = 0; i<=N; i++){
        for(; j < shows.size(); ){
            int v = shows[j].v, t = shows[j].t, ch = shows[j].ch;
            j++;

            if(mapp.count(t)){
                for(; i<=N; i++) printf("%d\n", v);
                return 0;
            }

            auto it = mapp.upper_bound(t);
            pair<int, int> rit = *it, lft = *(--it);

            if(lft.second != ch && rit.second != ch){
                printf("%d\n", v);

                if(rit.first == N+1)
                	mapp[N+1] = ch;
                else {
                	printf("%d\n", v);
                	i++;
                }

                mapp[t] = ch; break;
            }
            else {
                mapp[t] = ch;
            }
        }
    }
}
