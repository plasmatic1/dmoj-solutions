#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> void printDebug(T *arr,int sz){cout<<"[";for(int i=0;i<sz;i++){cout<<arr[i]<<", "; } cout<<"]\n";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
#define OUT_OPERATOR(type, propa, propb) ostream& operator<<(ostream& out,type obj){out<<"("<<#propa<<"="<<obj. propa<<", "<<#propb<<"="<<obj. propb<<")";return out;}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
inline void println(){cout<<"\n";}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

/*
POSITIONS ARE 1-INDEXED

SPLIT(idx) -> LHS: [1, idx], RHS: [idx+1, N]
INSERT(idx, x) -> Insert (x) after pos [idx]
*/
ll seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> dis;
struct Node {
    int pri, sz; Node *l, *r; bool chr; int pfxMax, sfxMax, totMax; bool reverse;
    Node(bool val0) : pri(dis(gen)), sz(1), l(nullptr), r(nullptr), chr(val0) {
        pfxMax = sfxMax = totMax = chr;
        reverse = false;
    }
};
struct ImplicitTreap {
    Node* root;
    ImplicitTreap() : root(nullptr) {}
    inline int sz(Node* &cur) { return cur ? cur->sz : 0; }
    inline int pfxMax(Node* &cur) { return cur ? cur->pfxMax : 0; }
    inline int sfxMax(Node* &cur) { return cur ? cur->sfxMax : 0; }
    inline int totMax(Node* &cur) { return cur ? cur->totMax : 0; }
    void pushDown(Node* cur) {
        if (cur) {
            if (cur->reverse) {
                cur->reverse = false;
                swap(cur->l, cur->r);
                swap(cur->pfxMax, cur->sfxMax);
                
                if (cur->l) cur->l->reverse ^= true;
                if (cur->r) cur->r->reverse ^= true;
            }
        }
    }
    void upd(Node* cur) { 
        if (cur) { 
            pushDown(cur->l); pushDown(cur->r); // MUST INCLUDE THIS OR YOU LITERALLY DIEEEEEEEEEEEE (WA)
            cur->sz = sz(cur->l) + sz(cur->r) + 1;

            if (sz(cur->l) == pfxMax(cur->l) && cur->chr)
                cur->pfxMax = sz(cur->l) + 1 + pfxMax(cur->r);
            else
                cur->pfxMax = pfxMax(cur->l);
            
            if (sz(cur->r) == sfxMax(cur->r) && cur->chr)
                cur->sfxMax = sz(cur->r) + 1 + sfxMax(cur->l);
            else
                cur->sfxMax = sfxMax(cur->r);
            
            cur->totMax = max(totMax(cur->l), totMax(cur->r));
            maxa(cur->totMax, max(cur->pfxMax, cur->sfxMax));
            if (cur->chr)
                cur->totMax = max(cur->totMax, sfxMax(cur->l) + 1 + pfxMax(cur->r));
        }
    }
    void split(Node* cur, int key, Node* &l, Node* &r) {
        pushDown(cur);
        if (!cur) l = r = nullptr;
        else if (key < sz(cur->l) + 1) { split(cur->l, key, l, cur->l); r = cur; }
        else { split(cur->r, key - sz(cur->l) - 1, cur->r, r); l = cur; }
        upd(cur);
    }
    void merge(Node* &cur, Node* l, Node* r) {
        pushDown(l); pushDown(r); //pushDown(cur);
        if (!l || !r) cur = l ? l : r;
        else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
        else { merge(r->l, l, r->l); cur = r; }
        upd(cur);
    }
    void insert(Node* &cur, int key, Node* node) {
        Node* rhs;
        split(cur, key + 1, cur, rhs);
        merge(cur, cur, node);
        merge(cur, cur, rhs);
    }
    void remove(Node* &cur, int key) {
        pushDown(cur);
        if (!cur) return;
        int cKey = sz(cur->l) + 1;
        if (key == cKey) { merge(cur, cur->l, cur->r); }
        else { key > cKey ? remove(cur->r, key - cKey) : remove(cur->l, key); }
        upd(cur);
    }
    Node* kth(Node* &cur, int idx) {
        pushDown(cur);
        int cKey = sz(cur->l) + 1;
        if (idx == cKey) return cur;
        auto ret = idx < cKey ? kth(cur->l, idx) : kth(cur->r, idx - cKey);
        upd(cur);
        return ret;
    }
    void inOrder(Node* &cur) {
        if (!cur) return;
        inOrder(cur->l); cout << cur->chr << " "; inOrder(cur->r);
    }
    void reverse(int l, int len) {
        Node *subt, *rhs;
        split(root, l - 1, root, subt);
        split(subt, len, subt, rhs);
        subt->reverse ^= true;
        merge(root, root, subt);
        merge(root, root, rhs);
    }
    int query(int l, int len) {
        Node *subt, *rhs;
        split(root, l - 1, root, subt);
        split(subt, len, subt, rhs);
        int ans = subt->totMax;
        merge(subt, subt, rhs);
        merge(root, root, subt);
        return ans;
    }
};

ImplicitTreap t;
int n, q, ba, bb, bt;
string s;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    scan(n, q, s);

    for (int i = 0; i < n; i++) {
        Node *nd = new Node(s[i] == '1');
        t.merge(t.root, t.root, nd);
    }

    for (int i = 0; i < q; i++) {
        scan(bt, ba, bb);
        ba++; // ba is 0-indexed

        if (bt == 1)
            t.reverse(ba, bb);
        else // bt == 2
            cout << t.query(ba, bb) << "\n";
    }

    return 0;
}
