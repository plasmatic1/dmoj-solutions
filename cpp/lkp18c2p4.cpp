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

struct suffix {
    int idx, fst, snd;
    bool operator<(const suffix &o) const { return fst == o.fst ? snd < o.snd : fst < o.fst; }
};
template <size_t MAX, char A = 'a'>
struct SuffixArray {
    static const int LOG = log2(MAX) + 2;
    int &n; string &s; suffix sfx[MAX]; int rnk[LOG][MAX];
    SuffixArray(int &n0, string &s0) : n(n0), s(s0) {}
    void init() {
        for (int i = 0; i < n; i++)
            rnk[0][i] = s[i] - A;
        for (int i = 1; (1 << (i - 1)) < n; i++) {
            int jmp = 1 << (i - 1);
            for (int j = 0; j < n; j++)
                sfx[j] = {j, rnk[i - 1][j], j + jmp < n ? rnk[i - 1][j + jmp] : -1};
            sort(sfx, sfx + n);
            for (int j = 0; j < n; j++)
                rnk[i][sfx[j].idx] = (j > 0 && sfx[j].fst == sfx[j - 1].fst && sfx[j].snd == sfx[j - 1].snd ? rnk[i][sfx[j - 1].idx] : j); 
        }
    }
    inline int get(int id) { return sfx[id].idx; }
    inline char ch(int id, int chId) { return s[sfx[id].idx + chId]; }
    void print() { for (int i = 0; i < n; i++) cout << i << ": " << s.substr(get(i)) << "\n"; }
    int bsearch(int l, int r, int chId, char find) { // l, r, and chId are 1-indexed.  Acts like C++ lower_bound
        l--; l--; chId--;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (ch(mid, chId) >= find) r = mid; else l = mid;
        } return r + 1;
    }
};

const int MN = 2e5 + 1;
int n, 
    idxOf[MN], matchAmt[MN], totOf[MN], ls[MN], rs[MN];
string s;
SuffixArray<MN> sfx(n, s);
bool work[MN];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, s);
    sfx.init();

    // sfx.print();
    
    for (int i = 0; i < n; i++)
        idxOf[n - sfx.sfx[i].idx] = i + 1;   

    ls[0] = 1; rs[0] = n;
    for (int i = 1; i <= n; i++) {
        int newL = sfx.bsearch(ls[i - 1], rs[i - 1], i, s[i - 1]),
            newR = sfx.bsearch(ls[i - 1], rs[i - 1], i, s[i - 1] + 1) - 1;
        ls[i] = newL;
        rs[i] = newR;

        // debug(i, newL, newR);

        totOf[i] = rs[i] - ls[i] + 1;
    }

    ll tot = 0;
    for (int i = 1; i <= n; i++) {
        if (ls[i] <= idxOf[i] && idxOf[i] <= rs[i])
            tot += totOf[i]; // debug(i, ls[i], idxOf[i], rs[i]);
    }

    cout << tot << "\n";

    return 0;
}
