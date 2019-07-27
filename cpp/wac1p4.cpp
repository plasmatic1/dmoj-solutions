#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// Defines and one-liners
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
template <typename T> inline T& back(vector<T> &vec) { return *(vec.end() - 1); }
template <typename T> inline void pop(vector<T> &vec) { return vec.erase(vec.end() - 1); }

// Scan, Debug, and other nonsense
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printArray(ostream& out,T* arr,int sz){out<<"[";for(int i=0;i<sz;i++){out<<arr[i]<<", "; } out<<"]";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}

void scan(){}
template<typename F, typename... R> void scan(F &f,R&... r){cin>>f;scan(r...);}
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R> void debug_(F f,R... r){while(dnms_[di_] != ',')cout<<dnms_[di_++];di_++;cout<<": "<<f<<",";debug_(r...);}
#define debug(...) dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__)

template <int MAX>
struct Graph {
    int n, m, __ba, __bb; vector<int> matrix[MAX];
    void init(int n0, int m0) { n = n0; m = m0; }
    inline void addEdge(int a, int b) { matrix[a].push_back(b); }
    inline auto& adjs(int x) { return matrix[x]; }
    Graph& operator=(const Graph o) { n = o.n; m = o.m; copy(o.matrix, o.matrix + n + 1, matrix); return *this; }
    void input(bool undirected) { // Reads a graph's edges from stdin
        for (int i = 0; i < m; i++) {
            cin >> __ba >> __bb;
            addEdge(__ba, __bb);
            if (undirected) addEdge(__bb, __ba);
        }
    }
};

const ll MOD = 998244353;
const int MN = 1e2 + 2;
int n, k,   
    pars[MN];
char type[MN];
Graph<MN> g;
ll dp[MN][MN][3][3]; // Node, Subgraph Size, # of red, # of black

void setPar(int cur, int par) {
    pars[cur] = par;
    for (int adj : g.adjs(cur))
        if (adj ^ par)
            setPar(adj, cur);
}

ll freq[MN][MN][MN][3][3]; // # of nodes, # of red, # of black
void rec(int cur) {
    // freq[cur][0][1][type[cur] == 'R'][type[cur] == 'B'] = 1;
    freq[cur][0][0][0][0] = 1;
    int ptr = 1;
    for (int adj : g.adjs(cur)) {
        if (adj ^ pars[cur]) {
            rec(adj);
            ll (&cfreq)[MN][3][3] = freq[cur][ptr], (&pfreq)[MN][3][3] = freq[cur][ptr - 1];
            for (int i = 0; i <= k; i++) {
                for (int j = 0; j <= min(2, i); j++) {
                    for (int l = 0; l <= min(2, i - j); l++) {
                        // if (j + l > i)
                        //     continue;
                        
                        ll val = dp[adj][i][j][l];
                        // if (type[adj] == 'R')
                        //     assert(dp[adj][1][0][1] == 0);
                        for (int m = 0; m <= k - i; m++) {
                            for (int n = 0; n <= min(2, m); n++) {
                                for (int o = 0; o <= min(2, m - n); o++) {
                                    // if (n + o > m)
                                    //     continue;

                                    int trueI = i + m, trueJ = min(2, j + n), trueL = min(2, l + o);
                                    cfreq[trueI][trueJ][trueL] += (pfreq[m][n][o] * val) % MOD;

                                    // if (cur == 1 && trueI == 3 && trueJ == 0 && trueL == 2)
                                    //     debug("spe", ptr, i, j, l, val, m, n, o, pfreq[m][n][o], pfreq[trueI][trueJ][trueL]);
                                    // if (cur == 2 && trueI == 2 && trueJ == 0 && trueL == 2)
                                    //     debug("spe", ptr, i, j, l, val, m, n, o, pfreq[m][n][o], pfreq[trueI][trueJ][trueL]);

                                    // if (i == 1 && j == 0 && l == 1 && m == 1 && n == 0 && o == 1)
                                    //     debug(ptr, adj, trueI, trueJ, trueL, pfreq[m][n][o], val, pfreq[trueI][trueJ][trueL]), assert(freq[cur][ptr][trueI][trueJ][trueL] > 0);
                                }
                            }
                        }
                    }
                }
            }

            for (int i = 0; i <= k; i++) {
                for (int j = 0; j <= min(2, i); j++) {
                    for (int l = 0; l <= min(2, i - j); l++) {
                        cfreq[i][j][l] += pfreq[i][j][l];
                    }
                }
            }
            
            ptr++; 
        }
    }

    // if (cur == 2)
    // for (int ii = 0; ii < ptr; ii++)
    //     for (int i = 0; i <= k; i++)
    //     for (int j = 0; j <= 2; j++)
    //         for (int l = 0; l <= 2; l++)
    //             debug(cur, ii, i, j, l, freq[cur][ii][i][j][l]);

    bool isRed = type[cur] == 'R';
    for (int i = 0; i < k; i++)
        for (int j = 0; j <= 2; j++)
            for (int l = 0; l <= 2; l++)
                dp[cur][i + 1][min(2, j + isRed)][min(2, l + !isRed)] += freq[cur][ptr - 1][i][j][l];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, k, type);
    copy(type, type + n, type + 1);

    g.init(n, n - 1);
    g.input(true);

    if (k < 4) {
        cout << "0\n";
        return 0;
    }

    setPar(1, -1);
    rec(1);

    // for (int i = 1; i <= n; i++) {
    //     for (int j = 1; j <= k; j++) {
    //         for (int l = 0; l <= 2; l++) {
    //             for (int m = 0; m <= 2; m++) {
    //                 debug(i, j, l, m, dp[i][j][l][m]);
    //             }
    //         }
    //     }
    // }

    ll tot = 0;
    for (int i = 1; i <= n; i++)
        tot = (tot + dp[i][k][2][2]) % MOD;
    cout << tot << "\n";

    return 0;
}
