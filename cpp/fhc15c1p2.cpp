#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Scan and Debug
void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

struct trie {
    trie* ch[26];
    int sz;

    trie() {
        sz = 0;
        for (int i = 0; i < 26; i++)
            ch[i] = nullptr;
    }

    ~trie() {
        for (int i = 0; i < 26; i++)
            if (ch[i])
                delete ch[i];
    }
};

const int MAX = 1e5 + 1;
int n;
string strs[MAX];
trie* root = nullptr;

// Python ord() function but with chars
#define ord(x) ((int)((x) - 'a'))

void insert(trie* cur, int idx, int sz, string &s) {
    cur->sz++;
    if (idx == sz)
        return;
    
    trie* &nxt = cur->ch[ord(s[idx])];
    if (!nxt)
        nxt = new trie;

    insert(nxt, idx + 1, sz, s);
}

int best(trie* cur, int idx, int sz, string s) {
    if (idx == sz)
        return idx;

    if (cur->sz == 1 && cur != root)
        return idx;

    return best(cur->ch[ord(s[idx])], idx + 1, sz, s);
}

void solve(int tcn_) {
    int tot = 0;

    for (int i = 0; i < n; i++) {
        insert(root, 0, strs[i].length(), strs[i]);
        tot += best(root, 0, strs[i].length(), strs[i]);
    }

    cout << "Case #" << tcn_ << ": " << tot << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    int t; scan(t);
    for (int tcn_ = 1; tcn_ <= t; tcn_++) {
        scan(n);

        for (int i = 0; i < n; i++)
            scan(strs[i]);
        
        root = new trie;
        solve(tcn_);
        delete root;
    }

    return 0;
}
