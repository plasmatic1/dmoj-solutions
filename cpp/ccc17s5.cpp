#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using um = unordered_map<K, V>; template<typename K, typename V> using om = map<K, V>;
template <typename K> using us = unordered_set<K>; template <typename K> using os = set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Function Macros
#define Fori(a, b) for (int i = a; i < b; i++)
#define Forj(a, b) for (int j = a; j < b; j++)
#define Fork(a, b) for (int k = a; k < b; k++)
#define Forinci(a, b) for (int i = a; i <= b; i++)
#define Forincj(a, b) for (int j = a; j <= b; j++)
#define Forinck(a, b) for (int k = a; k <= b; k++)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(type) bool operator()(const type &a, const type &b)
// Shorthand Function Macros Part 2
#define Pow2(x) (1LL << (x))
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void debugArray(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, casttostr_ = ",";
void debug_(){cout<<endl;}
template<typename T> string debug_tostring_(T val) { ostringstream os; os << val; return os.str(); }
string debug_name_(string s, string str_val) {
    string ret = ""; if (s[0] == ' ') { ret += ' '; s = s.substr(1); } if (s[0] == '"' && s[s.length() - 1] == '"') { ret += string("[") + str_val + "]"; }
    else if (s.length() == (size_t)3 && s[0] == '\'' && s[2] == '\'') { ret += '(' + str_val + ')'; } else { ret += s + ": " + str_val; } return ret;
} template<typename F, typename... R> void debug_(F f, R... r) {
    int bc = 0; string pr = "";
    while (bc != 0 || dnms_[di_] != ',') { if (dnms_[di_] == '(') { bc++; } else if (dnms_[di_] == ')') { bc--; } pr += dnms_[di_++]; }
    di_++; cout << debug_name_(pr, debug_tostring_(f)) << ","; debug_(r...);
}
#define debug(...) do{dnms_=#__VA_ARGS__+casttostr_,di_=0,debug_(__VA_ARGS__);}while(0)
#pragma endregion

const int MN = 150001, BLKSZ = 350, BLKCNT = MN / BLKSZ + 10;
// const int MN = 151, BLKSZ = 2, BLKCNT = MN / BLKSZ + 10;
int n, m, Q,
    lineOf[MN], lineSize[MN]; // Line of station I, Size (no. of stations) of Line I

// Helping with counting and what not
int blockCnt,
    block[MN + 5], blockStart[BLKCNT]; // Larger size so that it doesn't go forever if you call updateBlock(blockCnt)

// Sqrt Blocks
vi lineCounts[MN], // Passenger counts for the stations in each line
    inBlocks[MN]; // Contains which blocks contain each line
int tots[BLKCNT], delta[MN][BLKCNT], // Totals -> Block sum, Delta -> Current number of additions put on that block for 
    stationId[MN]; // Station ID in respect to the line it's in

// Stations (originally deque<int>[MN][BLKCNT])
vi stationsIn[BLKCNT]; // Stations in each block
int stationsIdx[MN][BLKCNT]; 

// Updates blocks
inline void updateBlock(int blockToUpd) {
    for (int i = blockStart[blockToUpd]; block[i] == blockToUpd; i++) {
        int cline = lineOf[i], clineSize = lineSize[cline];
        if (delta[cline][blockToUpd]) {
            stationId[i] = (stationId[i] - delta[cline][blockToUpd]) % clineSize + clineSize;
            if (stationId[i] >= clineSize) stationId[i] -= clineSize;
        }
    }

    // Reset delta
    for (int line : stationsIn[blockToUpd])
        delta[line][blockToUpd] = 0;
}

// Increment and mod by MOD
inline int modInc(int x, int mod) {
    if (x == mod - 1) x = 0;
    else x++;
    return x;
}

// Decrement and mod by MOD
inline int modDec(int x, int mod) {
    if (!x) x = mod - 1;
    else x--;
    return x;
}

inline int deqBack(int line, int block) {
    return lineCounts[line][stationsIdx[line][block]];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, m, Q);
    blockCnt = (n + BLKSZ - 1) / BLKSZ;

    memset(blockStart, -1, sizeof blockStart);
    Forinci(1, n) {
        block[i] = i / BLKSZ;
        if (blockStart[block[i]] == -1)
            blockStart[block[i]] = i;
    }
    block[n + 1] = INF;

    // Input line ids
    Forinci(1, n) {
        scan(lineOf[i]);

        stationId[i] = lineSize[lineOf[i]];
        stationsIdx[lineOf[i]][block[i]] = stationId[i];
        inBlocks[lineOf[i]].pb(block[i]);
        stationsIn[block[i]].pb(lineOf[i]);
        lineSize[lineOf[i]]++;
    }

    // Stations In
    Fori(0, blockCnt) {
        vi &v = stationsIn[i];
        sort(v.begin(), v.end());
        v.resize(unique(v.begin(), v.end()) - v.begin());
    }

    // inBlocks
    Forinci(1, m) {
        vi &v = inBlocks[i];
        v.resize(unique(v.begin(), v.end()) - v.begin());
    }

    // Input block tots
    Forinci(1, n) {
        int x; scan(x);

        tots[block[i]] += x;
        lineCounts[lineOf[i]].pb(x);
    }

    while (Q--) {
        int t; scan(t);
        // debug(t);

        // for (int i = 0; i < blockCnt; i++)
        //     debug(i, tots[i]);

        if (t == 1) {
            int l, r; scan(l, r);

            // be careful to skip blocks that are 
            int blockL = block[l], blockR = block[r], tot = 0;

            // Update left and right blocks and sum
            if (blockL ^ blockR) {
                for (int i = blockL + 1; i <= blockR - 1; i++)
                    tot += tots[i];
                
                if (l == blockStart[blockL])
                    tot += tots[blockL];
                else {
                    updateBlock(blockL);
                    for (int i = l; block[i] <= blockL; i++)
                        tot += lineCounts[lineOf[i]][stationId[i]];
                }

                if (block[r + 1] != blockR)
                    tot += tots[blockR];
                else {
                    updateBlock(blockR);
                    for (int i = blockStart[blockR]; i <= r; i++)
                        tot += lineCounts[lineOf[i]][stationId[i]];
                }
            }
            else {
                updateBlock(blockL);
                for (int i = l; i <= r; i++)
                    tot += lineCounts[lineOf[i]][stationId[i]];
            }
            
            println(tot);
        }
        else {
            int x; scan(x);

            // Add delta
            for (int block : inBlocks[x])
                delta[x][block]++;

            // Subtract leaving stations and insert arriving ones while adding tot
            for (int i = 0, sz = inBlocks[x].size(); i < sz; i++) {
                int b = inBlocks[x][i], nxt = inBlocks[x][modInc(i, sz)];

                int ch = deqBack(x, b);
                tots[b] -= ch;
                tots[nxt] += ch;
            }

            for (int block : inBlocks[x])
                stationsIdx[x][block] = modDec(stationsIdx[x][block], lineSize[x]);
        }
    }

    return 0;
}
