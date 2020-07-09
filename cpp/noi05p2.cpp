#pragma GCC optimize "Ofast"
#pragma GCC optimize "unroll-loops"
#pragma GCC target "sse,sse2,sse3,sse4,abm,avx,mmx,popcnt,tune=native"

#include <bits/stdc++.h>

using namespace std;

// Common DS shorteners
using ll = long long; using ull = unsigned long long;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using mp = unordered_map<K, V>;
template <typename K> using us = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
using uint = unsigned int;
using ld = long double;
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
// Debugging
int di_; string dnms_, co_ = ",";
void debug_(){cout<<endl;}
template<typename F, typename... R>
void debug_(F f,R... r){int bc=0;while (bc != 0 || dnms_[di_] != ','){if (dnms_[di_] == '(') {bc++;}else if (dnms_[di_] == ')') {bc--;}cout << dnms_[di_++];}di_++;cout << ": " << f << ",";debug_(r...);}
#define debug(...) do{dnms_=#__VA_ARGS__+co_,di_=0,debug_(__VA_ARGS__);}while(0)

// Wesley
constexpr const char nl='\n',sp=' ';constexpr const int INT_INF=0x3f3f3f3f;constexpr const ll LL_INF=0x3f3f3f3f3f3f3f3f;
constexpr const double D_INF=numeric_limits<double>::infinity();constexpr const ld LD_INF=numeric_limits<ld>::infinity();constexpr const double EPS=1e-9;
template<typename T>constexpr bool flt(const T&x,const T&y){return x<y-EPS;}template<typename T>constexpr bool fgt(const T&x,const T&y){return x>y+EPS;}
template<typename T>constexpr bool feq(const T&x,const T&y){return abs(x-y)<=EPS;}template<typename T>constexpr bool in(const T&v,const T&lo,const T&hi){return!(v<lo||hi<v);}
template<typename T>constexpr const T&_min(const T&x,const T&y){return x<y?x:y;}template<typename T>constexpr const T&_max(const T&x,const T&y){return x<y?y:x;}
template<typename T,typename...Ts>constexpr const T&_min(const T&x,const Ts&...xs){return _min(x,_min(xs...));}
template<typename T,typename...Ts>constexpr const T&_max(const T&x,const Ts&...xs){return _max(x,_max(xs...));}
template<typename T,typename...Ts>void MIN(T&x,const Ts&...xs){x=_min(x,xs...);}template<typename T,typename...Ts>void MAX(T&x,const Ts&...xs){x=_max(x,xs...);}
template<typename T>constexpr const T&_clamp(const T&v,const T&lo,const T&hi){return v<lo?lo:hi<v?hi:v;}template<typename T>void CLAMP(T&v,const T&lo,const T&hi){v=_clamp(v,lo,hi);}
template<typename T,typename...Args>unique_ptr<T>_make_unique(Args&&...args){return unique_ptr<T>(new T(forward<Args>(args)...));}
template<typename T,typename...Args>shared_ptr<T>_make_shared(Args&&...args){return shared_ptr<T>(new T(forward<Args>(args)...));}
#define min _min
#define max _max
#define clamp _clamp
#define make_unique _make_unique
#define make_shared _make_shared
template<typename...Ts>using uset=unordered_set<Ts...>;template<typename...Ts>using umap=unordered_map<Ts...>;template<typename...Ts>using pq=priority_queue<Ts...>;
template<typename T>using minpq=pq<T,vector<T>,greater<T>>;template<typename T>using maxpq=pq<T,vector<T>,less<T>>;
template<typename T1,typename T2,typename H1=hash<T1>,typename H2=hash<T2>>struct pair_hash{size_t operator()(const pair<T1,T2>&p)const{return 31*H1{}(p.first)+H2{}(p.second);}};

constexpr const int _bufferSize=1<<16,_maxNumLength=128;
char _inputBuffer[_bufferSize+1],*_inputPtr=_inputBuffer,_outputBuffer[_bufferSize],_c,_sign,*_tempInputBuf=nullptr,_numBuf[_maxNumLength],_tempOutputBuf[_maxNumLength],_fill=' ';
FILE*_input=stdin,*_output=stdout,*_error=stderr;const char*_delimiter=" ";int _cur,_outputPtr=0,_numPtr=0,_precision=6,_width=0,_tempOutputPtr=0,_cnt;ull _precisionBase=1000000;
#ifdef _WIN32
    #define getchar_unlocked getchar
    #define fread_unlocked fread
    #define fwrite_unlocked fwrite
