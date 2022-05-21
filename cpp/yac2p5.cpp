// ./p5-mirror-maze.yml
#include <bits/stdc++.h>
#define DEBUG 0
using namespace std;

// Defines
#define fs first
#define sn second
#define pb push_back
#define eb emplace_back
#define mpr make_pair
#define mtp make_tuple
#define all(x) (x).begin(), (x).end()
// Basic type definitions
#if __cplusplus == 201703L // CPP17 only things
template <typename T> using opt_ref = optional<reference_wrapper<T>>; // for some templates
#endif
using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<long long, long long>;
#ifdef __GNUG__
// PBDS order statistic tree
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, class comp = less<T>> using os_tree = tree<T, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;
template <typename K, typename V, class comp = less<K>> using treemap = tree<K, V, comp, rb_tree_tag, tree_order_statistics_node_update>;
// HashSet
#include <ext/pb_ds/assoc_container.hpp>
template <typename T, class Hash> using hashset = gp_hash_table<T, null_type, Hash>;
template <typename K, typename V, class Hash> using hashmap = gp_hash_table<K, V, Hash>;
const ll RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash { ll operator()(ll x) const { return x ^ RANDOM; } };
#endif
// More utilities
int SZ(string &v) { return v.length(); }
template <typename C> int SZ(C &v) { return v.size(); }
template <typename C> void UNIQUE(vector<C> &v) { sort(v.begin(), v.end()); v.resize(unique(v.begin(), v.end()) - v.begin()); }
template <typename T, typename U> void maxa(T &a, U b) { a = max(a, b); }
template <typename T, typename U> void mina(T &a, U b) { a = min(a, b); }
const ll INF = 0x3f3f3f3f, LLINF = 0x3f3f3f3f3f3f3f3f;

/*
 * ax + by = gcd(a, b)
 *
 * we know
 * bx' + (a%b)y' = gcd(a, b)
 *
 * bx' + (a-b*(a//b))y' = gcd(a, b)
 * bx' + ay' - b*(a//b)y' = gcd(a, b)
 * ay' + b(x' - (a//b)y') = gcd(a, b)
 */
template <typename T> T extgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    T x0, y0, res = extgcd(b, a%b, x0, y0);
    x = y0;
    y = x0 - (a / b) * y0;
    return res;
}

// based on Tourist modInt orz
template <typename MD> struct _ModInt {
    using T = typename decay<decltype(MD::value)>::type;
    static_assert(sizeof(T) >= 4, "size of T must be at least 32 bits");
    static_assert(sizeof(T) <= 8, "size of T must be at most 64 bits");
    static_assert(is_integral<T>::value, "T must be an integral type");
#ifdef __SIZEOF_INT128__
    using mul_t = typename conditional<sizeof(T) <= 4, int64_t, __int128>::type;
#else
    using mul_t = int64_t;
    static_assert(sizeof(T) <= 4, "int128 not available, cannot use 64-bit size of T");
#endif

    constexpr static T mod() { return MD::value; }

    template <typename U> static T normalize(const U& x) {
        T res = x;
        res %= mod();
        if (res < 0) res += mod();
        return res;
    }

    T value;
    constexpr _ModInt() : value() {}
    template <typename U> _ModInt(const U& x) { value = normalize(x); }
    const T& operator()() const { return value; }
    template <typename U> operator U() const { return static_cast<U>(value); }

    // FastPow
    template <typename U> static _ModInt pow(_ModInt x, U y) {
        _ModInt res(1);
        for (; y; y /= 2) {
            if (y & 1) res *= x;
            x *= x;
        }
        return res;
    }
    static _ModInt inv(const _ModInt &x) {
        T inv, _; extgcd(x.value, mod(), inv, _);
        return _ModInt(inv);
    }

    // Arithmetic Operators w/ _ModInt
    // Assignment operators here
    _ModInt& operator+=(const _ModInt &o) { if ((value += o.value) >= mod()) value -= mod(); return *this; }
    template <typename U> _ModInt& operator+=(const U &o) { return *this += _ModInt(o); }
    _ModInt& operator-=(const _ModInt &o) { if ((value -= o.value) < 0) value += mod(); return *this; }
    template <typename U> _ModInt& operator-=(const U &o) { return *this -= _ModInt(o); }
    _ModInt& operator++() { return *this += 1; }
    _ModInt operator++(int) { _ModInt res(*this); *this += 1; return res; }
    _ModInt& operator--() { return *this -= 1; }
    _ModInt operator--(int) { _ModInt res(*this); *this -= 1; return res; }
    _ModInt& operator*=(const _ModInt &o) { value = (mul_t)value * o.value % mod(); if (value < 0) value += mod(); return *this; } // make sure cast to mul_t!!!
    template <typename U> _ModInt& operator*=(const U &o) { return *this *= _ModInt(o); }
    _ModInt& operator/=(const _ModInt &o) { return *this *= inv(o.value); }
    template <typename U> _ModInt& operator/=(const U &o) { return *this /= _ModInt(o); }
    _ModInt operator-() const { return _ModInt(value); }
    // Other Operators
    T& operator()() { return value; }
    // Definitions of some operators
};
// Binary operators
#define OP_CMP(op) template <typename T> bool operator op(const _ModInt<T> &lhs, const _ModInt<T> &rhs) { return lhs.value op rhs.value; } \
    template <typename T, typename U> bool operator op(const _ModInt<T> &lhs, U rhs) { return lhs op _ModInt<T>(rhs); } \
    template <typename T, typename U> bool operator op(U lhs, const _ModInt<T> &rhs) { return _ModInt<T>(lhs) op rhs; }
