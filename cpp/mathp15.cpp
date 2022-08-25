// sol.yml
#include <bits/stdc++.h>
#define DEBUG 1
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

namespace ExitCode {
  const int AC = 0, WA = 1, PE = 2, IE = 3, PARTIAL = 7;
}

namespace Input {
  struct PresentationError : public std::exception {};
  struct IntegerParsingError : public PresentationError {};
  struct FloatingPointParsingError : public PresentationError {};
  struct WhitespaceError : public PresentationError {};
  struct RequirementFailure : public std::exception {};
  struct IntegerRangeError : public RequirementFailure {};
  struct FloatingPointRangeError : public RequirementFailure {};
  struct RegexError : public RequirementFailure {};

  struct ValidatorErrorHandler {
  public:
    template <class E> void handle(const E &e) {
      throw e;
    }
  };

  struct CheckerErrorHandler {
  public:
    void handle(const PresentationError &) {
      exit(ExitCode::PE);
    }
    void handle(const RequirementFailure &) {
      exit(ExitCode::WA);
    }
  };

  const bool IDENTICAL = true, STANDARD = false;

  template <class ErrorHandler, const bool IDENTICAL_WHITESPACE> struct Reader : public ErrorHandler {
  private:
    std::unique_ptr<std::ifstream> streamPtr;
    std::istream &stream;
    bool hasLast;
    bool skipToNextLine;
    char last;

    bool isWhitespace(char c) {
      if (IDENTICAL_WHITESPACE) return c == ' ' || c == '\n';
      return isspace(c);
    }

    bool isNewLine(char c) {
      if (IDENTICAL_WHITESPACE) return c == '\n';
      return c == '\n' || c == '\r';
    }

    bool isEOF(char c) {
      return c == std::char_traits<char>::eof();
    }

    char peekChar() {
      if (!hasLast) last = stream.get();
      hasLast = true;
      return last;
    }

    char getChar() {
      char ret = peekChar();
      hasLast = false;
      return ret;
    }

    void skipWhitespace() {
      while (isWhitespace(peekChar()) && (skipToNextLine || !isNewLine(peekChar()))) getChar();
      skipToNextLine = false;
    }

  public:
    template <class E> void require(bool expr, const E &e) {
      if (!expr) ErrorHandler::handle(e);
    }

    template <class ...Args> Reader(std::istream &stream, Args &&...args)
        : ErrorHandler(std::forward<Args>(args)...), stream(stream), hasLast(false), skipToNextLine(true) {}

    template <class ...Args> Reader(const std::string &fileName, Args &&...args)
        : ErrorHandler(std::forward<Args>(args)...), streamPtr(std::make_unique<std::ifstream>(fileName)),
          stream(*streamPtr), hasLast(false), skipToNextLine(true) {}

    long long readInt(long long minValid = std::numeric_limits<long long>::min(),
                      long long maxValid = std::numeric_limits<long long>::max()) {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      std::string token = "";
      while (isdigit(peekChar()) || peekChar() == '-') token.push_back(getChar());
      long long ret = 0;
      try {
        ret = std::stoll(token);
      } catch (std::invalid_argument &) {
        ErrorHandler::handle(IntegerParsingError());
      } catch (std::out_of_range &) {
        ErrorHandler::handle(IntegerParsingError());
      }
      require(minValid <= ret && ret <= maxValid, IntegerRangeError());
      return ret;
    }

    long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(),
                          long double maxValid = std::numeric_limits<long double>::max()) {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      std::string token = "";
      while (isdigit(peekChar()) || peekChar() == '-' || peekChar() == '.') token.push_back(getChar());
      long double ret = 0;
      try {
        ret = std::stold(token);
      } catch (std::invalid_argument &) {
        ErrorHandler::handle(FloatingPointParsingError());
      } catch (std::out_of_range &) {
        ErrorHandler::handle(FloatingPointParsingError());
      }
      require(minValid <= ret && ret <= maxValid, FloatingPointRangeError());
      return ret;
    }

    std::string readString(std::regex rgx) {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      std::string ret = "";
      while (!isWhitespace(peekChar()) && !isEOF(peekChar())) ret.push_back(getChar());
      require(std::regex_match(ret, rgx), RegexError());
      return ret;
    }

    std::string readString() {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      std::string ret = "";
      while (!isWhitespace(peekChar()) && !isEOF(peekChar())) ret.push_back(getChar());
      return ret;
    }

    char readChar(std::regex rgx) {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      char ret = getChar();
      require(std::regex_match(std::string(1, ret), rgx), RegexError());
      return ret;
    }

    char readChar() {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      return getChar();
    }

    std::string readLine(std::regex rgx) {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      std::string ret = "";
      while (!isNewLine(peekChar()) && !isEOF(peekChar())) ret.push_back(getChar());
      require(std::regex_match(ret, rgx), RegexError());
      return ret;
    }

    std::string readLine() {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      std::string ret = "";
      while (!isNewLine(peekChar()) && !isEOF(peekChar())) ret.push_back(getChar());
      return ret;
    }

    void readSpace() {
      require(isWhitespace(peekChar()) && !isNewLine(peekChar()), WhitespaceError());
      getChar();
    }

    void readNewLine() {
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      skipToNextLine = true;
      require((!IDENTICAL_WHITESPACE && isEOF(peekChar())) || isNewLine(getChar()), WhitespaceError());
    }

    bool atEOF() {
      skipToNextLine = true;
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      return isEOF(peekChar());
    }

    void readEOF() {
      skipToNextLine = true;
      if (!IDENTICAL_WHITESPACE) skipWhitespace();
      require(isEOF(getChar()), WhitespaceError());
    }
  };

  using Validator = Reader<ValidatorErrorHandler, IDENTICAL>;
  using StandardReader = Reader<CheckerErrorHandler, STANDARD>;
  using IdenticalReader = Reader<CheckerErrorHandler, IDENTICAL>;
}

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
        T res = x % mod();
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
        assert(sums.N() == coeffs.N() && sums.M() == 1);
        int oldM = coeffs.M();
        coeffs.augment(sums);
        coeffs.rref();
        Matrix res(oldM, 1);
        for (int i = 0; i < oldM; i++)
            res[i][0] = coeffs[i][oldM];
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

const int MOD = 1e9 + 7;
using MI = ModInt<int, MOD>;
using Mat = Matrix<MI>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Input::Validator in(cin);

    int N = in.readInt(1, 500); in.readNewLine();
    Mat m(N+1, N);
    Mat ref(N, N);

    for (auto i = 0; i < N; i++) {
        for (auto j = 0; j < N; j++) {
            m[i][j] = in.readInt(1, MOD-1); // non zero
            ref[i][j] = m[i][j];

            if (j < N-1) in.readSpace();
            else in.readNewLine();
        }
    }
    for (auto i = 0; i < N; i++) {
        MI colSum = 0;
        for (auto j = 0; j < N; j++) {
            colSum += m[j][i];
        }
        assert(colSum == 1);
    }
    in.readEOF();

    // ubtract I
    for (auto i = 0; i < N; i++)
        m[i][i] -= 1;
    // other stuff
    for (auto i = 0; i < N; i++)
        m[N][i] = 1;

    Mat result(N+1, 1); result[N][0] = 1;
    auto ans = Mat::solveLinear(m, result);

    for (auto i = 0; i < N; i++)
        cout << ans[i][0] << " \n"[i == N-1];

    // check answer
    {
        auto tmp = ref * ans;
        for (auto i = 0; i < N; i++) {
            assert(tmp[i][0] == ans[i][0]);
        }
    }

    return 0;
}