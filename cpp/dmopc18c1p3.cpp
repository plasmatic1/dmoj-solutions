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

const int MAX = 101;
int n,
    perm[MAX];
bool vis[MAX];
vector<vector<int>> moves;

void doCycle(int cur, vector<int> &nodes) {
    if (vis[cur]) return;
    vis[cur] = true;
    nodes.push_back(cur);
    doCycle(perm[cur], nodes);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n);

    for (int i = 1; i <= n; i++)
        scan(perm[i]);
    
    for (int i = 1; i <= n; i++) {
        if (vis[i])
            continue;

        vector<int> nodes;
        doCycle(i, nodes);

        if (nodes.size() > (size_t)1)
            moves.push_back(nodes);
    }

    if (moves.size() <= (size_t)2) {
        cout << moves.size() << "\n";
        for (vector<int> nodes : moves) {
            cout << nodes.size() << " ";
            for (int nd : nodes)
                cout << nd << " ";
            cout << "\n";
        }
    }
    else {
        cout << "2\n";

        int sum = 0;
        for (vector<int> nodes : moves)
            sum += nodes.size();
        cout << sum << " ";
        for (vector<int> nodes : moves)
            for (int node : nodes)
                cout << node << " ";
        cout << "\n";

        cout << moves.size() << " ";
        vector<int> rev;
        for (vector<int> nodes : moves)
            rev.push_back(nodes[0]);
        reverse(rev.begin(), rev.end());
        for (int node : rev)
            cout << node << " ";
        cout << "\n";
    }

    return 0;
}