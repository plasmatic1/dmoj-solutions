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

// im lazy
ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

ll intsqrt(ll s) {
    ll l = 0, r = min(s, 1000000000LL), ans = -1;

    while (l <= r) {
        ll mid = (l + r) / 2;
        if (mid * mid <= s) {
            ans = mid;
            l = mid + 1;
        }
        else {
            r = mid - 1;
        }
    }

    return ans;
}

ll mod(ll x, ll m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

ll modmul(ll a, ll b, ll m) {
    ll res = 0;
    while (b > 0) {
        if (b & 1) res = mod(res + a, m);
        b /= 2;
        a = mod(a + a, m);
    }
    return res;
}

using u64 = uint64_t;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1)
            result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}
bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
};

bool MillerRabin(u64 n) { // returns true if n is prime, else returns false.
    if (n < 2)
        return false;

    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }

    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a)
            return true;
        if (check_composite(n, a, d, r))
            return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Input::Validator in(std::cin);

    int T = in.readInt(1, 100);
    in.readNewLine();
    for (auto _ = 0; _ < T; _++) {
        ll N = in.readInt(1, 1000000000000000000LL);
        in.readSpace();
        ll e = in.readInt(1, 1000000000000000000LL);
        in.readSpace();
        ll c1 = in.readInt(0, N-1);
        in.readSpace();
        ll c2 = in.readInt(0, N-1);
        in.readNewLine();

        assert(e % 2 == 1);

        ll pe = modmul(mod(c1 + c2, N), N / 2 + 1, N);
        ll qe = mod(c1 - pe, N);

        ll p = gcd(pe, N);
        ll q = gcd(qe, N);

        if (p > q)
            swap(p, q);
        if (p == N) {
            p = intsqrt(p);
            q = p;
        }

        cout << (p) << ' ' << (q) << '\n';
        cout.flush();
        assert(3 <= p && p <= 1000000000000000000LL);
        assert(3 <= q && q <= 1000000000000000000LL);
        assert(MillerRabin(p));
        assert(MillerRabin(q));
    }
    in.readEOF();

    return 0;
}