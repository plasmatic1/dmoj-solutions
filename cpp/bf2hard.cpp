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
};

const int MN = 1e6 + 1;
int n, k;
string s;
SuffixArray<MN, 'a'> sfx(n, s);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(s, k);
    n = s.length();
    sfx.init();

    // for (int i = 0; i < n; i++) {
    //     auto ss = s.substr(sfx.get(i)); debug(i, ss, n - sfx.get(i));
    // }

    for (int i = 0; i < n; i++) {
        int idx = sfx.get(i);
        if (n - idx >= k) {
            cout << s.substr(idx, k) << "\n";
            return 0;
        }
    }

    return 0;
}