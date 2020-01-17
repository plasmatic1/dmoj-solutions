#pragma region
#include <bits/stdc++.h>
using namespace std;
// Common Type shorteners and int128
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
template <typename T> using vec = vector<T>;
template <typename K, typename V> using umap = unordered_map<K, V>; template <typename K> using uset = unordered_set<K>;
using vi = vec<int>; using vl = vec<ll>; using vpi = vec<pii>; using vpl = vec<pll>;
#ifdef __SIZEOF_INT128__
using int128 = __int128_t; using uint128 = __uint128_t;
#endif
template<typename I> string intStr(I x) { string ret; while (x > 0) { ret += (x % 10) + '0'; x /= 10; } reverse(ret.begin(), ret.end()); return ret; } // Int to string
// Shorthand Macros
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define mpr make_pair
#define pb push_back
#define popcount __builtin_popcount
#define clz __builtin_clz
#define ctz __builtin_ctz
// Shorthand Function Macros
#define sz(x) ((int)((x).size()))
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for (__typeof(a) i = a; i < b; i++)
#define reprev(i, a, b) for (__typeof(a) i = a; i > b; i--)
#define repi(a, b) rep(i, a, b)
#define repj(a, b) rep(j, a, b)
#define repk(a, b) rep(k, a, b)
#define Cmplt(type) bool operator<(const type &o) const
#define Cmpgt(type) bool operator>(const type &o) const
#define Cmpfn(name, type) bool name(const type &a, const type &b)
#define Inop(type) istream& operator>>(istream& in, type &o)
#define Outop(type) ostream& operator<<(ostream& out, type o)
#define Pow2(x) (1LL << (x))
#define scn(type, ...) type __VA_ARGS__; scan(__VA_ARGS__) // scn -> Short for SCan New
// Shorthand Functions
template<typename T> inline void maxa(T& st, T v) { st = max(st, v); }
template<typename T> inline void mina(T& st, T v) { st = min(st, v); }
inline void setprec(ostream& out, int prec) { out << setprecision(prec) << fixed; }
// Out operators and printing for arrays and vectors
template <typename T> ostream& operator<<(ostream& out,vector<T> iter){out<<"[";for(auto t:iter){out<<t<<", ";}out<<"]";return out;}
template <typename T> string arrayStr(T *arr,int sz){string ret = "[";for(int i=0;i<sz;i++){ret+=to_string(arr[i])+", "; } return ret + "]";}
template <typename T> void printArray(T *arr,int sz){for(int i=0;i<sz;i++){cout<<arr[i]<<" "; } cout<<"\n";}
// I/O Operations
inline void scan(){}
template<typename F, typename... R> inline void scan(F &f,R&... r){cin>>f;scan(r...);}
template <typename F> inline void println(F t){cout<<t<<'\n';}
template<typename F, typename... R> inline void println(F f,R... r){cout<<f<<" ";println(r...);}
inline void print(){}
template<typename F, typename... R> inline void print(F f,R... r){cout<<f;print(r...);}
// Debugging
#define db(x) cout << (#x) << ": " << x << ", "
#define dblb(s) cout << "[" << s << "] "
#define dbbin(x, n) cout << (#x) << ": " << bitset<n>(x) << ", "
#define dbarr(x, n) cout << (#x) << ": " << arrayStr((x), (n)) << ", "
#define dbln cout << endl;
#pragma endregion

const int MN = 11, MSZ = 10000001;
int n, q, msub,
	lens[MN], pt[2][MN], coords[MN], arr[MSZ];
uint tree[MSZ];

// resolves the index in the array "coords" into a single number
inline int resolveindex(){
	int tot = 0, mtot = 1;
	repi(0, n) {
		tot += (coords[i] - 1) * mtot;
		mtot *= lens[i];
	}
	return tot + 1;
}

// Copies the values of base over to the "coords" array
void setcoords(int base[]){
	repi(0, n)
		coords[i] = base[i];
}

// adds the value to the point given by the "coords" array
void add(int dim, int val){
	if(dim == n)
		tree[resolveindex()] += val;
	else {
		for (; coords[dim] <= lens[dim]; coords[dim] += coords[dim] & -coords[dim]) {
			int lastnext = coords[dim + 1];
			add(dim + 1, val);
			coords[dim + 1] = lastnext;
		}
	}
}

// Sums the values up to the value given by the coords array
uint sum(int dim){
	// if (dim == n) { dbarr(coords, n); db(parity); dbln; }
	if (dim == n) {
		uint ret = tree[resolveindex()];
		// return parity ? (~ret + 1) : ret;
		return ret;
	}

	uint sumv = 0;
	for (int x = pt[1][dim]; x; x -= x & -x) {
		coords[dim] = x;
		sumv += sum(dim + 1);
	}
	if (pt[0][dim]) {
		for (int x = pt[0][dim]; x; x -= x & -x) {
			coords[dim] = x;
			sumv -= sum(dim + 1);
		}
	}
	return sumv;
}

inline void readdim(int arr[]){
	repi(0, n)
		scan(arr[i]);
}

// #define getchar() (*_pbuf ? *_pbuf++ : (_buf[fread_unlocked(_pbuf = _buf, 1, 1048576, stdin)] = 0, *_pbuf++))
char _buf[1048577], *_pbuf = _buf;

int readint() {
    int c, o = 0;
    while ((c = getchar()) < '0');
    do {o = (o<<3)+(o<<1) + (c - '0');} while ((c = getchar()) >= '0');
    return o;
}

int main(){
	// scan(n, q);
	n = readint(); q = readint();
	msub = 1 << n;

	repi(0, n) {
		// scan(lens[i]);
		lens[i] = readint();
	}

	repi(0, q) {
		// scn(int, bt);
		int bt = readint();
		readdim(pt[0]);

		if(bt == 1){
			// scn(int, bv);
			int bv = readint();

			setcoords(pt[0]);
			int idx = resolveindex();
			add(0, bv - arr[idx]);
			arr[idx] = bv;
		}
		else{ // bt == 2
			readdim(pt[1]);
			repj(0, n) pt[0][j]--;

			// dbarr(pt[0], n); dbarr(pt[1], n); dbln;
			uint ans = sum(0);

			println(ans);
		}
	}
}