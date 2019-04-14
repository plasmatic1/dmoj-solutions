#include <bits/stdc++.h>

using namespace std;

#define MV 1000001

bool flag[MV], done = false;

void xff(){
    memset(flag, true, sizeof flag);
    for(int i = 2; i < MV; i++){
        if(flag[i]){
            for(int j = i + i; j < MV; j += i)
                flag[j] = false;
        }
    }
    flag[0]=flag[1] = false;
}

bool f(int v){
    if(!done){
        xff();
        done = true;
    }
    
    return flag[v];
}

int main(){
    
    return 0;
}