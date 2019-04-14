#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F &f, R&... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

int n, t;
string s;
vector<string> strs;

// Count number of nodes in trie
int countNodes(int idx, int l, int r){
    while(strs[l].length() <= idx && l <= r)
        l++;
    if(l > r)
        return 1;
    
    int lastIdx = l, tot = 1;
    char last = strs[l][idx];
    for (int i = l; i <= r; i++) {
        char cur = strs[i].length() > idx ? strs[i][idx] : '/';
        if(cur != last){
            tot += countNodes(idx + 1, lastIdx, i - 1);
            lastIdx = i;
            last = cur;
        }
    }
    tot += countNodes(idx + 1, lastIdx, r);

    return tot;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    scan(t);

    while(t--){
        scan(s);
        n = s.length();

        for (int i = 0; i < n; i++)
            strs.push_back(s.substr(i, n - i));
        sort(strs.begin(), strs.end());
        
        printf("%d\n", countNodes(0, 0, n - 1));

        strs.clear();
    }

    return 0;
}