#define OP_ARI(op) template <typename T> _ModInt<T> operator op(const _ModInt<T> &lhs, const _ModInt<T> &rhs) { return _ModInt<T>(lhs) op##= rhs; } \
    template <typename T, typename U> _ModInt<T> operator op(U lhs, const _ModInt<T> &rhs) { return _ModInt<T>(lhs) op##= rhs; } \
    template <typename T, typename U> _ModInt<T> operator op(const _ModInt<T> &lhs, U rhs) { return _ModInt<T>(lhs) op##= rhs; }
OP_CMP(==) OP_CMP(!=) OP_CMP(<) OP_CMP(>) OP_CMP(<=) OP_CMP(>=)
OP_ARI(+) OP_ARI(-) OP_ARI(*) OP_ARI(/)
#undef OP_CMP
#undef OP_ARI
template <typename T> istream& operator>>(istream& in, _ModInt<T> &o) { return in >> o(); }
template <typename T> ostream& operator<<(ostream& out, _ModInt<T> &o) { return out << o(); }

// Definitions
template <typename T, T mod> using ModInt = _ModInt<integral_constant<T, mod>>;
template <typename T> struct VarMod {
    static T value;
    static void read(istream& in) { in >> value; }
    static void set(T v0) { value = v0; }
};
template <typename T> using VarModInt = _ModInt<VarMod<T>>;

template <typename T> struct Matrix {
    vector<vector<T>> m;

    Matrix(int N, int M) : m(N, vector<T>(M, T(0))) {}
    Matrix(const vector<vector<T>> &o) : m(o) {}
    Matrix(const Matrix &o) : m(o.m) {}
    static Matrix identity(int N) {
        Matrix res(N, N);
        for (int i = 0; i < N; i++) res[i][i] = T(1);
        return res;
    }

    int N() const { return m.size(); }
    int M() const { return m[0].size(); }
    vector<T>& operator[](int k) { return m[k]; }
    const vector<T>& operator[](int k) const { return m[k]; }
    bool invalid() { return m.size() == 0; } // For invalid returns (i.e. matrix not invertible)

    // Elementwise Stuff
    Matrix& operator+=(const Matrix &o) {
        assert(N() == o.N() && M() == o.M());
        for (int i = 0; i < N(); i++) for (int j = 0; j < M(); j++)
                m[i][j] += o[i][j];
        return *this;
    }
    Matrix& operator-=(const Matrix &o) {
        assert(N() == o.N() && M() == o.M());
        for (int i = 0; i < N(); i++) for (int j = 0; j < M(); j++)
                m[i][j] -= o[i][j];
        return *this;
    }

    // Matrix Multiplication
    Matrix& operator*=(const Matrix &o) {
        assert(this->M() == o.N());
        int N = this->N(), M = this->M(), K = o.M();
        vector<vector<T>> res(N, vector<T>(K, T(0)));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < K; j++)
                for (int k = 0; k < M; k++)
                    res[i][j] += m[i][k] * o[k][j];
        m = res;
        return *this;
    }

    // Scalar operations
    Matrix& operator+=(const T &o) {
        for (int i = 0; i < N(); i++) for (int j = 0; j < M(); j++)
                m[i][j] += o;
        return *this;
    }
    Matrix& operator-=(const T &o) {
        for (int i = 0; i < N(); i++) for (int j = 0; j < M(); j++)
                m[i][j] -= o;
        return *this;
    }
    Matrix& operator*=(const T &o) {
        for (int i = 0; i < N(); i++) for (int j = 0; j < M(); j++)
                m[i][j] *= o;
        return *this;
    }

    Matrix& operator-() {
        for (int i = 0; i < N(); i++) for (int j = 0; j < M(); j++)
                m[i][j] = -m[i][j];
    }

    // Reduced row echelon form
    T rref() {
        int nvar = min(N(), M());
        T det = 1;
        for (int i = 0; i < nvar; i++) {
            int target = -1;
            for (int j = i; j < N(); j++) {
                if (m[j][i] != 0) {
                    target = j;
                    break;
                }
            }
            if (target == -1) continue;
            if (i != target) {
                m[i].swap(m[target]);
                det *= -1;
            }

            T co = 1 / m[i][i];
            det *= m[i][i];
            for (int j = 0; j < M(); j++)
                m[i][j] *= co;
            for (int j = 0; j < N(); j++)
                if (j != i) {
                    T jco = m[j][i];
                    for (int k = 0; k < M(); k++)
                        m[j][k] -= jco * m[i][k];
                }
        }
        for (int i = 0; i < N(); i++)
            if (m[i][i] == 0)
                return T(0);

        return det;
    }
    static pair<Matrix, T> rref(Matrix m) { T det = m.rref(); return {m, det}; }

    // Augmenting
    void augment(const Matrix &o) {
        assert(N() == o.N());
        for (int i = 0; i < N(); i++)
            m[i].insert(m[i].end(), o[i].begin(), o[i].end());
    }
    static Matrix augment(Matrix m, const Matrix n) { m.augment(n); return m; }

    // Determinant
    T det() const {
        assert(N() == M()); // determinant is only for square matrices lmfao
        Matrix tmp(*this);
        return tmp.rref();
    }

    // Other functions
    static Matrix pow(Matrix x, ll y) {
        assert(x.N() == x.M());
        Matrix res = identity(x.N());
        for (; y; y /= 2) {
            if (y & 1) res *= x;
            x *= x;
        }
        return res;
    }
    static Matrix inv(Matrix x) {
        assert(x.N() == x.M());
        int n = x.N(); x.augment(identity(n));
        if (x.rref() == 0) return Matrix(0, 0); // Determinant == 0 -> no inverse
        Matrix res(x.N(), x.N());
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                res[i][j] = x[i][j + n];
        return res;
    }
    static Matrix solveLinear(Matrix coeffs, const Matrix &sums) {
        assert(coeffs.N() == coeffs.M() && sums.N() == coeffs.N() && sums.M() == 1);
        int oldN = coeffs.N();
        coeffs.augment(sums);
        coeffs.rref();
        Matrix res(coeffs.N(), 1);
        for (int i = 0; i < oldN; i++)
            res[i][0] = coeffs[i][oldN];
        return res;
    }
};

// Binary operators
#define OP_CMP(op) template <typename T> bool operator op(const Matrix<T> &lhs, const Matrix<T> &rhs) { return lhs.value op rhs.value; }
#define OP_ARI(op) template <typename T> Matrix<T> operator op(const Matrix<T> &lhs, const Matrix<T> &rhs) { return Matrix<T>(lhs) op##= rhs; } \
    template <typename T> Matrix<T> operator op(const Matrix<T> &lhs, T rhs) { return Matrix<T>(lhs) op##= rhs; }
OP_CMP(==) OP_CMP(!=) OP_CMP(<) OP_CMP(>) OP_CMP(<=) OP_CMP(>=)
OP_ARI(+) OP_ARI(-) OP_ARI(*) OP_ARI(/)
template <typename T> Matrix<T> operator+(T lhs, const Matrix<T> &rhs) { return Matrix<T>(rhs) += lhs; }
template <typename T> Matrix<T> operator*(T lhs, const Matrix<T> &rhs) { return Matrix<T>(rhs) *= lhs; }
#undef OP_CMP
#undef OP_ARI

using MI = ModInt<int, 1000000007>;
using Mat = Matrix<MI>;

const int MN = 51, MB = 30;
int N, L,
    adj[MN][MN];
MI ans[MN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L;
    for (auto i = 0; i < N; i++)
        for (auto j = 0; j < N; j++)
            cin >> adj[i][j];

    for (auto i = 0; i <= MB; i++) {
        Mat probs(N+1, N+1);
        for (auto j = 0; j < N; j++) {
            MI prob = MI(1) / (N-1);

            for (auto k = 0; k < N; k++) {
                if ((adj[j][k] >> i) & 1) {
                    probs[N][j] += prob;
                }
                else if (j != k) {
                    probs[k][j] += prob;
                }
            }
        }
        probs[N][N] = 1; // make sure you can go from success to itself
 
        if (i < 5) {
            if (DEBUG) { cout<<"i="<<(i)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i
            for (auto j = 0; j <= N; j++) {
                if (DEBUG) { cout << "probs[j]=["; for (auto __x:probs[j])cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db I:probs[j]
            }
        }

        probs = Mat::pow(probs, L);
 
        if (i < 5) {
            if (DEBUG) { cout<<"i="<<(i)<<", "; cout << endl; } //__RAW_DEBUG_LINE__:db i
            for (auto j = 0; j <= N; j++) {
                if (DEBUG) { cout << "probs[j]=["; for (auto __x:probs[j])cout<<__x<<", "; cout<<"], "; cout << endl; } //__RAW_DEBUG_LINE__:db I:probs[j]
            }
        }

        for (auto j = 0; j < N; j++) {
            ans[j] += probs[N][j] * MI::pow(2, i);
        }
    }

    for (auto i = 0; i < N; i++)
        cout << ans[i] << " \n"[i == N-1];

    return 0;
}