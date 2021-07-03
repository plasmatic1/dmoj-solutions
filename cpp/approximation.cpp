#include <bits/stdc++.h>
using namespace std;
template <class C> constexpr int sz(const C &c) { return int(c.size()); }
constexpr const char nl = '\n', sp = ' '; using uint = unsigned int;
using ll = long long; using ull = unsigned long long; using ld = long double;
#if __SIZEOF_INT128__
  using i128 = __int128_t; using ui128 = __uint128_t;
#endif

namespace Validator {
  std::regex nonWhitespaceToken("\\S+"), nonWhitespaceChar("\\S"), anyLine(".+");
  bool _hasLast = false;
  char _last;

  char _peekChar() {
    _last = _hasLast ? _last : getchar();
    _hasLast = true;
    return _last;
  }

  char _getChar() {
    char ret = _peekChar();
    _hasLast = false;
    return ret;
  }

  long long readInt(long long minValid = std::numeric_limits<long long>::min(), long long maxValid = std::numeric_limits<long long>::max()) {
    std::string token = "";
    while (isdigit(_peekChar()) || _peekChar() == '-') token.push_back(_getChar());
    long long ret = std::stoll(token);
    assert(minValid <= ret && ret <= maxValid);
    return ret;
  }

  long double readFloat(long double minValid = std::numeric_limits<long double>::lowest(), long double maxValid = std::numeric_limits<long double>::max()) {
    std::string token = "";
    while (isdigit(_peekChar()) || _peekChar() == '-' || _peekChar() == '.') token.push_back(_getChar());
    long double ret = std::stold(token);
    assert(minValid <= ret && ret <= maxValid);
    return ret;
  }

  std::string readString(const std::regex &rgx = nonWhitespaceToken) {
    std::string ret = "";
    while (!isspace(_peekChar())) ret.push_back(_getChar());
    assert(std::regex_match(ret, rgx));
    return ret;
  }

  char readChar(const std::regex &rgx = nonWhitespaceChar) {
    char ret = _getChar();
    assert(std::regex_match(std::string(1, ret), rgx));
    return ret;
  }

  std::string readLine(const std::regex &rgx = anyLine) {
    std::string ret = "";
    while (_peekChar() != '\n') ret.push_back(_getChar());
    assert(std::regex_match(ret, rgx));
    return ret;
  }

  void readSpace() {
    assert(_getChar() == ' ');
  }

  void readNewLine() {
    assert(_getChar() == '\n');
  }

  void readEOF() {
    assert(_getChar() == std::char_traits<char>::eof());
  }
}

using F = double;

using namespace Validator;

const F PI = acos(-1);
ll cnt(ll h) {
    ll res = 0, ptr = 0;
    for (auto i = h; i >= 1; i--) {
        while (i*i+(ptr+1)*(ptr+1)<=h*h) ptr++;
        res += ptr;
    }
    return res;
}
F cntf(F h) { return PI*h*h*0.25; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T = readInt(); readNewLine();
    while (T--) {
        int h = readInt(); readNewLine();
        if (h > 10000) cout << cntf(h) << '\n';
        else cout << cnt(h) << '\n';
    }
    readEOF();

    return 0;
}