#endif
#if INTERACTIVE_INPUT
    #define _getchar() getchar_unlocked()
#else
    #define _peekchar() (*_inputPtr?*_inputPtr:(_inputBuffer[fread_unlocked(_inputPtr=_inputBuffer,1,_bufferSize,_input)]='\0',*_inputPtr))
    #define _getchar() (*_inputPtr?*_inputPtr++:(_inputBuffer[fread_unlocked(_inputPtr=_inputBuffer,1,_bufferSize,_input)]='\0',*_inputPtr++))
    #define _hasNext() (*_inputPtr||!feof(_input))
    bool hasNext(){while(_hasNext()&&_peekchar()<=' ')_getchar();return _hasNext();}bool hasNextLine(){while(_hasNext()&&_peekchar()=='\r')_getchar();return _hasNext();}
#endif
#define _readSignAndNum(x) do{(x)=_getchar();}while((x)<=' ');_sign=(x)=='-';if(_sign)(x)=_getchar();for((x)-='0';(_c=_getchar())>='0';(x)=(x)*10+_c-'0')
#define _readFloatingPoint(x,T) for(T _div=1.0;(_c=_getchar())>='0';(x)+=(_c-'0')/(_div*=10))
#define rc(x) do{do{(x)=_getchar();}while((x)<=' ');}while(0)
#define ri(x) do{_readSignAndNum(x);if(_sign)(x)=-(x);}while(0)
#define rd(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,double);if(_sign)(x)=-(x);}while(0)
#define rld(x) do{_readSignAndNum(x);if(_c=='.')_readFloatingPoint(x,ld);if(_sign)(x)=-(x);}while(0)
#define rcs(x) do{_cur=0;do{_c=_getchar();}while(_c<=' ');do{(x)[_cur++]=_c;}while((_c=_getchar())>' ');(x)[_cur]='\0';}while(0)
#define rs(x) do{if(!_tempInputBuf)assert(0);rcs(_tempInputBuf);(x)=string(_tempInputBuf,_cur);}while(0)
#define rcln(x) do{while(_inputPtr!=_inputBuffer&&*(_inputPtr-1)=='\r')_getchar();_cur=0;while((_c=_getchar())!='\n'&&_c){if(_c!='\r')(x)[_cur++]=_c;}(x)[_cur]='\0';}while(0)
#define rln(x) do{if(!_tempInputBuf)assert(0);rcln(_tempInputBuf);(x)=string(_tempInputBuf,_cur);}while(0)
void setLength(int x){if(_tempInputBuf)delete[](_tempInputBuf);_tempInputBuf=new char[x+1];}
void read(int&x){ri(x);}void read(uint&x){ri(x);}void read(ll&x){ri(x);}void read(ull&x){ri(x);}void read(double&x){rd(x);}void read(ld&x){rld(x);}
void read(char&x){rc(x);}void read(char*x){rcs(x);}void read(string&x){rs(x);}void readln(char*x){rcln(x);}void readln(string&x){rln(x);}
template<class T1,class T2>void read(pair<T1,T2>&x){read(x.first);read(x.second);}template<class T>void read(complex<T>&x){T _re,_im;read(_re);read(_im);x.real(_re);x.imag(_im);}
template<class T>void read(T&x);template<class T,class...Ts>void read(T&x,Ts&&...xs);
// template<class It>typename enable_if<is_iterator<It>::value>::type read(It st,It en){for(It _i=st;_i!=en;_i++)read(*_i);}
// template<class It,class...Ts>typename enable_if<is_iterator<It>::value>::type read(It st,It en,Ts&&...xs){read(st,en);read(forward<Ts>(xs)...);}
template<class T>void read(T&x){for(auto&&_i:x)read(_i);}template<class T,class...Ts>void read(T&x,Ts&&...xs){read(x);read(forward<Ts>(xs)...);}
void setInput(FILE*file){*_inputPtr='\0';_input=file;}void setInput(const char*s){*_inputPtr='\0';_input=fopen(s,"r");}void setInput(const string&s){*_inputPtr='\0';_input=fopen(s.c_str(),"r");}
#define _flush() do{_flushBuf();fflush(_output);}while(0)
#define _flushBuf() (fwrite_unlocked(_outputBuffer,1,_outputPtr,_output),_outputPtr=0)
#define _putchar(x) (_outputBuffer[_outputPtr==_bufferSize?_flushBuf():_outputPtr]=(x),_outputPtr++)
#define _writeTempBuf(x) (_tempOutputBuf[_tempOutputPtr++]=(x))
#define _writeOutput() for(int _i=0;_i<_tempOutputPtr;_putchar(_tempOutputBuf[_i++]));_tempOutputPtr=0
#define _writeNum(x,T,digits) _cnt=0;for(T _y=(x);_y;_y/=10,_cnt++)_numBuf[_numPtr++]='0'+_y%10;for(;_cnt<digits;_cnt++)_numBuf[_numPtr++]='0';_flushNumBuf();
#define _writeFloatingPoint(x,T) ull _I=(ull)(x);ull _F=((x)-_I)*_precisionBase+(T)(0.5);if(_F>=_precisionBase){_I++;_F=0;}_writeNum(_I,ull,1);_writeTempBuf('.');_writeNum(_F,ull,_precision)
#define _checkFinite(x) if(std::isnan(x)){wcs("NaN");}else if(std::isinf(x)){wcs("Inf");}
#define _flushNumBuf() for(;_numPtr;_writeTempBuf(_numBuf[--_numPtr]))
#define _fillBuf(x) for(int _i=0;_i<(x);_i++)_putchar(_fill)
#define _flushTempBuf() int _tempLen=_tempOutputPtr;_fillBuf(_width-_tempLen);_writeOutput();_fillBuf(-_width-_tempLen)
#define wb(x) do{if(x)_writeTempBuf('1');else _writeTempBuf('0');_flushTempBuf();}while(0)
#define wc(x) do{_writeTempBuf(x); _flushTempBuf();}while(0)
#define wi(x) do{if((x)<0){_writeTempBuf('-');_writeNum(-(x),uint,1);}else{_writeNum(x,uint,1);}_flushTempBuf();}while(0)
#define wll(x) do{if((x)<0){_writeTempBuf('-');_writeNum(-(x),ull,1);}else{_writeNum(x,ull,1);}_flushTempBuf();}while(0)
#define wd(x) do{_checkFinite(x)else if((x)<0){_writeTempBuf('-');_writeFloatingPoint(-(x),double);}else{_writeFloatingPoint(x,double);}_flushTempBuf();}while(0)
#define wld(x) do{_checkFinite(x)else if((x)<0){_writeTempBuf('-');_writeFloatingPoint(-(x),ld);}else{_writeFloatingPoint(x,ld);}_flushTempBuf();}while(0)
#define wcs(x) do{int _slen=strlen(x);_fillBuf(_width-_slen);for(const char*_p=(x);*_p;_putchar(*_p++));_fillBuf(-_width-_slen);}while(0)
#define ws(x) do{_fillBuf(_width-int((x).length()));for(int _i=0;_i<int((x).length());_putchar(x[_i++]));_fillBuf(-_width-int((x).length()));}while(0)
void setPrecision(int x){_precision=x;_precisionBase=1;for(int _i=0;_i<x;_i++,_precisionBase*=10);}void setWidth(int x){_width=x;}void setFill(char x){_fill=x;}
void setDelimiter(const char*x){_delimiter=x;}void setDelimiter(const string&x){_delimiter=x.c_str();}
void writeDelimiter(){for(const char*_p=_delimiter;*_p;_putchar(*_p++));}
void write(const bool&x){wb(x);}void write(const int&x){wi(x);}void write(const uint&x){wi(x);}void write(const ll&x){wll(x);}void write(const ull&x){wll(x);}
void write(const double&x){wd(x);}void write(const ld&x){wld(x);}void write(const char&x){wc(x);}void write(const char*x){wcs(x);}void write(const string&x){ws(x);}
template<class T1,class T2>void write(const pair<T1,T2>&x){write(x.first);writeDelimiter();write(x.second);}
template<class T>void write(const complex<T>&x){write(x.real());writeDelimiter();write(x.imag());}
template<class T>void write(const T&x);template<class T,class...Ts>void write(const T&x,Ts&&...xs);
// template<class It>typename enable_if<is_iterator<It>::value>::type write(It st,It en){bool _first=1;for(It _i=st;_i!=en;_i++){if(_first)_first=0;else writeDelimiter();write(*_i);}}
// template<class It,class...Ts>typename enable_if<is_iterator<It>::value>::type write(It st,It en,Ts&&...xs){write(st,en);writeDelimiter();write(forward<Ts>(xs)...);}
template<class T>void write(const T&x){bool _first=1;for(auto&&_i:x){if(_first)_first=0;else writeDelimiter();write(_i);}}
template<class T,class...Ts>void write(const T&x,Ts&&...xs){write(x);writeDelimiter();write(forward<Ts>(xs)...);}
void writeln(){_putchar('\n');}template<class...Ts>void writeln(Ts&&...xs){write(forward<Ts>(xs)...);_putchar('\n');}
void flush(){_flush();}class IOManager{public:~IOManager(){flush();if(_tempInputBuf)delete[](_tempInputBuf);}};unique_ptr<IOManager>iomanager=make_unique<IOManager>();


/*
POSITIONS ARE 1-INDEXED

SPLIT(idx) -> LHS: [1, idx], RHS: [idx+1, N]
INSERT(idx, x) -> Insert (x) after pos [idx]
*/
ll seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 gen(seed);
uniform_int_distribution<int> dis;
struct Node {
    int pri, sz; Node *l, *r; int val, maxSfx, maxPfx, maxSum, sum, lazySet, maxv; bool reverse;
    Node(int val0) : pri(dis(gen)), sz(1), l(nullptr), r(nullptr), val(val0) {
        maxSfx = maxPfx = maxSum = sum = maxv = val;
        lazySet = INF; // Default Value
        reverse = false;
    }
    ~Node() {
        if (l) delete l;
        if (r) delete r;
    }
};
struct ImplicitTreap {
    Node* root;
    ImplicitTreap() : root(nullptr) {}
    #define GETFUNC(name) inline int name(Node* &cur) { return cur ? cur->name : 0; }
    GETFUNC(sz) GETFUNC(sum) GETFUNC(maxPfx) GETFUNC(maxSfx) GETFUNC(maxSum)
    inline int maxv(Node* &cur) { return cur ? cur->maxv : INT_MIN; }
    inline void pushDown(Node* &cur) {
        if (cur) {
            cur->sz = sz(cur->l) + 1 + sz(cur->r);
            cur->maxv = max(maxv(cur->l), max(cur->val, maxv(cur->r)));

            if (cur->reverse) {
                swap(cur->l, cur->r);
                swap(cur->maxPfx, cur->maxSfx);

                // Propagate
                if (cur->l) cur->l->reverse ^= cur->reverse;
                if (cur->r) cur->r->reverse ^= cur->reverse;
                cur->reverse = false;
            }

            if (cur->lazySet != INF) {
                cur->val = cur->maxv = cur->lazySet;
                if (cur->lazySet > 0) {
                    cur->maxPfx = cur->maxSfx = cur->maxSum = cur->sum = sz(cur) * cur->lazySet;
                }
                else {
                    cur->maxPfx = cur->maxSfx = cur->maxSum = 0;
                    cur->sum = sz(cur) * cur->lazySet;
                }

                // Propagate
                if (cur->l) cur->l->lazySet = cur->lazySet;
                if (cur->r) cur->r->lazySet = cur->lazySet;
                cur->lazySet = INF;
            }
        }
    }
    inline void updSMOnly(Node* &cur) {
        cur->sz = sz(cur->l) + sz(cur->r) + 1;
        cur->maxv = max(maxv(cur->l), max(maxv(cur->r), cur->val));
    }
    inline void upd(Node* &cur) { 
        if (cur) { 
            pushDown(cur->l); pushDown(cur->r); // MUST INCLUDE THIS OR YOU LITERALLY DIEEEEEEEEEEEE (WA) (REQUIRED FOR REVERSE OPERATION)
            cur->sz = sz(cur->l) + sz(cur->r) + 1;
            cur->maxv = max(maxv(cur->l), max(cur->val, maxv(cur->r)));
            cur->sum = sum(cur->l) + cur->val + sum(cur->r);

            cur->maxPfx = max(maxPfx(cur->l), sum(cur->l) + cur->val + maxPfx(cur->r));
            cur->maxSfx = max(maxSfx(cur->r), maxSfx(cur->l) + cur->val + sum(cur->r));
            cur->maxSum = max(max(cur->maxPfx, cur->maxSfx), max(max(maxSum(cur->l), maxSum(cur->r)), maxSfx(cur->l) + cur->val + maxPfx(cur->r)));
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
        pushDown(l); pushDown(r);
        if (!l || !r) cur = l ? l : r;
        else if (l->pri > r->pri) { merge(l->r, l->r, r); cur = l; }
        else { merge(r->l, l, r->l); cur = r; }
        upd(cur);
    }
    void insert(Node* &cur, int key, Node* node) {
        Node* rhs;
        split(cur, key, cur, rhs);
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
        pushDown(cur);
        inOrder(cur->l); cout << cur->val << " "; inOrder(cur->r);
        upd(cur);
    }

    #define DOSPLIT Node *t1, *t2; \
        split(root, pos - 1, root, t1); \
        split(t1, tot, t1, t2); 
    #define DOMERGE merge(root, root, t1); \
        merge(root, root, t2);

    void OpDelete(int pos, int tot) {
        DOSPLIT
        delete t1;
        merge(root, root, t2);
    }
    void OpMakeSame(int pos, int tot, int val) {
        DOSPLIT
        if (t1) t1->lazySet = val;
        DOMERGE
    }
    void OpReverse(int pos, int tot) {
        DOSPLIT
        if (t1) t1->reverse ^= true;
        DOMERGE
    }
    int OpGetSum(int pos, int tot) {
        DOSPLIT
        int ans = sum(t1);
        DOMERGE
        return ans;
    }
};

int n, q, ba, bb, bc;
string bt;
ImplicitTreap t;

// Fuck it ive lost all dignity
void heapify (Node* t) {
    if (!t) return;
    Node* max = t;
    if (t->l && t->l->pri > max->pri) { max = t->l; }
    if (t->r && t->r->pri > max->pri) { max = t->r; }
    if (max != t) {
        swap(t->pri, max->pri);
        heapify(max);
    }
}

int cbuf[500001];
Node* build(int *arr, int n) {
    if (!n) return nullptr;
    int mid = n >> 1;
    Node* cur = new Node(arr[mid]);
    cur->l = build(arr, mid);
    cur->r = build(arr + mid + 1, n - mid - 1);
    t.upd(cur);
    heapify(cur);
    return cur;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    read(n, q);
    
    setLength(10);
    for (int i = 0; i < n; i++) {
        read(ba);
        t.merge(t.root, t.root, new Node(ba));
    }

    for (int i = 0; i < q; i++) {
        read(bt);
        // print("i: ", i, " | ");
        // t.inOrder(t.root);
        // print('\n');

        if (bt == "INSERT") {
            read(ba, bb);
            for (int i = 0; i < bb; i++) {
                read(cbuf[i]);
            }
            t.insert(t.root, ba, build(cbuf, bb));
        }
        else if (bt == "DELETE") {
            read(ba, bb);
            t.OpDelete(ba, bb);
        }
        else if (bt == "MAKE-SAME") {
            read(ba, bb, bc);
            t.OpMakeSame(ba, bb, bc);
        }
        else if (bt == "REVERSE") {
            read(ba, bb);
            t.OpReverse(ba, bb);
        }
        else if (bt == "GET-SUM") {
            read(ba, bb);
            int sum = t.OpGetSum(ba, bb);
            writeln(sum);
        }
        else { // bt == MAX-SUM
            t.pushDown(t.root);
            t.upd(t.root);

            int ans = t.maxSum(t.root);
            if (ans == 0) ans = t.maxv(t.root);
            writeln(ans);
        }

        // cout.flush();
    }

    return 0;
}